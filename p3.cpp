#include <iostream>
#include <omp.h>
using namespace std;

bool isPalindrome(int n) {
    int num = 0, temp = n;
    while (n) {
        int digit = n % 10;
        n /= 10;
        num = num * 10 + digit;
    }
    return num == temp;
}

void printerSerial(int threshold) {
    for(int i = 11;i < threshold;++i) {
        if(isPalindrome(i)) {
            cout << i << ", ";
        }
    }
}

void printer_parallel(int threshold) {
    #pragma omp parallel for
    for (int i = 11; i <= threshold; ++i) {
        if (isPalindrome(i)) {
            #pragma omp critical
            {
                cout << i << ", ";
                cout << "Thread " << omp_get_thread_num() << " checked number " << i << "\n";
            }
        }
    }
}

int main() {
    int threshold;
    cout << "Enter the limit value: ";
    cin >> threshold;
    
   
    omp_set_num_threads(5);

    double s = omp_get_wtime();
    printerSerial(threshold);
    double e = omp_get_wtime();
    cout << "\nserial execution time : " << e - s << " seconds\n";

    s = omp_get_wtime();
    printer_parallel(threshold);
    e = omp_get_wtime();
    cout << "parallel execution time : " << e - s << " seconds\n";

    return 0;
}
