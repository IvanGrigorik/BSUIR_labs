<<<<<<< HEAD
#include <iostream>
#include <random>
#include <vector>

// AVX/AVX2
#include <immintrin.h>
#include <chrono>

using namespace std;

#define MATRIX_SIZE 32
#define BIG_MATRIX_SIZE 40

using SmallMatrix = vector<vector<float>>;
using BigMatrix = vector<vector<SmallMatrix>>;

#define NEW_BIG_MATRIX BIG_MATRIX_SIZE, {BIG_MATRIX_SIZE, {MATRIX_SIZE, std::vector<float>(MATRIX_SIZE)}}
#define NEW_SMALL_MATRIX MATRIX_SIZE, {std::vector<float>(MATRIX_SIZE)}

void randomize_one_matrix(BigMatrix &matrix) {

    random_device device;
    mt19937 generator{device()};
    uniform_real_distribution<float> distribution(0.0, 1.0);

    for (auto &i: matrix)
        for (auto &j: i)
            for (auto &k: j)
                for (auto &l: k)
                    l = distribution(generator);
}

void sum_small_matrices(SmallMatrix &matrix1, const SmallMatrix &matrix2) {

    for (int i = 0; i < MATRIX_SIZE; i++)
        for (int j = 0; j < MATRIX_SIZE; j++)
            matrix1[i][j] += matrix2[i][j];
}


