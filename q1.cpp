#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

void serialLuDecomposition(vector<vector<double>> &A, vector<vector<double>> &L, vector<vector<double>> &U, vector<int> &P) {
    int n = A.size();
    for (int k = 0; k < n; ++k) {
        
        for (int j = k; j < n; ++j) {
            U[k][j] = A[k][j];
        }
        for (int i = k + 1; i < n; ++i) {
            L[i][k] = A[i][k] / U[k][k];
            for (int j = k; j < n; ++j) {
                A[i][j] -= L[i][k] * U[k][j];
            }
        }
    }
}

void serialforwardSubstitution(const vector<vector<double>> &L, const vector<double> &Pb, vector<double> &y) {
    int n = L.size();
    for (int i = 0; i < n; ++i) {
        y[i] = Pb[i];
        for (int j = 0; j < i; ++j) {
            y[i] -= L[i][j] * y[j];
        }
        y[i] /= L[i][i];
    }
}

void serialbackwardSubstitution(const vector<vector<double>> &U, const vector<double> &y, vector<double> &x) {
    int n = U.size();
    for (int i = n - 1; i >= 0; --i) {
        x[i] = y[i];
        for (int j = i + 1; j < n; ++j) {
            x[i] -= U[i][j] * x[j];
        }
        x[i] /= U[i][i];  
    }
}

int main() {
    int n = 3; 
    vector<vector<double>> A = {{4, -2, 1}, {1, 1, 1}, {2, 1, 5}};
    vector<double> b = {3, 1, 2};
    
    vector<vector<double>> L(n, vector<double>(n, 0.0));
    vector<vector<double>> U(n, vector<double>(n, 0.0));
    vector<int> P(n);
    for (int i = 0; i < n; ++i) P[i] = i;

    auto start = omp_get_wtime();
    
    serialLuDecomposition(A, L, U, P);

    vector<double> Pb(n);
    for (int i = 0; i < n; ++i) Pb[i] = b[P[i]];

    vector<double> y(n);
    serialforwardSubstitution(L, Pb, y);

    vector<double> x(n);
    serialbackwardSubstitution(U, y, x);

    auto end = omp_get_wtime();

    cout << "Serial Execution Time: " << end - start << " seconds" << endl;
    cout << "Solution x: ";
    for (double xi : x) cout << xi << " ";
    cout << endl;

    return 0;
}
