#include<bits/stdc++.h>
#include<omp.h>

using namespace std;

bool isPrime(int n) {
    if(n <= 1) return false;
    if(n <= 3) return true;
    if(n % 2 == 0 || n % 3 == 0) return false;
    for(int i = 5;i * i <= n; i += 6) {
        if(n % i == 0 || n % (i + 2) == 0) return false; 
    }
    return true;
}

int isPrimeParallel(unordered_map<int,int> &mp) {
    int count = 0;
    #pragma omp parallel for reduction(+ : count)
    for(int i = 3;i <= 20; i += 2) {
        bool element_1 = isPrime(i);
        bool element_2 = isPrime(i + 2);
        
        if(element_1 && element_2) {
            #pragma omp critical
            {
                cout << "Thread " << omp_get_thread_num() << " compared elements " << i << " & " << (i + 2) << "\n";
            }
            #pragma omp atomic
            mp[i] ++;
            #pragma omp atomic
            mp[i + 2] ++;   
            count ++;
        }
    }
    return count;
}

int main() {
    omp_set_num_threads(omp_get_max_threads());
    int sum = 0;
    unordered_map<int,int> mp;
    double s = omp_get_wtime();
    int pairCount = isPrimeParallel(mp);
    double e = omp_get_wtime();
    for(auto &pair : mp) {
        sum += pair.first;
    }
    cout << "test";
    cout << "\nSum of all the prime pairs = " << sum;
    cout << "\nExecution time: " << e - s << " seconds";
    return 0;
}
