#include <iostream>
#include <cmath>
#include <string>
#include "Stack.h"
using std::cout;
using std::cin;
using std::endl;
using std::string;

int main() {
	string eqn = "";
	bool go = 1;
	Stack nums;
	double last = 0;
	double x1 = 0;
	double x2 = 0;
	double result = 0;
	while (go) {
		cin >> eqn;
		if (isdigit(eqn.at(0)) || (eqn.at(0) == '.')) {
			double digit = std::stod(eqn);
			push(nums, digit);
		}
		else if (eqn.at(0) == '=') {
			go = 0;
			last = pop(nums);
		}
		else {
			switch (eqn.at(0)) {
				case '+':
					x1 = pop(nums);
					x2 = pop(nums);
					result = x1 + x2;
					push(nums, result);
					break;

				case '-':
					x1 = pop(nums);
					x2 = pop(nums);
					result = x2-x1;
					push(nums, result);
					break;

				case '*':
					x1 = pop(nums);
					x2 = pop(nums);
					result = x1 * x2;
					push(nums, result);
					break;

				case '/':
					x1 = pop(nums);
					x2 = pop(nums);
					result = x2 / x1;
					push(nums, result);
					break;

				default:
					cout << "[ERROR] invalid operator: " << eqn.at(0) << endl;
					return 1;
			}
		}
	}
	
	cout << last;
	delete[] nums.A;
	return 0;
}