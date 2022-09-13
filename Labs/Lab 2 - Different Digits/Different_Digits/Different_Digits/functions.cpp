#include "functions.h"

bool is_valid_range(int a, int b) {
    // TODO(student): validate input range
    if ((0 < a) and (a <= b) and (b <= 10000)) {
        return true;
    }
    else {
        return false;
    }
}
int count_digit_occurrences(int number, int digit) {
    // TODO(student): return how many times digit occurs in number
    if (number < 0) {
        number = -number;
    }
    if (digit < 0) {
        digit = -digit;
    }
    if (number == digit) {
        return 1;
    }
    else {
        int occurrence = 0;
        int fake_number = number;
        while (fake_number > 0) {
            int remainder = fake_number % 10;
            if (remainder == digit)
            {
                occurrence += 1;
            }
            fake_number /= 10;
        }
        return occurrence;
    }
}

bool has_repeated_digits(int number) {
    int a = count_digit_occurrences(number, 1);
    int b = count_digit_occurrences(number, 2);
    int c = count_digit_occurrences(number, 3);
    int d = count_digit_occurrences(number, 4);
    int e = count_digit_occurrences(number, 5);
    int f = count_digit_occurrences(number, 6);
    int g = count_digit_occurrences(number, 7);
    int h = count_digit_occurrences(number, 8);
    int i = count_digit_occurrences(number, 9);
    int j = count_digit_occurrences(number, 0);

    if ((a > 1) || (b > 1) || (c > 1) || (d > 1) || (e > 1) || (f > 1) || (g > 1) || (h > 1) || (i > 1) || (j > 1)) {
        return true;
    }
    else {
        return false;
    }
}   



int count_valid_numbers(int a, int b) {
    long int count_of_repitition = 0;
    while (a <= b) {
        if (has_repeated_digits(a)) {
            count_of_repitition += 1;
        }
        a++;
    }
    return count_of_repitition;
}
