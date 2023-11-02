#include <iostream>
#include <vector>
using namespace std;
int main() {
    const int numProcesses = 4; 
    vector<int> tokenValues(numProcesses, 0); 

    cout<<"---------------DHIVYESH R K----2021CBS0084----------------\n";
    tokenValues[0] = 100;

    for (int i = 0; i < numProcesses; ++i) {
        int nextProcess = (i + 1) % numProcesses;
        tokenValues[nextProcess] = tokenValues[i];

        cout << "Process P" << i << " passed the token with value " << tokenValues[i] << " to Process P" << nextProcess << endl;
    }

    cout << "Process P0 received the token with value " << tokenValues[0] << " from Process P3\n. Program terminated." << endl;

    return 0;
}
