#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>

using namespace std;

void gaussianEliminationSerial(vector<vector<double>>& A) {
    int n = A.size();

    for (int i = 0; i < n; i++) {
        int maxRow = i;
        for (int k = i + 1; k < n; k++) {
            if (abs(A[k][i]) > abs(A[maxRow][i]))
                maxRow = k;
        }
        swap(A[i], A[maxRow]);

        for (int k = i + 1; k < n; k++) {
            double factor = A[k][i] / A[i][i];
            for (int j = i; j <= n; j++) {
                A[k][j] -= factor * A[i][j];
            }
        }
    }
}


vector<double> backSubstitution(vector<vector<double>>& A) {
    int n = A.size();
    vector<double> x(n);

    for (int i = n - 1; i >= 0; i--) {
        x[i] = A[i][n] / A[i][i];
        for (int k = i - 1; k >= 0; k--) {
            A[k][n] -= (A[k][i] * x[i]);
        }
    }

    return x;
}

int main() {
    cout<< "Done by DHIVYESH RK 2021bcs0084"<<endl;
    int n;
    cout << "Enter the number of equations: ";
    cin >> n;

    vector<vector<double>> A(n, vector<double>(n + 1));

    cout << "Enter the coefficients of the system:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            cin >> A[i][j];
        }
    }

    // Serial Version
    auto startSerial = chrono::high_resolution_clock::now();
    gaussianEliminationSerial(A);
    vector<double> solutionSerial = backSubstitution(A);
    auto endSerial = chrono::high_resolution_clock::now();
    chrono::duration<double> durationSerial = endSerial - startSerial;
    double executionTimeSerial = durationSerial.count();

    // Output results
    cout << "Serial Version:" << endl;
    cout << "Solution: ";
    for (double val : solutionSerial) {
        cout << val << " ";
    }
    cout << endl;
    cout << "Execution Time: " << executionTimeSerial << " seconds" << endl;

    return 0;
}

