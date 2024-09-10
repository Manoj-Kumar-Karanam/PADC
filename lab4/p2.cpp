#include<bits/stdc++.h>
#include<omp.h>

using namespace std;

void takeInput(vector<int> &nums,int size) {
    for(int i = 0;i < size; ++i) {
        nums[i] = rand() % 30;
    }
}

void serial_bubbleSort(vector<int> &nums,int size,int &swapCount) {
    
    for(int i = 0;i < size ; ++i) {
        for(int j = 0;j < size - i - 1; ++j) {
            if(nums[j] > nums[j + 1]) 
                {swapCount ++;
                swap(nums[j + 1],nums[j]);} 
        }
    }
}

vector<int> oddEvenTransposition(vector<int> nums,int size,int &swapCount_even,int &swapCount_odd) {
    for(int phase = 0;phase < size; ++phase) {
        if(phase % 2 == 0) {
            for(int i = 1;i < size; i += 2) {
                if(nums[i - 1] > nums[i]) {
                    swap(nums[i - 1], nums[i]);
                    swapCount_even ++;
                }
            }
        }
        else {
            for(int i = 2;i < size ; i += 2) {
                if(nums[i - 1] > nums[i]) {
                    swap(nums[i - 1],nums[i]);
                    swapCount_odd ++;
                }
            }
        }
    }
    return nums;
}

vector<int> parallel_oddEven(vector<int> nums, int size, int &swapCount_even, int &swapCount_odd) {
    int num_threads = omp_get_max_threads();  
    vector<int> thread_swap_count(num_threads, 0);  
    
    #pragma omp parallel default(none) shared(nums, size, swapCount_even, swapCount_odd, cout, thread_swap_count)
    {
        for (int phase = 0; phase < size; ++phase) {
            if (phase % 2 == 0) {
                // Even phase
                #pragma omp for
                for (int i = 1; i < size; i += 2) {
                    int thread_id = omp_get_thread_num();
                    if (nums[i - 1] > nums[i]) {
                        
                        swap(nums[i - 1], nums[i]);
                        #pragma omp atomic
                        swapCount_even++;
                        #pragma omp atomic
                        thread_swap_count[thread_id]++; 
                    }
                }
            } else {
                
                #pragma omp for
                for (int i = 2; i < size; i += 2) {
                    int thread_id = omp_get_thread_num();
                    if (nums[i - 1] > nums[i]) {
                        // #pragma omp critical
                        // {
                        //     std::cout << "Thread " << thread_id << " swapping elements " << nums[i - 1] << " and " << nums[i] << endl;
                        // }
                        swap(nums[i - 1], nums[i]);
                        #pragma omp atomic
                        swapCount_odd++;
                        #pragma omp atomic
                        thread_swap_count[thread_id]++;  
                    }
                }
            }
        }
    }

    std::cout << "\nSwap counts for each thread:" << endl;
    for (int i = 0; i < num_threads; ++i) {
        std::cout << "Thread " << i << " performed " << thread_swap_count[i] << " swaps." << endl;
    }

    return nums;
}


void print(vector<int> &nums) {
    for(int i : nums) {
        cout << i << " ,";
    
    }
    cout << "\n";
}

void run(int size) {
    vector<int> nums(size);
    takeInput(nums,size);
    cout << "\n<-------------------------------- For n : " << size << " ---------------------------------------->\n";
    int swapCount = 0,swapCount_even = 0, swapCount_odd = 0;
    // cout << "Array before sorting:" << endl;
    // print(nums);
    // cout << "array after sorting: " << endl;
    cout << "\nserial odd even :";
    auto s = omp_get_wtime();
    vector<int> temp = oddEvenTransposition(nums,size,swapCount_even,swapCount_odd);
    auto e = omp_get_wtime();
    // print(temp);
    cout << "\nExecution time(serial odd even) :" << e - s << "\n";
    cout << "\nSwaps in even Phase :" << swapCount_even;
    cout << "\nSwaps in odd Phase :" << swapCount_odd;
    swapCount_even = 0;
    swapCount_odd = 0;
    cout << "\nparallel odd even transposition:";
    s = omp_get_wtime();
    vector<int> arr = parallel_oddEven(nums,size,swapCount_even,swapCount_odd); 
    e = omp_get_wtime();
    cout << "\nExecution time(parallel odd even) :" << e - s << "\n";
    // print(arr);
    cout << "Swaps in even Phase :" << swapCount_even;
    cout << "\nSwaps in odd Phase :" << swapCount_odd;
    cout << "\nserial sort :" ;
    s = omp_get_wtime();
    serial_bubbleSort(nums,size,swapCount);
    e = omp_get_wtime();
    // print(nums); 
    cout << "No. of swaps in serial bubble sort :" << swapCount;
    cout << "\nExecution time(serial bubble sort) :" << e - s << "\n";
    cout << "<------------------------------------------------------------------------------------->\n";
}

int main() {
    vector<int> size = {10,50,100,500};
    
    omp_set_num_threads(omp_get_max_threads());
    for(int n : size)
        run(n);
    return 0;    
}