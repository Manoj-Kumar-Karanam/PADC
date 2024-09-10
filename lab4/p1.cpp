#include <bits/stdc++.h>
#include <omp.h>

using namespace std;

void takeInputs(vector<vector<double>> &q,int n,int m) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j <= m; j++) {
            q[i][j] = rand() % 10;
        }
    }
}

vector<vector<double>> pivot(vector<vector<double>>& q, int r1, int r2, int a) {
    double r = q[r2][a];
    #pragma omp parallel for
    for(int i = 0; i < q[r2].size(); i++) {
        
        
            // cout << "Thread " << omp_get_thread_num() << " reducing row " << r2 << endl;
            q[r2][i] /= r;
     
    }

    double p = q[r1][a];
     #pragma omp parallel for
    for (int i = 0; i < q[r2].size(); i++) {
        int thread_id = omp_get_thread_num();  
        #pragma omp critical
        {
            // cout << "Thread " << thread_id << " is reducing row " << r1 << endl;
        }
        q[r1][i] -= q[r2][i] * p;
    }

    return q;
}
vector<vector<double>> s_pivot(vector<vector<double>>& q, int r1, int r2, int a) {
    double r = q[r2][a];
    for(int i = 0; i < q[r2].size(); i++) {
        q[r2][i] /= r;
    }

    double p = q[r1][a];
    for(int i = 0; i < q[r2].size(); i++) {
        q[r1][i] -= q[r2][i] * p;
    }

    return q;
}

vector<double> b_substitution(const vector<vector<double>>& q, int n) {
    vector<double> result(n, 0);
    for (int i = n - 1; i >= 0; --i) {
        double s = 0;
        #pragma omp parallel for reduction(+:s)
        for (int j = i + 1; j < n; ++j) {
            s += result[j] * q[i][j];
        }
        result[i] = (q[i][n] - s) / q[i][i];
    }
    return result;
}
vector<double> s_b_substitution(const vector<vector<double>>& q, int n) {
    vector<double> result(n, 0);
    for (int i = n - 1; i >= 0; --i) {
        double s = 0;
        for (int j = i + 1; j < n; ++j) {
            s += result[j] * q[i][j];
        }
        result[i] = (q[i][n] - s) / q[i][i];
    }
    return result;
}

void printMatrix(vector<vector<double>> &q) 
{
    for(auto &vec : q) {
        for(int i : vec) {
            cout << i << " ";
        }
        cout << "\n";
    }
}



void run(int n,vector<vector<double>> &q){
    printMatrix(q);
    auto s = omp_get_wtime();
    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            {
                q = pivot(q, j, i, i);

            }
        }
    }
    vector<double> result = b_substitution(q, n);

    auto e = omp_get_wtime();
    // for(int i = 0; i < result.size(); i++) {
    //     cout << result[i] << " ";
    // }
    cout << endl;
    cout << "Execution time (parallel) : " << e - s << endl;
    s = omp_get_wtime();
    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            {
            // cout << "Thread " << omp_get_thread_num() << " reducing row " << j << endl;
            q = s_pivot(q, j, i, i);

            }
        }
    }
    vector<double> result_s = s_b_substitution(q, n);
    cout << "\nSolution Vector :" << endl;
    for(int i = 0; i < result.size(); i++) {
        cout << result_s[i] << ", ";
    }
    cout << endl;
    e = omp_get_wtime();
    cout << "\nExecution time (serial) : " << e - s << endl;


}


int main() {
    int n, m;
    cin >> n >> m;
    omp_set_num_threads(3);

    vector<vector<double>> q(n, vector<double>(m + 1));

    takeInputs(q,n,m);
    auto s=omp_get_wtime();
    run(n,q);
    auto e=omp_get_wtime();
    
    return 0;
}
