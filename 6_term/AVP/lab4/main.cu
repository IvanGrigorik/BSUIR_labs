#include <iostream>
#include <random>
#include <curand_kernel.h>
#include <chrono>

#include <thrust/reduce.h>
#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/execution_policy.h>

using namespace std;
using namespace chrono;

typedef struct Point {
    float x{};
    float y{};
    float z{};

    Point() = default;

    Point(double a_x, double a_y, double a_z);

    Point &operator=(const Point &a) = default;

} Point;

Point::Point(double a_x, double a_y, double a_z) {
    x = static_cast<float>(a_x);
    y = static_cast<float>(a_y);
    z = static_cast<float>(a_z);
}

typedef struct Plane {
    float x;
    float y;
    float z;
    float d;

    Plane &operator=(const Plane &a) = default;
} Plane;

Plane define_plane(Point p1, Point p2, Point p3) {
    Point m1m2{}, m1m3{};
    m1m2 = {p2.x - p1.x, p2.y - p1.y, p2.z - p1.z};
    m1m3 = {p3.x - p1.x, p3.y - p1.y, p3.z - p1.z};
    Plane result_plane;

    result_plane = {m1m2.y * m1m3.z - m1m2.z * m1m3.y,
                    m1m2.z * m1m3.x - m1m2.x * m1m3.z,
                    m1m2.x * m1m3.y - m1m2.y * m1m3.x};
    result_plane.d = -p1.x * result_plane.x + -p1.y * result_plane.y +
                     -p1.z * result_plane.z;
    return result_plane;
}

__managed__
Plane planes[4]{};

const int numBlocks = 1024;

__managed__ int shared_grid[numBlocks];

__global__ void kernel(Point r_min, Point r_max, const bool *planes_signs) {
    unsigned idx = blockIdx.x * blockDim.x + threadIdx.x;

    curandState localState;
    curand_init(1234, idx, 0, &localState);

    Point p;
    p.x = curand_uniform(&localState) * (r_max.x - r_min.x) + r_min.x;
    p.y = curand_uniform(&localState) * (r_max.y - r_min.y) + r_min.y;
    p.z = curand_uniform(&localState) * (r_max.z - r_min.z) + r_min.z;

    float sides[4];
    bool signs[4]{};

    for (int j = 0; j < 4; j++) {
        sides[j] = planes[j].x * p.x +
                   planes[j].y * p.y +
                   planes[j].z * p.z +
                   planes[j].d;
        signs[j] = signbit(sides[j]);
    }

    bool is_hit = true;
    for (int i = 0; i < 4; i++) {
        if (signs[i] != planes_signs[i]) {
            is_hit = false;
            break;
        }
    }

    // Synchronize threads in block
    extern __shared__ int shared_block[];
    shared_block[threadIdx.x] = is_hit ? 1 : 0;

    __syncthreads();
    size_t stride = blockDim.x / 2;

    while (stride > 0) {
        if (threadIdx.x >= stride) {
            return;
        }

        shared_block[threadIdx.x] += shared_block[threadIdx.x + stride];
        stride /= 2;
        __syncthreads();
    }

    shared_grid[blockIdx.x] = shared_block[threadIdx.x];
}

int run_cpu(Point r_min, Point r_max, int try_counter) {
    random_device rd;
    mt19937 rng(rd());
    uniform_real_distribution<> dist_x(r_min.x, r_max.x);
    uniform_real_distribution<> dist_y(r_min.y, r_max.y);
    uniform_real_distribution<> dist_z(r_min.z, r_max.z);

    float sides[4]{};
    int hit_counter = 0;
    bool signs[4]{};
    bool planes_signs[4]{};
    for (int i = 0; i < 4; i++) {
        planes_signs[i] = signbit(planes[i].d);
    }

    for (int i = 0; i < try_counter; i++) {
        Point p{dist_x(rng), dist_y(rng), dist_z(rng)};

        for (int j = 0; j < 4; j++) {
            sides[j] = planes[j].x * p.x +
                       planes[j].y * p.y +
                       planes[j].z * p.z +
                       planes[j].d;

            signs[j] = signbit(sides[j]);
        }

        bool is_hit = true;
        for (int j = 0; j < 4; j++) {
            if (signs[j] != planes_signs[j]) {
                is_hit = false;
                break;
            }
        }

        if (is_hit) {
            hit_counter++;
        }
    }

    return hit_counter;
}


