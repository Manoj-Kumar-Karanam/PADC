#include <iostream>

using namespace std;

double f(double x) {
    return (3 * x) + 5;
}

double trap(int a, int b, int n) {
    double h = (b - a) / static_cast<double>(n);
    double area = (f(a) + f(b)) / 2.0; 

    for (int i = 1; i < n; ++i) {
        double x = a + i * h;
        area += f(x); 
    }

    area *= h;
    return area;
}

int main() {
    int a = 0, b = 3, n = 16;
    
    cout << "Approximate integral: " << trap(a, b, n) << endl;
    return 0;
}
