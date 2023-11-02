#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
  // Initialize MPI
  printf("Done by DHIVYESH R K 2021BCS0084");
  MPI_Init(&argc, &argv);

  // Get the number of processes and the rank of this process
  int size, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  // Declare the array to be scattered
  int A[4] = {10, 85, 150, 42};

  // Scatter the array to all processes
  int recv_buf[1];
  MPI_Scatter(A, 1, MPI_INT, recv_buf, 1, MPI_INT, 0, MPI_COMM_WORLD);

  // Print the received element
  printf("Process %d received element %d\n", rank, recv_buf[0]);

  // Finalize MPI
  MPI_Finalize();

  return 0;
}

