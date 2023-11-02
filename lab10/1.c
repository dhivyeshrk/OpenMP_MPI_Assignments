#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size;
    int token;
    printf("-----------DHIVYESH R K --- 2021BCS0084--------------------\n");
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        token = 100;
        MPI_Send(&token, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Process %d sent token %d to process %d\n", rank, token, (rank + 1) % size);
    }

    while (1) {
        MPI_Recv(&token, 1, MPI_INT, (rank - 1 + size) % size, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        if (rank == 0 && token == 100) {
            printf("Token returned to process 0. Program complete.\n");
            break;
        }

        printf("Process %d received token %d from process %d\n", rank, token, (rank - 1 + size) % size);
        MPI_Send(&token, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);
        printf("Process %d sent token %d to process %d\n", rank, token, (rank + 1) % size);
        if (rank == 3) MPI_Finalize();
    }

    MPI_Finalize();
    return 0;
}

