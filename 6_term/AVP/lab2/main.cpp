#include <iostream>
<<<<<<< HEAD

#define M 4        // Must be divisible by 4
#define N 4        // Must be divisible by 4
#define window_size 2

int main() {

    auto **matrix = new int *[M];
    for (int i = 0; i < M; i++) {
        matrix[i] = new int[N];
    }

    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            matrix[i][j] = j + i;
        }
    }

    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cout << matrix[i][j] << ' ';
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {



        }
    }




    return 0;
}
=======
#include <chrono>
#include <sciplot/sciplot.hpp>

using namespace std;
using namespace chrono;

#define cache_path "/sys/devices/system/cpu/cpu0/cache/index3/size"

size_t get_cache_size() {
    size_t size;
    std::ifstream cache_size_stream(cache_path);
    cache_size_stream >> size;
    size *= 1024;
    return size;
}

const size_t L3_SIZE = get_cache_size();
const size_t L3_ELEMENTS_NUM = L3_SIZE / 64;

union Cell_t {
    size_t index{};
    [[maybe_unused]] uint8_t fill[64]; // Just reserve 64 bytes for one element
};

void init(Cell_t *arr, size_t N);

int main() {
    constexpr int N_max = 30;

    auto *arr = static_cast<Cell_t *>(aligned_alloc(64, N_max * 10 * L3_SIZE));
    sciplot::Vec timings{};
    sciplot::Vec Ns{};

    timings.resize(28);
    Ns.resize(28);

    for (int N = 2; N < 30; ++N) {
        init(arr, N);

        volatile size_t t = 0;

        auto start = steady_clock::now();
        for (int k = 0; k < 1'000'000'000; ++k) {
            t = arr[t].index;
        }
        auto duration = duration_cast<milliseconds>(steady_clock::now() - start).count();

        Ns[N - 2] = N;
        timings[N - 2] = static_cast<double>(duration);
        cout << N << ") " << duration << endl;
    }

    sciplot::Plot2D plot;
    plot.autoclean(false);
    plot.fontSize(10);
    plot.legend().hide();


    // Plot the data
    plot.drawBrokenCurve(Ns, timings).label(" ");

    sciplot::Figure fig = {{plot}};
    sciplot::Canvas canvas = {{fig}};
    canvas.size(1200, 700);
    canvas.show();
    canvas.save("Cache.pdf");
}

void init(Cell_t *arr, size_t N) {
    auto block_size = L3_SIZE * 10 / N;
    auto elements_num = block_size / 64;

    for (int i = 0; i < elements_num; ++i) {
        for (int j = 0; j < N; ++j) {
            arr[i + j * L3_ELEMENTS_NUM].index = i + (j + 1) * L3_ELEMENTS_NUM;
        }
        arr[i + (N - 1) * L3_ELEMENTS_NUM].index = (i == elements_num) ? 0 : i + 1;
    }
}
>>>>>>> 15ab466f592d11bed13ad857f8558c426106c980
