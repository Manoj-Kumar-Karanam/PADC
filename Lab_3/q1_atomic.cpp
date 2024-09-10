#include<iostream>
#include<vector>
#include<omp.h>

using namespace std;

double estimatePi_parallel_atomic(int n) {
    double width = 1.0 / n;
    double area = 0.0;

    #pragma omp parallel 
    {
        double localArea = 0.0;
        
        #pragma omp for
        for (int i = 0; i < n; i++) {
            double mid = (i + 0.5) * width;
            double height = 4.0 / (1 + (mid * mid));
            localArea += height * width;
        }

        

        #pragma omp atomic
        area += localArea;
         
        
    }
    
    return area;
}
double estimatePi_parallel_reduction(int n) {
    double width = 1.0 / n;
    double area = 0.0;

    #pragma omp parallel for reduction(+ : area)
    for (int i = 0; i < n; i++) {
        double mid = (i + 0.5) * width;
        double height = 4.0 / (1 + (mid * mid));
        area += height * width;
    }

    return area;
}


int main() {
    vector<int> n = {10,50,100,500,1000};
    for(int i : n) {
        cout << "for n : " << i << "\n";
        double s = omp_get_wtime();
        double res = estimatePi_parallel_reduction(i);
        double e = omp_get_wtime();
        cout << "execution time " << (e - s ) << " seconds\n";
        cout << "______________________________\n";
    }
}