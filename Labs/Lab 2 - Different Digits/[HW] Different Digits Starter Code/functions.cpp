#include "functions.h"

bool is_valid_range(int a, int b) {
    // TODO(student): validate input range
    if (a < b) {
        return true;
    }
    else {
        return false;
    }
}
int count_digit_occurrences(int number, int digit) {
  // TODO(student): return how many times digit occurs in number
    int digits = 0;
    if (number < 0) {
        digits = 1;
    }
    while (number) {
        number /= 10;
        digits++;
    }
    return digits;
}

bool has_repeated_digits(int number) {
    // TODO(student): return true if number has repeated digits
    return false;
}

int count_valid_numbers(int a, int b) {
    // TODO(student): return count of valid numbers in range
    return 0;
}
