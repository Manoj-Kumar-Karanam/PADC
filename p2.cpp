#include<bits/stdc++.h>

using namespace std;

double determinant(int n,vector<vector<double>> &a) {
    double det = 1.0;
    for (int i = 0; i < n; i++) {
        int pivot = i;
        for (int j = i + 1; j < n; j++) {
            if (abs(a[j][i]) > abs(a[pivot][i])) {
                pivot = j;
            }
        }
        if (pivot != i) {
            swap(a[i], a[pivot]);
            det *= -1;
        }
        if (a[i][i] == 0) {
            return 0;
        }
        det *= a[i][i];
        for (int j = i + 1; j < n; j++) {
            double factor = a[j][i] / a[i][i];
            for (int k = i + 1; k < n; k++) {
                a[j][k] -= factor * a[i][k];
            }
        }
    }
    return det;
}

// void co_factor(int n,vector<vector<int>> &mat,vector<vector<double>> &a) {

// }

void print(vector<vector<double>> &a,int n) {
    for(size_t i = 0;i < n; ++i) {
        for(size_t j = 0;j < n;++j) {
            cout << a[i][j] << " ";
        }
        cout << "\n";
    }
}

int main() {
    vector<vector<int>> mat = {{1,2,3}, {7,4,5}, {6,8,9}};
    int n = mat.size();
    vector<vector<double>> a(n , vector<double>(n));
    for(int i = 0;i < n;++i) {
        for(int j = 0;j < n;++j) {
            a[i][j] = mat[i][j];
        }
    }
    cout << determinant(n , a) << "\n";
    print(a,n);
    return 0;
}