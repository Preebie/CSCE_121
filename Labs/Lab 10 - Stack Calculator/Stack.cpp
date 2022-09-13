#include <iostream>
#include <cmath>
#include <string>
#include "Stack.h"

using std::cout;
using std::cin;
using std::endl;

void push(Stack& s, double element) {
	if (s.length == s.capacity) {
		double* doubleArray = new double[2 * s.capacity];

		for (int n = 0; n < s.capacity; n++)
			doubleArray[n] = s.A[n];

		delete[] s.A;
		s.A = doubleArray;
		s.capacity *= 2;
	}
	s.A[s.length] = element;
	s.length++;
}

double pop(Stack& s) {
	if (s.length == 0) 
		return NAN;
	
	double num = s.A[s.length-1];
	s.length--;
	return num;
}