#include <stdio.h>
#include <limits.h>
#include <mpi.h>
#define V 6
void printSolution(int dist[V][V]) {
 printf("Shortest distances between all pairs of vertices:\n");
 for (int i = 0; i < V; i++) {
 for (int j = 0; j < V; j++) {
 if (dist[i][j] == INT_MAX)
 printf("INF\t");
 else
 printf("%d\t", dist[i][j]);
 }
 printf("\n");
 }
}
void floydWarshall(int graph[V][V]) {
 int dist[V][V];
 for (int i = 0; i < V; i++) {
 for (int j = 0; j < V; j++) {
 dist[i][j] = graph[i][j];
 }
 }
 int rank, size;
 MPI_Comm_rank(MPI_COMM_WORLD, &rank);
 MPI_Comm_size(MPI_COMM_WORLD, &size);
 for (int k = 0; k < V; k++) {
 // Use barrier for synchronization
 MPI_Barrier(MPI_COMM_WORLD);
 for (int i = rank; i < V; i += size) {
 for (int j = 0; j < V; j++) {
 if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][k] +
dist[k][j] < dist[i][j]) {
 dist[i][j] = dist[i][k] + dist[k][j];
 }
 }
 }
 // Perform parallel reduction to find the minimum dist matrix
 MPI_Allreduce(MPI_IN_PLACE, dist, V * V, MPI_INT, MPI_MIN, MPI_COMM_WORLD);
 }
 // Gather results into the root process
 if (rank == 0) {
 int recv_buffer[V][V];
  for (int p = 1; p < size; p++) {
 MPI_Recv(recv_buffer, V * V, MPI_INT, p, 0, MPI_COMM_WORLD,
MPI_STATUS_IGNORE);
 for (int i = 0; i < V; i++) {
 for (int j = 0; j < V; j++) {
 if (recv_buffer[i][j] < dist[i][j]) {
 dist[i][j] = recv_buffer[i][j];
 }
 }
 }
 }
 } else {
 MPI_Send(dist, V * V, MPI_INT, 0, 0, MPI_COMM_WORLD);
 }
 // Root process prints the result
 if (rank == 0) {
 printSolution(dist);
 }
}
int main(int argc, char *argv[]) {
 printf("Shreyash Shendkar\n 2021BCS0148\n");
 int graph[V][V] = {
 {0, 5, INT_MAX, 10, INT_MAX, INT_MAX},
 {INT_MAX, 0, 3, INT_MAX, INT_MAX, INT_MAX},
 {INT_MAX, INT_MAX, 0, 1, 8, INT_MAX},
 {INT_MAX, INT_MAX, INT_MAX, 0, 2, INT_MAX},
 {INT_MAX, INT_MAX, INT_MAX, INT_MAX, 0, INT_MAX},
 {INT_MAX, INT_MAX, INT_MAX, INT_MAX, 1, 0}
 };
 MPI_Init(&argc, &argv);
 floydWarshall(graph);
 MPI_Finalize();
 return 0;
}