__attribute__((target("sse")))
SmallMatrix multiply_matrices_avx(SmallMatrix &matrix1, SmallMatrix &matrix2) {

    SmallMatrix small_matrix_result(NEW_SMALL_MATRIX);

    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            for (int k = 0; k < MATRIX_SIZE; k++) {
                small_matrix_result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    return small_matrix_result;
}

BigMatrix calculate_avx(BigMatrix &matrix1, BigMatrix &matrix2) {

    BigMatrix result_big_matrix(NEW_BIG_MATRIX);

    for (int i = 0; i < BIG_MATRIX_SIZE; i++) {
        for (int j = 0; j < BIG_MATRIX_SIZE; j++) {
            for (int k = 0; k < BIG_MATRIX_SIZE; k++) {
                auto multiplication = multiply_matrices_avx(matrix1[i][k], matrix2[k][j]);
                sum_small_matrices(result_big_matrix[i][j], multiplication);
            }
        }
    }
    return result_big_matrix;
}

__attribute__((target("no-sse")))
SmallMatrix multiply_matrices(SmallMatrix &matrix1, SmallMatrix &matrix2) {

    SmallMatrix small_matrix_result(NEW_SMALL_MATRIX);

    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            for (int k = 0; k < MATRIX_SIZE; k++) {
                small_matrix_result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    return small_matrix_result;
}

BigMatrix calculate(BigMatrix &matrix1, BigMatrix &matrix2) {

    BigMatrix result_big_matrix(NEW_BIG_MATRIX);

    for (int i = 0; i < BIG_MATRIX_SIZE; i++) {
        for (int j = 0; j < BIG_MATRIX_SIZE; j++) {
            for (int k = 0; k < BIG_MATRIX_SIZE; k++) {
                auto multiplication = multiply_matrices(matrix1[i][k], matrix2[k][j]);
                sum_small_matrices(result_big_matrix[i][j], multiplication);
            }
        }
    }
    return result_big_matrix;
}

SmallMatrix multiply_matrices_manually(SmallMatrix &matrix1, SmallMatrix &matrix2) {

    SmallMatrix small_matrix_result(NEW_SMALL_MATRIX);

    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {

            auto vec1 = _mm256_set1_ps(matrix1[i][j]);

            for (int k = 0; k < MATRIX_SIZE; k += 8) {

                auto va = _mm256_loadu_ps(&matrix1[i][k]);
                auto vb = _mm256_loadu_ps(&matrix2[k][j]);
                auto vtemp = _mm256_mul_ps(va, vb);
                auto vhi = _mm256_extractf128_ps(vtemp, 1);

                auto vres = _mm_add_ps(_mm256_castps256_ps128(vtemp), vhi);
                vres = _mm_hadd_ps(vres, vres);
                vres = _mm_hadd_ps(vres, vres);

                small_matrix_result[i][j] += _mm_cvtss_f32(vres);
            }
        }
    }
    return small_matrix_result;
}

BigMatrix calculate_manually(BigMatrix &matrix1, BigMatrix &matrix2) {

    BigMatrix result_big_matrix(NEW_BIG_MATRIX);

    for (int i = 0; i < BIG_MATRIX_SIZE; i++) {
        for (int j = 0; j < BIG_MATRIX_SIZE; j++) {
            for (int k = 0; k < BIG_MATRIX_SIZE; k++) {
                auto multiplication = multiply_matrices_manually(matrix1[i][k], matrix2[k][j]);
                sum_small_matrices(result_big_matrix[i][j], multiplication);
            }
        }
    }
    return result_big_matrix;
}

bool compare(BigMatrix &big_matrix1, BigMatrix &big_matrix2) {

    for (int i = 0; i < BIG_MATRIX_SIZE; i++) {
        for (int j = 0; j < BIG_MATRIX_SIZE; j++) {
            for (int k = 0; k < MATRIX_SIZE; k++) {
                for (int m = 0; m < MATRIX_SIZE; m++) {
                    auto e1 = big_matrix1[i][j][k][m], e2 = big_matrix2[i][j][k][m];
                    if (abs(e1 - e2) > 0.0001) {
                        cout << "Matrix not equal!" << endl;
                        return false;
                    }
                }
            }
        }
    }
    cout << "Matrix equal" << endl;
    return true;
}


int main() {

    using namespace chrono;

    BigMatrix big_matrix1(BIG_MATRIX_SIZE, {BIG_MATRIX_SIZE, {MATRIX_SIZE, std::vector<float>(MATRIX_SIZE)}});
    BigMatrix big_matrix2(BIG_MATRIX_SIZE, {BIG_MATRIX_SIZE, {MATRIX_SIZE, std::vector<float>(MATRIX_SIZE)}});

    randomize_one_matrix(big_matrix1);
    randomize_one_matrix(big_matrix2);

    auto start = steady_clock::now();
    auto big_result_avx = calculate_avx(big_matrix1, big_matrix2);
    auto time = duration_cast<milliseconds>(steady_clock::now() - start).count();
    cout << "With AVX took me " << time << " milliseconds." << endl;


    start = steady_clock::now();
    auto big_result = calculate(big_matrix1, big_matrix2);
    time = duration_cast<milliseconds>(steady_clock::now() - start).count();
    cout << "Without AVX took me " << time << " milliseconds." << endl;
    compare(big_result, big_result_avx);


    start = steady_clock::now();
    auto big_result_manually = calculate_manually(big_matrix1, big_matrix2);
    time = duration_cast<milliseconds>(steady_clock::now() - start).count();
    cout << "With manually AVX took me " << time << " milliseconds." << endl;
    compare(big_result, big_result_avx);


    return 0;
}
=======
#include <iostream>
#include <random>
#include <vector>

// AVX/AVX2
#include <immintrin.h>
#include <chrono>

using namespace std;

#define MATRIX_SIZE 10
#define BIG_MATRIX_SIZE 100

using SmallMatrix = vector<vector<double>>;
using BigMatrix = vector<vector<SmallMatrix>>;

#define NEW_BIG_MATRIX BIG_MATRIX_SIZE, {BIG_MATRIX_SIZE, {MATRIX_SIZE, std::vector<double>(MATRIX_SIZE)}}
#define NEW_SMALL_MATRIX MATRIX_SIZE, {std::vector<double>(MATRIX_SIZE)}

void randomize_one_matrix(BigMatrix &matrix) {

    random_device device;
    mt19937 generator{device()};
    uniform_real_distribution<double> distribution(0.0, 1.0);

    for (auto &i: matrix)
        for (auto &j: i)
            for (auto &k: j)
                for (auto &l: k)
                    l = distribution(generator);
}

void sum_small_matrices(SmallMatrix &matrix1, const SmallMatrix &matrix2) {

    for (int i = 0; i < MATRIX_SIZE; i++)
        for (int j = 0; j < MATRIX_SIZE; j++)
            matrix1[i][j] += matrix2[i][j];
}


__attribute__((target("sse")))
SmallMatrix multiply_matrices_avx(SmallMatrix &matrix1, SmallMatrix &matrix2) {

    SmallMatrix small_matrix_result(NEW_SMALL_MATRIX);

    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            for (int k = 0; k < MATRIX_SIZE; k++) {
                small_matrix_result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    return small_matrix_result;
}

__attribute__((target("sse,avx")))
BigMatrix calculate_avx(BigMatrix &matrix1, BigMatrix &matrix2) {

    BigMatrix result_big_matrix(NEW_BIG_MATRIX);

    for (int i = 0; i < BIG_MATRIX_SIZE; i++) {
        for (int k = 0; k < BIG_MATRIX_SIZE; k++) {
            for (int j = 0; j < BIG_MATRIX_SIZE; j++) {
                auto multiplication = multiply_matrices_avx(matrix1[i][k], matrix2[k][j]);
                sum_small_matrices(result_big_matrix[i][j], multiplication);
            }
        }
    }
    return result_big_matrix;
}

__attribute__((target("no-sse")))
SmallMatrix multiply_matrices(SmallMatrix &matrix1, SmallMatrix &matrix2) {

    SmallMatrix small_matrix_result(NEW_SMALL_MATRIX);

    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            for (int k = 0; k < MATRIX_SIZE; k++) {
                small_matrix_result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    return small_matrix_result;
}

BigMatrix calculate(BigMatrix &matrix1, BigMatrix &matrix2) {

    BigMatrix result_big_matrix(NEW_BIG_MATRIX);

    for (int i = 0; i < BIG_MATRIX_SIZE; i++) {
        for (int j = 0; j < BIG_MATRIX_SIZE; j++) {
            for (int k = 0; k < BIG_MATRIX_SIZE; k++) {
                auto multiplication = multiply_matrices(matrix1[i][k], matrix2[k][j]);
                sum_small_matrices(result_big_matrix[i][j], multiplication);
            }
        }
    }
    return result_big_matrix;
}

__attribute__((target("avx,sse")))
SmallMatrix multiply_matrices_manually_reverse(SmallMatrix &matrix1, SmallMatrix &matrix2) {

    SmallMatrix small_matrix_result(NEW_SMALL_MATRIX);

    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            __m128d result{};
            for (int k = 0; k < MATRIX_SIZE - 2; k += 4) {

                auto va = _mm256_loadu_pd(&matrix1[i][k]);
                auto vb = _mm256_setr_pd(matrix2[k][j],
                                         matrix2[k + 1][j],
                                         matrix2[k + 2][j],
                                         matrix2[k + 3][j]);

                auto mul = va * vb;

                auto high = _mm256_extractf128_pd(mul, 1);
                auto low = _mm256_extractf128_pd(mul, 0);
                result += high + low;
            }

            auto va = _mm_loadu_pd(&matrix1[i][8]);
            auto vb = _mm_setr_pd(matrix2[8][j], matrix2[9][j]);
            result += va * vb;

            auto res4 = _mm_hadd_pd(result, result);

            // Get first vector
            small_matrix_result[i][j] += _mm_cvtsd_f64(res4);
        }
    }

    return small_matrix_result;
}

BigMatrix calculate_manually_reverse(BigMatrix &matrix1, BigMatrix &matrix2) {

    BigMatrix result_big_matrix(NEW_BIG_MATRIX);

    for (int i = 0; i < BIG_MATRIX_SIZE; i++) {
        for (int j = 0; j < BIG_MATRIX_SIZE; j++) {
            for (int k = 0; k < BIG_MATRIX_SIZE; k++) {
                auto multiplication = multiply_matrices_manually_reverse(matrix1[i][k], matrix2[k][j]);
                sum_small_matrices(result_big_matrix[i][j], multiplication);
            }
        }
    }
    return result_big_matrix;
}


__attribute__((target("avx,sse")))
SmallMatrix multiply_matrices_manually(SmallMatrix &matrix1, SmallMatrix &matrix2) {

    SmallMatrix small_matrix_result(NEW_SMALL_MATRIX);

    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            __m128d result{};
            for (int k = 0; k < MATRIX_SIZE - 2; k += 4) {

                auto va = _mm256_loadu_pd(&matrix1[i][k]);
                auto vb = _mm256_set_pd(matrix2[k + 3][j],
                                         matrix2[k + 2][j],
                                         matrix2[k + 1][j],
                                         matrix2[k][j]);

                auto mul = va * vb;

                auto high = _mm256_extractf128_pd(mul, 1);
                auto low = _mm256_extractf128_pd(mul, 0);
                result += high + low;
            }

            auto va = _mm_loadu_pd(&matrix1[i][8]);
            auto vb = _mm_set_pd(matrix2[9][j], matrix2[8][j]);
            result += va * vb;

            auto res4 = _mm_hadd_pd(result, result);

            // Get first vector
            small_matrix_result[i][j] += _mm_cvtsd_f64(res4);
        }
    }

    return small_matrix_result;
}

