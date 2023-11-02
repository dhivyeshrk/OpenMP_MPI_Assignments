#include <stdio.h>
#include <limits.h>
// Define the number of vertices in the graph
#define V 6
// Function to print the solution matrix
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
// Implementation of the Floyd-Warshall algorithm
void floydWarshall(int graph[V][V]) {
 int dist[V][V];


 // Initialize the dist matrix with the same values as the graph matrix
 for (int i = 0; i < V; i++) {
 for (int j = 0; j < V; j++) {
 dist[i][j] = graph[i][j];
 }
 }


// Apply the Floyd-Warshall algorithm
 for (int k = 0; k < V; k++) {
 for (int i = 0; i < V; i++) {
 for (int j = 0; j < V; j++) {
 if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][k] +
dist[k][j] < dist[i][j]) {
 dist[i][j] = dist[i][k] + dist[k][j];
 }
 }
 }
 }


 printSolution(dist);
}
int main() {
 printf("Shreyash Shendkar\n 2021BCS0148\n");
 int graph[V][V] = {
 {0, 5, INT_MAX, 10, INT_MAX, INT_MAX},
 {INT_MAX, 0, 3, INT_MAX, INT_MAX, INT_MAX},
 {INT_MAX, INT_MAX, 0, 1, 8, INT_MAX},
 {INT_MAX, INT_MAX, INT_MAX, 0, 2, INT_MAX},
 {INT_MAX, INT_MAX, INT_MAX, INT_MAX, 0, INT_MAX},
 {INT_MAX, INT_MAX, INT_MAX, INT_MAX, 1, 0}
 };
 floydWarshall(graph);
 return 0;
}