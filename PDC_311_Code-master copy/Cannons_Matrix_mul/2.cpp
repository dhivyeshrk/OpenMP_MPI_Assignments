#include <iostream>
#include <vector>
#include <chrono>
#include <mpi.h>
using namespace std;
using namespace chrono;

vector<vector<int>> generateMatrix(int size) {
    vector<vector<int>> matrix(size, vector<int>(size));
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            matrix[i][j] = rand() % 10 + 1;
        }
    }
    return matrix;
}

vector<vector<int>> multiplyMatrices(vector<vector<int>>& A, vector<vector<int>>& B) {
    int size = A.size();
    vector<vector<int>> C(size, vector<int>(size, 0));
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            for(int k = 0; k < size; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

vector<vector<int>> scatterMatrix(vector<vector<int>>& matrix, int size, int rank, int numProcesses) {
    vector<vector<int>> localMatrix(size, vector<int>(size));
    int elementsPerProcess = size * size / numProcesses;

    MPI_Scatter(matrix[0].data(), elementsPerProcess, MPI_INT, localMatrix[0].data(), elementsPerProcess, MPI_INT, 0, MPI_COMM_WORLD);

    return localMatrix;
}

vector<vector<int>> gatherMatrix(vector<vector<int>>& localMatrix, int size, int rank, int numProcesses) {
    vector<vector<int>> result(size, vector<int>(size));
    int elementsPerProcess = size * size / numProcesses;

    MPI_Gather(localMatrix[0].data(), elementsPerProcess, MPI_INT, result[0].data(), elementsPerProcess, MPI_INT, 0, MPI_COMM_WORLD);

    return result;
}

int main(int argc, char** argv) {
	cout<<"-------DHIVYESH R K---2021bcs0084---------"<<endl;
    MPI_Init(&argc, &argv);

    int rank, numProcesses;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numProcesses);

    if (rank == 0) {
        vector<int> sizes = {2, 5, 10, 50, 500, 1000}; // Add more sizes as needed

        for(int size : sizes) {
            vector<vector<int>> A = generateMatrix(size);
            vector<vector<int>> B = generateMatrix(size);

            auto start = high_resolution_clock::now();
            vector<vector<int>> C = multiplyMatrices(A, B);
            auto end = high_resolution_clock::now();

            auto duration = duration_cast<microseconds>(end - start);

            cout << "Size " << size << "x" << size << " took " << duration.count() << " microseconds";
            cout << " (" << duration.count() / 1000000.0 << " seconds)" << endl;
        }
    }

    MPI_Finalize();

    return 0;
}

