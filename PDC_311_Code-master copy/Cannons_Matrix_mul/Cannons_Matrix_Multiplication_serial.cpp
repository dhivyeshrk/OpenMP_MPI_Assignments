#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
using namespace chrono;

// Function to generate a random matrix of size NxN
vector<vector<int>> generateMatrix(int size) {
    vector<vector<int>> matrix(size, vector<int>(size));
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            matrix[i][j] = rand() % 10 + 1; // Random elements between 1 and 10
        }
    }
    return matrix;
}

// Function to multiply two matrices
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

int main() {
    vector<int> sizes = {2, 5, 10, 50, 500, 1000}; 
	cout<<"---------DHIVYESH R K--2021BCS0084---------------"<<endl;
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

    return 0;
}