int main() {
    // GPU info output
    int nDevices{};
    cudaGetDeviceCount(&nDevices);

    for (int i = 0; i < nDevices; i++) {

        cudaDeviceProp prop{};

        cudaGetDeviceProperties(&prop, 0);
        cout << "GPU: " << prop.name << endl;
        cout << "Global memory: " << prop.totalGlobalMem << endl;
        cout << "Shared memory: "
             << prop.sharedMemPerBlock * prop.sharedMemPerBlock << endl;
        cout << "Compute capability: " << prop.major << "." << prop.minor
             << endl;
    }

    Point A{0.4, 0.5, -0.05}, B{0.2, -1, -0.2},
            C{-2, -0.3, -0.5}, D{-0.1, 0.05, 0.3};

    planes[0] = define_plane(A, B, C);
    planes[1] = define_plane(A, B, D);
    planes[2] = define_plane(B, C, D);
    planes[3] = define_plane(C, A, D);

    Point points[4] = {A, B, C, D};
    Point r_min{A.x, A.y, A.z}, r_max{A.x, A.y, A.z};

    for (auto point: points) {
        r_min.x = point.x < r_min.x ? point.x : r_min.x;
        r_min.y = point.y < r_min.y ? point.y : r_min.y;
        r_min.z = point.z < r_min.z ? point.z : r_min.z;

        r_max.x = point.x > r_max.x ? point.x : r_max.x;
        r_max.y = point.y > r_max.y ? point.y : r_max.y;
        r_max.z = point.z > r_max.z ? point.z : r_max.z;
    }

//    int gpu_precision = 10'000'000;
    int cpu_precision = 51'200;
    auto main_volume =
            (r_max.x - r_min.x) * (r_max.y - r_min.y) * (r_max.z - r_min.z);

    auto start = steady_clock::now();
    auto cpu_hits = run_cpu(r_min, r_max, cpu_precision);
    auto time = duration_cast<milliseconds>(
            steady_clock::now() - start).count();
    cout << "CPU time: " << time << " milliseconds." << endl;
    cout << "CPU volume: " << static_cast<float>(cpu_hits) * main_volume /
                              static_cast<float>(cpu_precision) << endl;
    cout << "CPU hits: " << cpu_hits << endl;


    bool planes_signs[4]{};
    for (int i = 0; i < 4; i++) {
        planes_signs[i] = signbit(planes[i].d);
    }

    bool *d_planes_signs;
    cudaMalloc(&d_planes_signs, 4 * sizeof(bool));
    cudaMemcpy(d_planes_signs, planes_signs, 4 * sizeof(bool),
               cudaMemcpyHostToDevice);

    int threadsPerBlock = 512;

    cudaEvent_t start_event, stop_event;
    cudaEventCreate(&start_event);
    cudaEventCreate(&stop_event);

    cudaEventRecord(start_event);

    kernel<<<numBlocks, threadsPerBlock, /*Shared memory size*/1024>>>(r_min, r_max, d_planes_signs);
    cudaDeviceSynchronize();
    thrust::device_vector<unsigned> d_vec(shared_grid, shared_grid + numBlocks);
    auto gpu_hits = thrust::reduce(thrust::device,
                                   d_vec.begin(), d_vec.end(),
                                   0, thrust::plus<>());

    cudaEventRecord(stop_event);
    cudaEventSynchronize(start_event);
    cudaEventSynchronize(stop_event);

    float milliseconds = 0;
    cudaEventElapsedTime(&milliseconds, start_event, stop_event);
    cout << "GPU time: " << milliseconds << endl;

    auto gpu_precision = threadsPerBlock * numBlocks;
    cout << "GPU volume: " << static_cast<float>(gpu_hits) * main_volume /
                              static_cast<float>(gpu_precision) << endl;
    cout << "GPU hits: " << gpu_hits;
    cout << gpu_hits;
    return 0;
}
