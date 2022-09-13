/*
DADA function definitions
*/

#include <iostream>
#include <cmath>
#include "dada.h"
using std::cout; 
using std::endl;
using std::abs;
using std::sqrt;

int amax(const double x[], const unsigned int len) {
    int max_num = 0;
    double truemax = 0;
    double y = 0;
    if (len == 0) {
        return -1;
    }
    else {
        for (size_t n = 0; n < len; n++) {
            y = abs(x[n]);
            cout << y << endl;
            if (y > truemax) {
                max_num = n;
                truemax = y;
            }
        }
        cout << max_num << endl;
        return max_num;
    }
    
}

double asum(const double x[], const unsigned int len) {
    double sum = 0;
    double y = 0;
    for (size_t n = 0; n < len;n++) {
        y = abs(x[n]);
        sum += y;
    }
    //TODO: student implement code here
    return sum;
}

void axpy(const double a, const double x[], double y[], const unsigned int len) {
    //TODO: student implement code here
    double numx = 0;
    double numy = 0;
    for (size_t n = 0; n < len;n++) {
        numx = x[n];
        numy = y[n];
        y[n] = (numx * a) + numy;
    }
}

void copy(const double src[], double dest[], const unsigned int len) {
    //TODO: student implement code here
    for (size_t n = 0; n < len;n++) {
        dest[n] = src[n];
    }
}

double dot(const double x[], const double y[], const unsigned int len) {
    double dotsum = 0;
    double multiplied = 0;
    for (size_t n = 0; n < len;n++) {
        multiplied = x[n] * y[n];
        dotsum += multiplied;
    }
    return dotsum;
}

double norm2(const double x[], const unsigned int len) {
    //TODO: student implement code here
    double sum = 0;
    double y = 0;
    for (size_t n = 0; n < len;n++) {
        y = x[n]*x[n];
        sum += y;
    }
    sum = sqrt(sum);
    return sum;
}

void scale(const double a, double x[], const unsigned int len) {
    //TODO: student implement code here
    
    for (size_t n = 0; n < len;n++) {
        x[n] = a * x[n];
    }
}

void swap(double x[], double y[], const unsigned int len) {
    //TODO: student implement code here
    double numx = 0;
    double numy = 0;
    for (size_t n = 0; n < len;n++) {
        numx = x[n];
        numy = y[n];
        x[n] = numy;
        y[n] = numx;
    }
}

