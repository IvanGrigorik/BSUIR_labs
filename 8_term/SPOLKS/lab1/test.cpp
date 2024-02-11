#include "mpi.h"
#include <iostream>
#include <string>

int main(int argc, char** argv)
{
    int rank, size;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        // std::cout << "Hello from " << rank << "!\n";
        std::string message = "Hello from master!";
        for (size_t i = 0; i < size; i++) {
            MPI_Request sender_req;
            MPI_Isend(message.c_str(), message.length(), MPI_CHAR, i, 99, MPI_COMM_WORLD, &sender_req);
            // MPI_Send(message.c_str(), message.length(), MPI_CHAR, i, 99, MPI_COMM_WORLD);
        }
    } else {
        MPI_Request receiver_req;

        char message[20] {};
        MPI_Status status {};

        // MPI_Recv(message, 20, MPI_CHAR, 0, 99, MPI_COMM_WORLD, &status);
        MPI_Irecv(message, 20, MPI_CHAR, 0, 99, MPI_COMM_WORLD, &receiver_req);
        MPI_Wait(&receiver_req, MPI_STATUS_IGNORE);

        std::cout << message << " | Process: "
                  << rank << " Total size: " << size << "\n";
    }

    MPI_Finalize();

    return 0;
}