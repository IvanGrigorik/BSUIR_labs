#include <iostream>

#define M 4        // Must be divisible by 4
#define N 4        // Must be divisible by 4
#define window_size 2

int main() {

    int **matrix = new int *[M];
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
            std::cout << matrix[1][1];
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {



        }
    }




    return 0;
}
