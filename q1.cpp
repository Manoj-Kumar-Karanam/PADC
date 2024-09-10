#include<iostream>
#include<omp.h>
#include<chrono>


void sequential() {
    for(int i = 0;i < 10;i++) {
        std::cout << "Hello world\n";
    }
}

void parallel() {
    #pragma omp parallel for
    
        
        
            for(int i = 0;i < 10;i++)
            {
                std::cout << "Hello world from iteration :" << i << " thread:" << omp_get_thread_num() << std::endl;
            } 
        
    
}

int main() {
    auto s = std::chrono::high_resolution_clock::now();
    sequential();
    auto e = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> dur = e - s;
    std::cout << "Execution time for sequential:" << dur.count() << std::endl;
    auto s_p = std::chrono::high_resolution_clock::now();
    parallel();
    auto e_p = std::chrono::high_resolution_clock::now();
    dur = e_p - s_p;
    std::cout << "Execution time for parallel:" << dur.count() << std::endl;

}