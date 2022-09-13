#include <iostream>

using namespace std;

bool array_compare(int A[], unsigned int size_A, int B[], unsigned int size_B) {
    int counter = 0;
    //check size of array
    if (size_A < size_B) {
        return true;
    }
    else if (size_A > size_B) {
        return false;
    }
    //if size is equal, check values inside arrays
    else if (size_A == size_B) {
        while (A[counter] == B[counter]) {
            bool x = true;
            counter++;
        }
        if (A[counter] > B[counter]) {
            return false;
        }
        else if (A[counter] < B[counter]) {
            return true;
        }
        
    }
}



