#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
    int rank, size, token;
	printf("DONE BY 2021BCS0084 DHIVYESH R K");
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
	printf("size : %d\n", size);
    if (size != 2) {
        fprintf(stderr, "This program requires exactly 2 processes.\n");
        MPI_Finalize();
        return 1;
    }

    if (rank == 0) {
        token = 100;

        // Sending token from process 0 to process 1
        MPI_Send(&token, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Process 0 (sender) sent token %d to Process 1 (receiver).\n", token);
    } else if (rank == 1) {
        // Receiving token at process 1 from process 0
        MPI_Recv(&token, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 1 (receiver) received token %d from Process 0 (sender).\n", token);
    }

    MPI_Finalize();
    return 0;
}