BigMatrix calculate_manually(BigMatrix &matrix1, BigMatrix &matrix2) {

    BigMatrix result_big_matrix(NEW_BIG_MATRIX);

    for (int i = 0; i < BIG_MATRIX_SIZE; i++) {
        for (int j = 0; j < BIG_MATRIX_SIZE; j++) {
            for (int k = 0; k < BIG_MATRIX_SIZE; k++) {
                auto multiplication = multiply_matrices_manually(matrix1[i][k], matrix2[k][j]);
                sum_small_matrices(result_big_matrix[i][j], multiplication);
            }
        }
    }
    return result_big_matrix;
}


bool compare(BigMatrix &big_matrix1, BigMatrix &big_matrix2) {

    for (int i = 0; i < BIG_MATRIX_SIZE; i++) {
        for (int j = 0; j < BIG_MATRIX_SIZE; j++) {
            for (int k = 0; k < MATRIX_SIZE; k++) {
                for (int m = 0; m < MATRIX_SIZE; m++) {
                    auto e1 = big_matrix1[i][j][k][m], e2 = big_matrix2[i][j][k][m];

                    if (abs(e1 - e2) > 0.01) {
                        cout << "Matrix not equal!" << e1 << '-' << e2 << " Index:" << i << j << k << m << endl;
                        return false;
                    }
                }
            }
        }
    }
    cout << "Matrix equal" << endl;
    return true;
}


