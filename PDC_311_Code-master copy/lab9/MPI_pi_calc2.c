#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv) {
  // Initialize MPI
  MPI_Init(&argc, &argv);

  // Get the number of processes and the rank of this process
  int size, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	printf("Dhivyesh R K 2021BCS0084 \n");
  // Start timer
  double start_time = MPI_Wtime();

  // Estimate PI using the Monte Carlo method
  int num_iterations = 10000000;
  int num_in_circle = 0;
  for (int i = 0; i < num_iterations; i++) {
    // Generate random points in a square with side length 2
    double x = (2.0 * rand()) / RAND_MAX - 1.0;
    double y = (2.0 * rand()) / RAND_MAX - 1.0;

    // Check if the point is inside the circle
    if (x * x + y * y <= 1.0) {
      num_in_circle++;
    }
  }

  // Calculate the estimated value of PI
  double estimated_pi = 4.0 * num_in_circle / num_iterations;

  // Send the estimated value of PI to the root process
  if (rank != 0) {
    MPI_Send(&estimated_pi, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
  }

  // Collect the estimated values of PI from all processes on the root process
  if (rank == 0) {
    double global_estimated_pi = 0.0;
    for (int i = 1; i < size; i++) {
      double recv_estimated_pi;
      MPI_Recv(&recv_estimated_pi, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      global_estimated_pi += recv_estimated_pi;
    }

    // Calculate the final estimated value of PI
    global_estimated_pi = (global_estimated_pi + estimated_pi) / size;

    // Stop timer
    double end_time = MPI_Wtime();

    // Calculate the execution time
    double execution_time = end_time - start_time;

    // Print the final estimated value of PI and the execution time
    printf("Estimated value of PI: %.10f\n", global_estimated_pi);
    printf("Execution time: %.10f seconds\n", execution_time);
  }

  // Finalize MPI
  MPI_Finalize();

  return 0;
}

