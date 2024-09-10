#include<bits/stdc++.h>

using namespace std;

int partition (vector<int>& arr,int left,int right) {
    int piv = arr[right];
    int l = left - 1;

    for(int i = left;i < right;i++) {
        if(arr[i] < piv) {
            l++;
            swap(arr[l],arr[i]);
        }
    }
    swap(arr[l + 1],arr[right]);
    return l + 1;
}

void quick(vector<int>& arr,int left,int right) {
    if(left < right) {
        int pivot = partition(arr,left,right);
        quick(arr,left,pivot - 1);
        quick(arr,pivot + 1,right);
    }
}

void print(vector<int>& arr) {
    std::cout << "["; 
    for (int i : arr) {
        cout << i << ", ";
    }
    std::cout << "]";
}

void p_quick(vector<int>& arr,int left,int right) {
        if (left < right) {
        int pivot = partition(arr, left, right);

        // Parallelize recursive calls if the partition is large enough
        #pragma omp parallel sections if(right - left > 50) // Limit small partitions from spawning too many threads
        {
            #pragma omp section
            {
                p_quick(arr, left, pivot - 1);
            }
            #pragma omp section
            {
                p_quick(arr, pivot + 1, right);
            }
        }
    }
}

void randomize(vector<int> &arr) {
    std::random_device rd;
    int n = arr.size();
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> uni(INT16_MIN, INT16_MAX);
    for(int i = 0;i < n;i++) {
        arr[i] = uni(gen);
    }
}

void run(const size_t &length) {
    vector<int> arr(length);

    randomize(arr);
    auto start = std::chrono::high_resolution_clock::now();
    quick(arr,0,arr.size() - 1);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "\nexecution time for serial of array length "<< length << " is : " << duration.count() << endl;

    randomize(arr);
    auto start_p = std::chrono::high_resolution_clock::now();

    #pragma omp parallel
    {
        #pragma omp single
        {
            p_quick(arr, 0, arr.size() - 1);
        }
    }
    auto end_p = std::chrono::high_resolution_clock::now();
    

    std::chrono::duration<double> duration_p = end_p - start_p;
    std::cout << "\nExecution time for parallel  of array length "<< length << " is :" << duration_p.count() << endl;
}

int main() {
    for(int len : {10,100,1000}) {
        run(len);
    }
    return 0;
}