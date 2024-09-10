#define _USE_MATH_DEFINES
#include<bits/stdc++.h>
#include<omp.h>

using namespace std;

double estimatePi_serial(int n) {
    double width = 1.0 / n;
    double area = 0.0;

    for (int i = 0; i < n; i++) {
        double mid = (i + 0.5) * width;
        double height = 4.0 / (1 + (mid * mid));
        area += height * width;
    }

    return area;
}

double estimatePi_serial_leftEndPoint(int n) {
    double width = 1.0 / n;
    double area = 0.0;

    for (int i = 0; i < n; i++) {
        double x = i * width;
        double height = 4.0 / (1 + (x * x));
        area += height * width;
    }

    return area;
}
double estimatePi_serial_rightEndPoint(int n) {
    double width = 1.0 / n;
    double area = 0.0;

    for (int i = 0; i < n; i++) {
        double x = (i + 1) * width;
        double height = 4.0 / (1 + (x * x));
        area += height * width;
    }

    return area;
}
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
double estimatePi_parallel_critical(int n) {
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

        #pragma omp critical
        {
            area += localArea;
          cout << "Thread " << omp_get_thread_num() << " calculated localArea: " << localArea << endl;
            
        }

        
         
        
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

void run(int n) {
    cout << "############ " << "For n :" << n << " ##################\n";
    omp_set_num_threads(5);
    // double PI = 3.141414141;
    double s = omp_get_wtime();
    double area = estimatePi_serial(n);
    double e = omp_get_wtime();
    cout << "Value of pi (serial): " << area << endl;
    cout << "Execution time (serial): " << (e - s) << " micro seconds" << endl;
    double area_left = estimatePi_serial_leftEndPoint(n);
    cout << "value of pi with left most point :" << area_left << endl;
    double right_area = estimatePi_serial_rightEndPoint(n);
    cout << "Pi value(right end point) :" << right_area << endl;
    cout << "error value with mid point :" << abs( M_PI - area) << endl;
    cout << "error value with left :" <<abs(area_left - M_PI) << endl;
    cout << "error value with right :" << abs(M_PI - right_area) << endl;

 
    s = omp_get_wtime();
    area = estimatePi_parallel_atomic(n);
    e = omp_get_wtime();
    cout << "Value of pi (parallel with atomic): " << area << endl;
    cout << "Execution time (parallel with atomic): " << (e - s) << " micro seconds" << endl;
    s = omp_get_wtime();
    area = estimatePi_parallel_critical(n);
    e = omp_get_wtime();
    cout << "Value of pi (parallel with critical): " << area << endl;
    cout << "Execution time (parallel with critical): " << (e - s) << " micro seconds" << endl;
    s = omp_get_wtime();
    // auto st = std::chrono::high_resolution_clock::now();
    area = estimatePi_parallel_reduction(n);
    // auto end = std::chrono::high_resolution_clock::now();
    e = omp_get_wtime();
    // std::chrono::duration<double> d = end - st;
    cout << "Value of pi (parallel with reduction): " << area << endl;
    cout << "Execution time (parallel with reduction): " << e - s << " micro seconds" << endl;
    cout << "<--------------------------------------------------------------------->\n";
    cout << "\n";
}


int main() {
    vector<int> n = {10, 50, 100, 500, 1000};
    for(int num : n) {
        run(num);
    }
    return 0;
}
