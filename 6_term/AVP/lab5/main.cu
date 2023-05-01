#include "cpu.cuh"
#include "Image.cuh"
#include "utilities.cuh"
#include <iostream>

__device__ GPUPixel markerGPU{0, 255, 0};
__device__ GPUPixel threshold{20, 20, 20};

__global__ void kernel(const ImageGPU image, int *houghAccum,   //NOLINT (to disable clang-tidy)
                       float step, int thetasCount, int maxDist,//
                       int height, int width, size_t pitch) {
    const unsigned x = threadIdx.x + blockDim.x * blockIdx.x;
    const unsigned y = threadIdx.y + blockDim.y * blockIdx.y;

    if (y >= height || x >= width) {
        return;
    }

    auto row = reinterpret_cast<GPUPixel *>(reinterpret_cast<uint8_t *>(image.devData) + pitch * y);
    auto element = row[x];
    //    printf("x:%d y:%d: %d:%d:%d\n", x, y, element.red, element.green, element.blue);

    if (element.red - markerGPU.red >= threshold.red or      //
        element.green - markerGPU.green >= threshold.green or//
        element.blue - markerGPU.blue >= threshold.blue) {
        return;
    }

    double ang = -90;
    for (int h = 0; h < thetasCount; ang += step, h++) {
        int idx = static_cast<int>(maxDist + x * cos(degToRad(ang)) + y * sin(degToRad(ang)));
        atomicAdd(&houghAccum[idx + h], 1);
    }
}


double houghGPU(const ImageGPU &image, const int numBlocks, dim3 threadsPerBlock) {
    using namespace std;
    int *houghAccum;
    const int maxDist = static_cast<int>(round(sqrt(pow(image.height, 2) + pow(image.width, 2))));
    const int thetasCount = 2 * (image.height + image.width) - 4;

    // May be wrong calculate houghAccum len (paranoid, all ok)?
    auto accumLen = 2 * maxDist * thetasCount;
    CUDA_ASSERT(cudaMallocManaged(&houghAccum, accumLen * sizeof(int)))
    CUDA_ASSERT(cudaMemset(houghAccum, 0, accumLen * sizeof(int)))

    const float step = 180.f / static_cast<float>(thetasCount);

    kernel<<<numBlocks, threadsPerBlock>>>(image, houghAccum, step, thetasCount, maxDist,//
                                           image.height, image.width, image.pitch);
    CUDA_ASSERT(cudaDeviceSynchronize())

    int idx{}, max{};
    for (int i = 0; i < maxDist * 2; i++) {
        for (int j = 0; j < thetasCount; j++) {
            if (houghAccum[i * thetasCount + j] > max) {
                max = houghAccum[i * thetasCount + j];
                idx = j;
            }
        }
    }

    auto angle = -90 + step * static_cast<float>(idx);
    cout << angle << endl;

    return angle;
}

void rotateLine(const std::string &imagePath, const int numBlocks, dim3 threadsPerBlock) {
    ImageGPU image{"../images/rgb.png"};
    image.readImage();

    const auto houghtResult = houghGPU(image, numBlocks, threadsPerBlock);
}

int main() {
    using namespace std;

    const int numBlocks = 2;
    dim3 threadsPerBlock(10, 10);

    rotateLine("../images/untitled.png", numBlocks, threadsPerBlock);
    cout << "CPU implementation: " << endl;
    runCpu("../images/untitled.png");

    return 0;
}
