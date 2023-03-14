#include <iostream>
#include <iomanip>
#include <chrono>

using namespace std::chrono;

using namespace std;

#define N /*16*/ /*32*/ /*64*/ 128

__managed__
int matrix[N][N];

void fill_matrix() {
    unsigned n = 1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = n++;
        }
    }
}

__managed__ int out_matrix_gpu[N][N];
int out_matrix_cpu[N][N];

__global__ void mash_gpu() {
    unsigned idx = blockIdx.x * blockDim.x + threadIdx.x;
    unsigned i = idx / N % N;
    unsigned j = idx % N;
    auto i_1 = i, j_1 = j;

    auto quarter_i = i % 2;
    auto quarter_j = j % 2;

    quarter_i == 0 ? i /= 2 : i += (N - i) / 2;
    quarter_j == 0 ? j /= 2 : j += (N - j) / 2;

    out_matrix_gpu[i][j] = matrix[i_1][j_1];
}

void mash_cpu() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            auto i_out = i;
            auto j_out = j;

            auto quarter_i = i % 2;
            auto quarter_j = j % 2;

            if (quarter_i == 0) {
                i_out /= 2;
            } else if (quarter_i == 1) {
                i_out = i_out + (N - i_out) / 2;
            }

            if (quarter_j == 0) {
                j_out /= 2;
            } else if (quarter_j == 1) {
                j_out = j_out + (N - j_out) / 2;
            }

            out_matrix_cpu[i_out][j_out] = matrix[i][j];
        }
    }
};

void run_gpu() {
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    cudaEventRecord(start);
    mash_gpu<<<N + 127 / 128, 128>>>();
    cudaDeviceSynchronize();
    cudaEventRecord(stop);

    cudaEventSynchronize(stop);
    float milliseconds = 0;
    cudaEventElapsedTime(&milliseconds, start, stop);

    cout << "GPU elapsed time: " << milliseconds << endl;
    cudaDeviceSynchronize();

}

void run_cpu() {

    auto start = steady_clock::now();
    mash_cpu();
    auto time = duration_cast<microseconds>(
            steady_clock::now() - start).count();
    cout << "CPU elapsed time: " << static_cast<double>(time) / 1000 << endl;
}

bool is_equal() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (out_matrix_cpu[i][j] != out_matrix_gpu[i][j]) {
                return false;
            }
        }
    }
    return true;
}

int main() {

    fill_matrix();

    run_gpu();
    run_cpu();

    cout << "Is matrix equal: " << std::boolalpha << is_equal() << endl;
}


//void matrix_output() {
//    cout << "Initial matrix: " << endl;
//    for (int i = 0; i < N; i++) {
//        cout << "|";
//        for (int j = 0; j < N; j++) {
//            cout << setw(3) << matrix[i][j] << ' ';
//            if ((j + 1) % 2 == 0) {
//                cout << "| ";
//            }
//        }
//        if ((i + 1) % 2 == 0 && i + 1 != N) {
//            cout << endl;
//            for (int k = 0; k < N; k++) {
//                cout << setw(3) << "-----";
//            }
//        }
//        cout << endl;
//    }
//
//    cout << endl << "Result matrix: " << endl;
//    for (int i = 0; i < N; i++) {
//        for (int j = 0; j < N; j++) {
//            cout << setw(3) << out_matrix[i][j] << ' ';
//            if (j == N / 2 - 1) {
//                cout << setw(3) << "| ";
//            }
//        }
//        if (i == N / 2 - 1) {
//            cout << endl;
//            for (int k = 0; k < N; k++) {
//                cout << setw(3) << "----";
//            }
//        }
//
//        cout << endl;
//    }
//}