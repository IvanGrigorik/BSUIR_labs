#include <mpi.h>

#include <source_location>

#include "Matrix.h"

template <size_t Size>
constexpr double PerformMatrixMultiplication(const Matrix<Size>& A, const Matrix<Size>& B,
    Matrix<Size>& C, const int rank,
    const int processors,
    const bool synchronous)
{
    // Calculate the range of rows to be processed by this rank
    const int from = rank * Size / processors;
    const int to = (rank + 1) * Size / processors;
    constexpr auto SizeSquare = Size * Size;

    // Measure the start time
    const auto start = MPI_Wtime();

    // Perform matrix multiplication
    if (synchronous) {
        // Synchronous mode: broadcast matrix B from process 0 and scatter matrix A to all
        // processes
        MPI_Bcast(B.PlainArray(), SizeSquare, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Scatter(A.PlainArray(), SizeSquare / processors, MPI_INT, A[from],
            SizeSquare / processors, MPI_INT, 0, MPI_COMM_WORLD);
    } else {
        // Asynchronous mode: non-blocking broadcast of matrix B and scatter of matrix A
        MPI_Request request[2];
        MPI_Status status[2];

        MPI_Ibcast(B.PlainArray(), SizeSquare, MPI_INT, 0, MPI_COMM_WORLD, &request[0]);
        MPI_Iscatter(A.PlainArray(), SizeSquare / processors, MPI_INT, A[from],
            SizeSquare / processors, MPI_INT, 0, MPI_COMM_WORLD,
            &request[1]);

        // Wait for the communication operations to complete
        MPI_Waitall(2, request, status);
    }

    // Perform the actual matrix multiplication for the assigned rows
    for (int i = from; i < to; i++) {
        for (size_t j = 0; j < Size; j++) {
            C[i][j] = 0;
            for (size_t k = 0; k < Size; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    // Gather the results from all processes to process 0
    MPI_Gather(C.PlainArray()[from], SizeSquare / processors, MPI_INT,
        C.PlainArray(), SizeSquare / processors, MPI_INT, 0,
        MPI_COMM_WORLD);

    double totalTime = 0.0;
    // Measure the total time and print the result only in process 0
    if (rank == 0) {
        totalTime = MPI_Wtime() - start;
        std::cout << "Result:\n";
        // C.Print();
    }

    return totalTime;
}

int main(int argc, char* argv[])
{
    constexpr auto MATRIX_SIZE = 300;

    Matrix<MATRIX_SIZE> A {};
    Matrix<MATRIX_SIZE> B {};
    Matrix<MATRIX_SIZE> C_sync {};
    Matrix<MATRIX_SIZE> C_async {};

    A.Randomize();
    B.Randomize();

    int rank {}, size {};

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); /* who am i */
    MPI_Comm_size(MPI_COMM_WORLD, &size); /* number of processors */

    if (rank == 0) {
        // std::cout << "A:\n";
        // A.Print();
        // std::cout << "B:\n";
        // B.Print();
    }

    // Check if matrix size is divisible by the number of processes
    if (MATRIX_SIZE % size != 0) {
        if (rank == 0)
            std::cout << "Matrix size not divisible by number of size\n";
        MPI_Finalize();
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    // Calculate synchronized matrix multiplication
    double timeSync = PerformMatrixMultiplication(A, B, C_sync, rank, size, true);

    // Calculate asynchronous matrix multiplication
    double timeAsync = PerformMatrixMultiplication(A, B, C_async, rank, size, false);

    MPI_Finalize();

    // Print the total time and comparison result
    if (rank == 0) {
        std::cout << "\nTotal time (CalculateSynchronized): " << std::fixed
                  << std::setprecision(6) << timeSync << " (sec)\n";
        std::cout << "Total time (CalculateAsynchronous): " << std::fixed
                  << std::setprecision(6) << timeAsync << " (sec)\n";

        const auto equal = C_sync == C_async;
        std::cout << "Matrices equal: " << std::boolalpha << equal << std::noboolalpha
                  << "\n\n";

        const auto syncToAsyncTimeCoefficient = timeSync / timeAsync;
        std::cout << "Sync mode is slower then Async by " << syncToAsyncTimeCoefficient
                  << " times\n";
    }

    return 0;
}
