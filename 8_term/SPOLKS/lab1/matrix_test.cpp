#include "Matrix.hpp"
#include "mpi.h"

#include <iostream>

// Matrix sizes
#define N 10
#define X 10
#define Y 15

int main(int argc, char** argv)
{
    Matrix matrix1 { X, N };
    Matrix matrix2 { N, Y };
    Matrix result { X, Y };

    matrix1.Randomize();
    matrix2.Randomize();

    // MPI part
    int size {}, rank {};
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Barrier(MPI_COMM_WORLD);
    const auto timestamp1 = MPI_Wtime(); // Get first timestamp

    // TODO: Matrix multiplication



    if (rank == 0) {
        const auto final_time = MPI_Wtime() - timestamp1;
        std::cout << "Time: " << final_time << std::endl;
    }

    MPI_Finalize();
    return 0;
}