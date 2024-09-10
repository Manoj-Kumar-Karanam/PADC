#include<bits/stdc++.h>

using namespace std;
#define THRESHOLD 50

void merge(vector<int> &arr, int left, int mid, int right) {
    int l = mid - left + 1;
    int r = right - mid;
    vector<int> left_array(l);
    vector<int> right_array(r);
    
    for (int i = 0; i < l; i++) {
        left_array[i] = arr[left + i];
    }
    for (int i = 0; i < r; i++) {
        right_array[i] = arr[mid + 1 + i];
    }
    
    int i = 0, j = 0, k = left;
    while (i < l && j < r) {
        if (left_array[i] <= right_array[j]) {
            arr[k] = left_array[i];
            i++;
        } else {
            arr[k] = right_array[j];
            j++;
        }
        k++;
    }
    
    while (i < l) {
        arr[k] = left_array[i];
        i++;
        k++;
    }
    
    while (j < r) {
        arr[k] = right_array[j];
        j++;
        k++;
    }
}
void print(vector<int>& arr) {
    std::cout << "["; 
    for (int i : arr) {
        cout << i << ", ";
    }
    std::cout << "]";
}

void mergeSort(vector<int> &arr, const int &left, const int &right) {
    if (left >= right)
        return;
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);  
}

void mergeParallelSort(vector<int> &arr, const int &left, const int &right) {
    if(left >= right) {
        return;
    }
    int mid = left + (right - left) / 2;
    if(right - left < THRESHOLD) {
        mergeSort(arr, left, right);
        return;
    }
    #pragma omp parallel 
    {
        #pragma omp single
        {
            #pragma omp taskgroup
            {
                #pragma omp task shared(arr)
                mergeParallelSort(arr, left, mid);

                #pragma omp task shared(arr)
                mergeParallelSort(arr, mid + 1, right);
            }
        }

    }
    #pragma omp taskwait
    merge(arr, left, mid,  right);
}

void fill_vector(vector<int> &arr) {
    std::random_device rd;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> uni(0, 100);
    for(int i = 0;i < arr.size();i++) {
        arr[i] = uni(gen);
    }
}

void run(const size_t &array_length) {
    vector<int> arr(array_length);
    
    fill_vector(arr);
    auto s = std::chrono::high_resolution_clock::now();
    mergeSort(arr, 0, array_length - 1);
    auto e = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> run_time = e - s;
    std::cout << "size [" << std::setw(4)<< std::left << array_length <<"] runtime for serial merge sort " << run_time.count() << "s" << std::endl;
    
    fill_vector(arr);
    auto ps = std::chrono::high_resolution_clock::now();
    mergeParallelSort(arr, 0, array_length - 1);
    auto pe = std::chrono::high_resolution_clock::now();
    run_time = pe - ps;
    std::cout << "size [" << std::setw(4) << array_length << "] runtime for parall merge sort " << run_time.count() << "s" << std::endl;

}

int main() {
    for(const auto& i : {10,100,1000}) {
        run(i);
    }
}
