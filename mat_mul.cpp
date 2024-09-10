#include<bits/stdc++.h>


using namespace std;



void print(std::vector<std::vector<int>> arr) {
    int row = arr.size() ,column = arr[0].size();
    for(int i = 0;i < row;i++) {
        for(int j = 0;j < column;j++) {
            std::cout << arr[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void p_matmul(std::vector<std::vector<int>> &arr1,std::vector<std::vector<int>> &arr2,std::vector<std::vector<int>> &result,size_t dim) {
    #pragma omp parallel for collapse(3) shared(result)
    for(size_t i = 0;i < dim;i++) {
        for(size_t j = 0;j < dim;j++) {
            result[i][j] = 0;
            for(size_t k = 0;k < dim;k++) {

                result[i][j] += arr1[i][k] * arr2[k][j];
            }
        }
    }
}
void matmul(std::vector<std::vector<int>> &arr1,std::vector<std::vector<int>> &arr2,std::vector<std::vector<int>> &result,size_t dim) {
    
    for(size_t i = 0;i < dim;i++) {
        for(size_t j = 0;j < dim;j++) {
            result[i][j] = 0;
            for(size_t k = 0;k < dim;k++) {

                result[i][j] += arr1[i][k] * arr2[k][j];
            }
        }
    }
}

void fillMatrix(vector<vector<int>> &arr,size_t dimension) {
    std::random_device rd;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> uni(0, 100);
    for(int i = 0;i < dimension;i++) {
        for(int j = 0;j < dimension;j++) {
            arr[i][j] = uni(gen);
        }
    }
}

void run(const size_t &dim) {
   
 std::vector<std::vector<int>> arr1 (dim,std::vector<int>(dim));
    std::vector<std::vector<int>> arr2 (dim,std::vector<int>(dim));
    std::vector<std::vector<int>> result(dim,std::vector<int>(dim));
    fillMatrix(arr1,dim);
    fillMatrix(arr2,dim);
    auto start = std::chrono::high_resolution_clock::now();
    matmul(arr1,arr2,result,dim);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
   
    auto start_p = std::chrono::high_resolution_clock::now();
    p_matmul(arr1,arr2,result,dim);
    auto end_p = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_p = end_p - start_p;
    
    std::cout << "\nExecution time for Multiplication(serial) of matrix dimension " << dim << " is :" << duration.count() ;
    std::cout << "\nExecution time for Multiplication(parallel) : of matrix dimension " << dim << "is : " << duration_p.count() ;
    
}

int main() {
    

    for(int i : {10,100,1000}) {
        run(i);
    }
   
    return 0;
}