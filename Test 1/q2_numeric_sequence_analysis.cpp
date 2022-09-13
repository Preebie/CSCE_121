#include <iostream>

using namespace std;



int main() {
   //initialize variables
   double average = 0;
   int n = 1;
   cout << "Input: ";
   int addition = 0;
   int max = 0;
   int min = INT32_MAX;
   int counter = 0;
   //check for 0
   while (n != 0) {
       cin >> n;
       addition += n;
       if (max < n) {
           max = n;
       }
       if (min > n) {
           min = n;
       }
       counter++;
       
   }
   average = addition / counter;
   //cout values
   cout << "min " << min << " max " << max << " average " << average;
}


