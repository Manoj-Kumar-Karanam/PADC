#include<bits/stdc++.h>

using namespace std;

int main() {
   vector<int> arr = {1,2,3,6,5,4};
   auto beg = std::find(arr.begin(),arr.end(),6);
   auto ed = std:: find(arr.begin(),arr.end(),1);
   int cost = ed - beg;
   
   cout << cost;
}