#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void shellSort(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;

            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }

            arr[j] = temp;
        }
    }
}

int main(int argc, char* argv[]) {
    int n, rank, size;
    int* arr = NULL;
    int* localArr = NULL;
    int* recvArr = NULL;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        // printf("Enter the number of elements: ");
        scanf("%d", &n);
        arr = (int*)malloc(n * sizeof(int));

        // printf("Enter the array elements: ");
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }
    }

    // Broadcast the size of the array to all processes
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int localSize = n / size;
    localArr = (int*)malloc(localSize * sizeof(int));
    recvArr = (int*)malloc(localSize * sizeof(int));

    // Scatter the array to all processes
    MPI_Scatter(arr, localSize, MPI_INT, localArr, localSize, MPI_INT, 0, MPI_COMM_WORLD);

    // Perform shell sort on the local array
    shellSort(localArr, localSize);
    // Gather the sorted local arrays back to the root process
    MPI_Gather(localArr, localSize, MPI_INT, recvArr, localSize, MPI_INT, 0, MPI_COMM_WORLD);

    // Merge the sorted arrays
    if (rank == 0) {
        shellSort(recvArr, n);

        printf("Original array: \n");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }

        printf("\nSorted array: \n");
        for (int i = 0; i < n; i++) {
            printf("%d ", recvArr[i]);
        }

        free(arr);
    }

    free(localArr);
    free(recvArr);
    MPI_Finalize();

    return 0;
}