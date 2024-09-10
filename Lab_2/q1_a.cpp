#define _USE_MATH_DEFINES
#include<bits/stdc++.h>
#include<cmath>

double f(double x) {
    return 1.0 / (1 + (x * x));
}

double simpsons(double a,double b,int n) {
    if(n % 2 != 0) n++;
    double h = (b - a) / n;
    double sum = f(a) + f(b);
    for(int i = 1;i < n;i++) {
        double x = a + i * h;
        if(i % 2 == 0) {
            sum += 2 * f(x);
        }
        else{
            sum += 4 * f(x);
        }

    }
    return (h / 3.0) * sum; 
}

int main() {
    int Threshold = 1000;
    double a = 0.0;
    double b = 1.0;
    double integral = simpsons(a,b,Threshold);
    double pi = 4 * integral;
    std::cout << "Estimated value of pi : " << pi << std::endl;
    std::cout << "actual value : " << M_PI << std::endl;

}