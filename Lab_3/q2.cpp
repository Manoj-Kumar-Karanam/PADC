//q2
#include<bits/stdc++.h>
#include<omp.h>
// #define points 100000
using namespace std;

double monteCarlo_serial(int points) {
    int circlePoints = 0;
    srand(time(0));
    
    for(int i = 0;i < (points) ;i++) {
        double randX = (double)rand() / RAND_MAX;
        double randY = (double)rand() / RAND_MAX;
        if((randX * randX) + (randY * randY) <= 1.0) circlePoints++;

    }
        return 4.0 * circlePoints / points;
}
double monteCarlo_parallel(int points) {
    int circlePoints = 0;
    srand(time(0));
    #pragma omp parallel reduction(+ : circlePoints)
    {
        #pragma omp for
        for(int i = 0;i < (points) ;i++) {
            double randX = (double)rand() / RAND_MAX;
            double randY = (double)rand() / RAND_MAX;
            if((randX * randX) + (randY * randY) <= 1.0) 
                circlePoints++;

        }
    }
        return 4.0 * circlePoints / points;
}
double monteCarlo_parallel_atomic(int points) {
    int circlePoints = 0;
    srand(time(0));
    #pragma omp parallel
    {
        #pragma omp for
        for(int i = 0;i < (points) ;i++) {
            double randX = (double)rand() / RAND_MAX;
            double randY = (double)rand() / RAND_MAX;
            if((randX * randX) + (randY * randY) <= 1.0) 
            #pragma omp atomic
                circlePoints++;

        }
    }
        return 4.0 * circlePoints / points;
}
double monteCarlo_parallel_critical(int points) {
    int circlePoints = 0;
    srand(time(0));
    #pragma omp parallel
    {
        #pragma omp for
        for(int i = 0;i < (points) ;i++) {
            double randX = (double)rand() / RAND_MAX;
            double randY = (double)rand() / RAND_MAX;
            if((randX * randX) + (randY * randY) <= 1.0) 
            #pragma omp critical
            circlePoints++;
            

        }
    }
        return 4.0 * circlePoints / points;
}

void run(int n) {
    cout << "for n :" << n << "------------------->\n";
 double s = omp_get_wtime();
    // cin >> side ;
    double result = monteCarlo_serial(n);
    double e = omp_get_wtime();
    cout << "execution time(serial) : " << e - s <<" seconds" << endl;
    cout << "Serial value: " << result << endl;
    s = omp_get_wtime();
    result = monteCarlo_parallel(n);
    e = omp_get_wtime();
    cout << "pi value for parallel(reduction):" << result << " Execution time(reduction) :" << (e - s) * 1.0e6 << " seconds\n";
    // cout << "s\n";
    s = omp_get_wtime();
    result = monteCarlo_parallel_atomic(n);
    e = omp_get_wtime();
    cout << "pi value:(atomic) " << result << " Execution time:" << (e - s)* 1.0e9 << endl;
    s = omp_get_wtime();
    result = monteCarlo_parallel_critical(n);
    e = omp_get_wtime();
    cout << "Pi value:(critical) " << result << " Execution time:" << (e - s)* 1.0e9 << endl;
    cout << "<--------------------------------------------------------------------->\n";

}

int main() {
    omp_set_num_threads(5);
    vector<int> n = {150,500,10000};
    for(int i : n) {
        run(i);
    }

}