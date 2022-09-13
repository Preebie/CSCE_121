#include <iostream>
#include <limits>
#include "functions.h"

using std::cout;
using std::cin; 
using std::endl;

int main() {
    // TODO(student): print prompt for input
    int number_1;
    cout << "Enter numbers 0 < a <= b <= 10000: ";
    int number_2;
    cin >> number_1;
    cin >> number_2;


    // TODO(student): read the numbers from standard input

    // TODO(student): validate input (and reprompt on invalid input)
    bool validity = is_valid_range(number_1, number_2);
    while (!validity) {
        cout << "Invalid input" << endl;
        cout << "Enter numbers 0 < a <= b <= 10000: ";
        cin >> number_1 >> number_2;
        validity = is_valid_range(number_1, number_2);
    }
    // TODO(student): compute and display solution
 
    int final_amount = count_valid_numbers(number_1, number_2);
    cout << "There are " << final_amount << " valid numbers between " << number_1 << " and " << number_2 << endl;

    return 0;
}
