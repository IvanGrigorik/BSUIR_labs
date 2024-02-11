#include "mpi.h"

#include <functional>
#include <iostream>
#include <random>
#include <source_location>

#define N 4
#define X 6
#define Y 12

void AssertMPISuccess(int expressionResult)
{
    if (expressionResult != MPI_SUCCESS) {
        const std::source_location& loc = std::source_location::current();
        std::cerr << "Assertion failed: " << std::source_location::current().file_name() << " at line " << loc.line()
                  << std::endl;
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }
}

void AllocateMatrix(int**& matrix, int n, int m)
{
    matrix = new int*[n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[m];
    }
}

void DeallocateMatrix(int**& matrix, int n)
{
    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void FillRandom(int** vec, size_t n, size_t m)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> distrib(1, 255);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            vec[i][j] = distrib(gen);
        }
    }
}

void PrintMatrix(int* const* matrix, int n, int m)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cout << matrix[i][j] << "\t"; // print the result
        }
        std::cout << std::endl;
    }
}

void CalculateSynchronized(int size, int rank, int* const* matrix1, int* const* matrix2,
    int** mat_res)
{
    int sum = 0;
    double result;
    MPI_Status status;

    for (int i = rank; i < X; i = i + size) { // divide the task in multiple processes
        for (int j = 0; j < Y; j++) {
            sum = 0;
            for (int k = 0; k < N; k++) {
                sum = sum + matrix1[i][k] * matrix2[k][j];
            }
            mat_res[i][j] = sum;
        }
    }

    if (rank != 0) {
        for (int i = rank; i < X; i = i + size)
            MPI_Send(&mat_res[i][0], Y, MPI_INT, 0, 10 + i,
                MPI_COMM_WORLD); // send calculated rows to process with rank 0
    }

    if (rank == 0) {
        for (int j = 1; j < size; j++) {
            for (int i = j; i < X; i = i + size) {
                MPI_Recv(&mat_res[i][0], Y, MPI_INT, j, 10 + i, MPI_COMM_WORLD,
                    &status); // receive calculated rows from respective process
            }
        }
    }
    MPI_Barrier(MPI_COMM_WORLD);
}

template <typename Func>
constexpr void Calculate(Func calcMethod, int size, int rank,
    int* const* matrix1, int* const* matrix2, int** mat_res)
{
    calcMethod(size, rank, matrix1, matrix2, mat_res);
}

int main(int argc, char** argv)
{
    int size, rank;

    int** matrix1;
    int** matrix2;
    int** mat_res;

    AllocateMatrix(matrix1, X, N);
    AllocateMatrix(matrix2, N, Y);
    AllocateMatrix(mat_res, X, Y);

    FillRandom(matrix1, X, N);
    FillRandom(matrix2, N, Y);

    AssertMPISuccess(MPI_Init(&argc, &argv));
    AssertMPISuccess(MPI_Comm_size(MPI_COMM_WORLD, &size));
    AssertMPISuccess(MPI_Comm_rank(MPI_COMM_WORLD, &rank));

    // BARRIER USAGE
    double t1;
    AssertMPISuccess(MPI_Barrier(MPI_COMM_WORLD));
    if (rank == 0)
        t1 = MPI_Wtime();

    Calculate(CalculateSynchronized, size, rank, matrix1, matrix2, mat_res);

    if (rank == 0) {
        const auto t2 = MPI_Wtime();
        const auto result = t2 - t1;

        PrintMatrix(mat_res, X, Y);
        std::cout << "Time taken = " << result << " seconds\n";
    }

    AssertMPISuccess(MPI_Finalize());

    DeallocateMatrix(matrix1, X);
    DeallocateMatrix(mat_res, X);
    DeallocateMatrix(matrix2, N);

    return 0;
}
