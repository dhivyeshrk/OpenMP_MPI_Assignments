#include <mpi.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    char hostname[MPI_MAX_PROCESSOR_NAME];
    int len;
    MPI_Get_processor_name(hostname, &len);
	printf("DONE BY 2021BCS0084\n");
    printf("Hello from process %d of %d on %s\n", rank, size, hostname);

    MPI_Finalize();
    return 0;
}


