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

void floydWarshall(int graph[V][V], int rank, int size) {
    int dist[V][V];
    
    // Initialize the dist matrix with the same values as the graph matrix
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            dist[i][j] = graph[i][j];
        }
    }
    
    for (int k = 0; k < V; k++) {
        // Broadcast the dist matrix to all processes
        MPI_Bcast(dist, V * V, MPI_INT, 0, MPI_COMM_WORLD);
        
        for (int i = rank; i < V; i += size) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    
    // Gather results into the root process
    if (rank == 0) {
        int recv_buffer[V][V];
        for (int p = 1; p < size; p++) {
            MPI_Recv(recv_buffer, V * V, MPI_INT, p, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
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
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    printf("Kanak Khandelwal 2021BCS0102\n");
    printf("Enter the adjacency matrix for the graph (%dx%d):\n", V, V);
    int graph[V][V];
    
    if (rank == 0) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                scanf("%d", &graph[i][j]);
                if (i == j) {
                    graph[i][j] = 0;
                }
                if (graph[i][j] == -1) {
                    graph[i][j] = INT_MAX;
                }
            }
        }
    }
    
    floydWarshall(graph, rank, size);
    
    MPI_Finalize();
    return 0;
}
