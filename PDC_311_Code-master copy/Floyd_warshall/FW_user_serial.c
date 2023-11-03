#include <stdio.h>
#include <limits.h>

// Define the maximum number of vertices in the graph
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
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    printSolution(dist);
}

int main() {
    printf("Kanak Khandelwal 2021BCS0102\n");
    printf("Enter the adjacency matrix for the graph (%dx%d):\n", V, V);
    int graph[V][V];

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            scanf("%d", &graph[i][j]);
            if (i == j) {
                // Diagonal elements should be 0 (no self-loops)
                graph[i][j] = 0;
            }
            if (graph[i][j] == -1) {
                // If the user enters -1, consider it as infinity (INT_MAX)
                graph[i][j] = INT_MAX;
            }
        }
    }

    floydWarshall(graph);

    return 0;
}
