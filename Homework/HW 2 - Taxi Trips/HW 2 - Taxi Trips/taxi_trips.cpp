#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include "taxi_trips.h"

using std::string;
using std::ifstream;
using std::cin;
using std::cout;
using std::endl;


bool is_payment_valid(string type, string valid_types[], unsigned int size) {
    bool counter = 0;
    if (type == "x") {
        throw std::invalid_argument("This is not a valid argument!");
    }
    for (unsigned int n = 0; n < size; n++) {
        if (valid_types[n] == type) {
            counter = true;
        }
    }
    if (counter) {
        return true;
    }
    else {
        return false;
    }
}

double max(double values[], unsigned int size) {
    double max = 0;
    if (size == 0) {
        throw std::invalid_argument("Invalid Argument!");
    }
    for (unsigned int n = 0; n < size;n++) {
        if (values[n] > max) {
            max = values[n];
        }
    }
    return max;
}

double min(double values[], unsigned int size) {
    double min = INT32_MAX;
    if (size == 0) {
        throw std::invalid_argument("Invalid Argument!");
    }
    for (unsigned int n = 0; n < size;n++) {
        if (values[n] < min) {
            min = values[n];
        }
    }
    return min;
}

double average(double values[], unsigned int size) {
    double avg = 0;
    int counter = 0;
    if (size == 0) {
        throw std::invalid_argument("Invalid Argument!");
    }
    for (unsigned int n = 0; n < size;n++) {
        avg += values[n];
        counter++;
    }

    avg /= counter;

    return avg;
}

double mode(double values[], unsigned int size) {
    if (size == 0) {
        throw std::invalid_argument("Invalid Argument!");
    }
    int counter = 0;
    int totalcounter = 0;
    double mode = 0;
    double x = 0;
    for (unsigned int n = 0; n < size;n++) {
        x = values[n];
        for (unsigned int n = 0; n < size;n++) {
            if (values[n] == x) {
                counter++;
            }
        }
        if (counter > totalcounter) {
            totalcounter = counter;
            mode = x;
        }
        counter = 0;
    }

    return mode;
}

unsigned int length_longest_seq_zeros(double values[], unsigned int size) {
    int counter = 0;
    int maxcounter = 0;
    int position = 0;

    if (size == 0) {
        throw std::invalid_argument("Invalid Argument!");
    }
    for (unsigned int n = 0; n < size;n++) {
        if (values[n] == 0) {
            counter++;
            if (counter > maxcounter) {
                maxcounter = counter;
            }
        }
        else {
            counter = 0;
        }
    }
    return maxcounter;
}