#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
    int rank, size;
    int a = 10, b = 4, c;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

	printf("Dhivyesh R K 2021BCS0084 \n");
    MPI_Bcast(&a, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&b, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        // Process 0 computes c = a + b
        c = a + b;
        printf("At process 0, %d + %d is %d\n",a, b, c);
    } else if (rank == 1) {
        // Process 1 computes c = a - b
        c = a - b;
                printf("At process 1, %d - %d is %d\n",a,b, c);
    } else {
        // Processes > 1 compute c = a * b
        c = a * b;
                printf("At process 2, %d * %d is %d\n",a,b, c);
    }

    // Send c to process 0
    if (rank != 0) {
        MPI_Send(&c, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    } 
    else {
        // Process 0 receives c from others
        for (int i = 1; i < size; i++) {
            MPI_Recv(&c, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        
        printf("Result at process 0: %d\n", c);
    }

    MPI_Finalize();
    return 0;
}

