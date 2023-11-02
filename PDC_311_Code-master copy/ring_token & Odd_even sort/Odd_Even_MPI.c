#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void oddEvenSort(int* array, int size) {
    int sorted = 0;
    while (!sorted) {
        sorted = 1;
        for (int i = 1; i < size-1; i += 2) {
            if (array[i] > array[i+1]) {
                int temp = array[i];
                array[i] = array[i+1];
                array[i+1] = temp;
                sorted = 0;
            }
        }
        for (int i = 0; i < size-1; i += 2) {
            if (array[i] > array[i+1]) {
                int temp = array[i];
                array[i] = array[i+1];
                array[i+1] = temp;
                sorted = 0;
            }
        }
    }
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        fprintf(stderr, "This program requires at least 2 processes.\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
	printf("------------DHIVYESH R K----------2021BCS0084--------------\n");

    int* numbers = NULL;
    int numCount;

    if (rank == 0) {
//        printf("Enter the number of elements: ");
        scanf("%d", &numCount);
        numbers = (int*)malloc(numCount * sizeof(int));
//        printf("Enter the elements: ");
        for (int i = 0; i < numCount; i++) {
            scanf("%d", &numbers[i]);
        }
    }

    MPI_Bcast(&numCount, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank != 0) {
        numbers = (int*)malloc(numCount * sizeof(int));
    }

    MPI_Bcast(numbers, numCount, MPI_INT, 0, MPI_COMM_WORLD);

    int* localNumbers = (int*)malloc((numCount / size) * sizeof(int));

    MPI_Scatter(numbers, numCount / size, MPI_INT, localNumbers, numCount / size, MPI_INT, 0, MPI_COMM_WORLD);

    oddEvenSort(localNumbers, numCount / size);

    MPI_Gather(localNumbers, numCount / size, MPI_INT, numbers, numCount / size, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        oddEvenSort(numbers, numCount);
        printf("Sorted array: ");
        for (int i = 0; i < numCount; i++) {
            printf("%d ", numbers[i]);
        }
        printf("\n");
        free(numbers);
    }

    free(localNumbers);

    MPI_Finalize();

    return 0;
}