int main() {

    using namespace chrono;

    BigMatrix big_matrix1(NEW_BIG_MATRIX);
    BigMatrix big_matrix2(NEW_BIG_MATRIX);

    randomize_one_matrix(big_matrix1);
    randomize_one_matrix(big_matrix2);

    auto start = steady_clock::now();
//    auto big_result_avx = calculate_avx(big_matrix1, big_matrix2);
    auto time = duration_cast<milliseconds>(steady_clock::now() - start).count();


//    cout << "With AVX took me " << time << " milliseconds." << endl;
//
//
//    start = steady_clock::now();
//    auto big_result = calculate(big_matrix1, big_matrix2);
//    time = duration_cast<milliseconds>(steady_clock::now() - start).count();
//    cout << "Without AVX took me " << time << " milliseconds." << endl;
//    compare(big_result, big_result_avx);

    start = steady_clock::now();
    auto big_result_manually = calculate_manually_reverse(big_matrix1, big_matrix2);
    time = duration_cast<milliseconds>(steady_clock::now() - start).count();
    cout << "With manually AVX took me " << time << " milliseconds." << endl;


    start = steady_clock::now();
    auto big_result_manually_reverse = calculate_manually_reverse(big_matrix1, big_matrix2);
    time = duration_cast<milliseconds>(steady_clock::now() - start).count();
    cout << "With manually reversed AVX took me " << time << " milliseconds." << endl;
    compare(big_result_manually, big_result_manually_reverse);

    return 0;
}
>>>>>>> 9d4131dc0ce34988aa45749231db77cda6a9dcfd
