#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
  // Initialize MPI
  MPI_Init(&argc, &argv);
	printf("DHIVYESH R K 2021BCS0084");
  // Get the number of processes and the rank of this process
  int size, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  // Declare the two-dimensional array to be distributed
  int B[4][4] = {{10, 20, 30, 40}, {50, 60, 70, 80}, {90, 100, 110, 120}, {130, 140, 150, 160}};

  // Create a subarray type for each row of the array
  MPI_Datatype row_type;
  int size_array[2] = {4, 4};
  int subsize_array[2] = {1, 4};

  MPI_Type_create_subarray(2, size_array, subsize_array, &(rank), MPI_ORDER_C, MPI_INT, &row_type);
  MPI_Type_commit(&row_type);

  // Scatter the rows of the array to all processes
  int recv_buf[4];
  MPI_Scatter(B, 1, row_type, recv_buf, 1, row_type, 0, MPI_COMM_WORLD);

  // Print the received row
  printf("Process %d received row: ", rank);
  for (int i = 0; i < 4; i++) {
    printf("%d ", recv_buf[i]);
  }
  printf("\n");

  // Finalize MPI
  MPI_Finalize();

  return 0;
}

