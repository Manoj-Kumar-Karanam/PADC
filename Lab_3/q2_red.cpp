#include<bits/stdc++.h>
#include<omp.h>

using namespace std;



double monteCarlo_serial(int points,int radius) {
    int circlePoints = 0;
    int count = 0;
    srand(time(0));
    for(int i = 0;i < (points) ;i++) {
        double randX = ((double)rand() / RAND_MAX) * radius;
        double randY = ((double)rand() / RAND_MAX) * radius;
        if(count < 5) {

        cout << "x-coordinate:" << randX << " ,y coordinate:" << randY << endl;
        count++;
        }

        if((randX * randX) + (randY * randY) <= (radius * radius)) 
            circlePoints++;


    }
        return 4.0 * circlePoints / points;
}

int main() {
    int radius = 50;
    double s = omp_get_wtime();
    double res = monteCarlo_serial(10000,radius);
    double e = omp_get_wtime();
    cout << "result :" << res << " execution time:" << (e -s ) <<" seconds";
    return 0;   
}