#include <iostream>
#include <string>
#include "./string_calculator.h"

using std::cout;
using std::endl;
using std::string;

unsigned int digit_to_decimal(char digit) {
    int x = (int)(digit);
    if ((x < 48) or (x > 57)) {
        throw std::invalid_argument("error");
    }
    else {
        digit = (int)(digit);
        digit -= 48;
    }
    return digit;
}

char decimal_to_digit(unsigned int decimal) {
    decimal += 48;
    int x = decimal;
    if ((x < 48) or (x > 57)) {
        throw std::invalid_argument("error");
    }
    decimal = (char)decimal;
    return decimal;
}

string trim_leading_zeros(string num) {
    string zero = "0";
    string neg_zero = "-0";
    string check = num.substr(0, 1);
    string neg_check = num.substr(0, 2);

    while (zero.compare(check) == 0) {
        num.erase(0, 1);
        check = num.substr(0, 1);

    }
    while (neg_zero.compare(neg_check) == 0) {
        num.erase(1, 1);
        neg_check = num.substr(0, 2);
    }
    if ((num == "") or (num == "-")) {
        num = "0";
    }


    return num;
}

string add(string lhs, string rhs) {
    // TODO(student): implement

    string addition = "0";
    lhs = trim_leading_zeros(lhs);
    rhs = trim_leading_zeros(rhs);
    if ((lhs == "0") and (rhs == "0")) {
        addition = "0";
    }
    else if ((lhs == "0") and (rhs != "0")) {
        addition = rhs;
    }
    else if ((lhs != "0") and (rhs == "0")) {
        addition = lhs;
    }

    else if ((lhs.at(0) != '-') and (rhs.at(0) != '-')) {
        int num1 = 0;
        int num2 = 0;
        int num3 = 0;
        int fnum1 = 0;
        int fnum2 = 0;
        char fnum3 = '0';
        while (lhs.size() > rhs.size()) {
            rhs.insert(0, "0");
        }
        while (lhs.size() < rhs.size()) {
            lhs.insert(0, "0");
        }
        int carry = 0;
        addition = "";

        while ((lhs.length() != 1) and (rhs.size() != 1)) {
            num1 = rhs.back();
            num2 = lhs.back();
            rhs.erase(rhs.length() - 1, 1);
            lhs.erase(lhs.length() - 1, 1);
            fnum1 = digit_to_decimal(num1);
            fnum2 = digit_to_decimal(num2);
            num3 = (fnum2 + carry) + fnum1;
            carry = 0;
            if (num3 >= 10) {
                num3 -= 10;
                carry = 1;
            }
            fnum3 = decimal_to_digit(num3);
            string num_3(1, fnum3);
            addition.insert(0, num_3);
        }

        num1 = rhs.back();
        num2 = lhs.back();
        rhs.erase(rhs.length() - 1, 1);
        lhs.erase(lhs.length() - 1, 1);
        fnum1 = digit_to_decimal(num1);
        fnum2 = digit_to_decimal(num2);
        num3 = (fnum2 + carry) + fnum1;
        carry = 0;
        if (num3 >= 10) {
            int num4 = num3 / 10;
            int num5 = num3 % 10;
            fnum3 = decimal_to_digit(num5);
            string num_5(1, fnum3);
            addition.insert(0, num_5);
            fnum3 = decimal_to_digit(num4);
            string num_4(1, fnum3);
            addition.insert(0, num_4);

        }
        else {
            fnum3 = decimal_to_digit(num3);
            string num_4(1, fnum3);
            addition.insert(0, num_4);
        }

    }

    else if ((lhs.at(0) != '-') and (rhs.at(0) == '-')) {    
        char num1 = '0';
        char num2 = '0';
        int num3 = 0;
        int fnum1 = 0;
        int fnum2 = 0;
        char fnum3 = '0';
        bool x = false;
        rhs.erase(0, 1);
        while (lhs.size() > rhs.size()) {
            rhs.insert(0, "0");
        }
        while (lhs.size() < rhs.size()) {
            lhs.insert(0, "0");
        }

        
        if (lhs.compare(rhs) < 0) {
            string switcher = rhs;
            rhs = lhs;
            lhs = switcher;
            x = true;
        }
        int carry = 0;
        //cout << rhs << "\n";
        //cout << lhs << "\n";

        addition = "";

        while ((lhs.length() != 1) and (rhs.length() != 1)) {

            num1 = rhs.back();
            num2 = lhs.back();
            rhs.erase(rhs.length() - 1, 1);
            lhs.erase(lhs.length() - 1, 1);
            fnum1 = digit_to_decimal(num1);
            fnum2 = digit_to_decimal(num2);
            num3 = (fnum2 - carry) - fnum1;
            carry = 0;
            if (num3 < 0) {
                num3 += 10;
                carry = 1;
                //cout << num3 << "\n";
            }
            fnum3 = decimal_to_digit(num3);
            string num_3(1, fnum3);
            addition.insert(0, num_3);
            //cout << addition << "\n";

        }

        num1 = rhs.back();
        num2 = lhs.back();
        rhs.erase(rhs.length() - 1, 1);
        lhs.erase(lhs.length() - 1, 1);
        fnum1 = digit_to_decimal(num1);
        fnum2 = digit_to_decimal(num2);
        num3 = (fnum2 - carry) - fnum1;
        carry = 0;
        if (num3 < 0) {
            num3 += 10;
            carry = 1;
        }
        fnum3 = decimal_to_digit(num3);
        string num_3(1, fnum3);
        addition.insert(0, num_3);
        if (x) {
            addition.insert(0, "-");

        }
    }
   
    else if ((lhs.at(0) == '-') and (rhs.at(0) != '-')) {

        int num1 = 0;
        int num2 = 0;
        int num3 = 0;
        int fnum1 = 0;
        int fnum2 = 0;
        char fnum3 = '0';
        bool x = false;
        lhs.erase(0, 1);
        while (lhs.size() > rhs.size()) {
            rhs.insert(0, "0");
        }
        while (lhs.size() < rhs.size()) {
            lhs.insert(0, "0");
        }
        
        if (lhs.compare(rhs) > 0) {            
            x = true;
        }
        if (lhs.compare(rhs) < 0) {
            string switcher = rhs;
            rhs = lhs;
            lhs = switcher;
        }
        int carry = 0;

        addition = "";
        while ((lhs.length() != 1) and (rhs.length() != 1)) {
            char num1 = rhs.back();
            char num2 = lhs.back();
            rhs.erase(rhs.length() - 1, 1);
            lhs.erase(lhs.length() - 1, 1);
            int fnum1 = digit_to_decimal(num1);
            int fnum2 = digit_to_decimal(num2);
            int num3 = (fnum2 - carry) - fnum1;
            carry = 0;
            if (num3 < 0) {
                num3 += 10;
                carry = 1;
            }
            char fnum3 = decimal_to_digit(num3);
            string num_3(1, fnum3);
            addition.insert(0, num_3);
        }

        num1 = rhs.back();
        num2 = lhs.back();
        rhs.erase(rhs.length() - 1, 1);
        lhs.erase(lhs.length() - 1, 1);
        fnum1 = digit_to_decimal(num1);
        fnum2 = digit_to_decimal(num2);
        num3 = (fnum2 - carry) - fnum1;
        carry = 0;
        if (num3 < 0) {
            num3 += 10;
            carry = 1;
        }
        fnum3 = decimal_to_digit(num3);
        string num_3(1, fnum3);
        addition.insert(0, num_3);
    
        if (x) {
            addition.insert(0, "-");
        }
    }

    else if ((lhs.at(0) == '-') and (rhs.at(0) == '-')) {

        lhs.erase(0, 1);
        rhs.erase(0, 1);
        addition = add(lhs, rhs);
        addition.insert(0, "-");

    }
    addition = trim_leading_zeros(addition);
    return addition;

}


string subtract(string lhs, string rhs) {
    string subtraction = "0";
    lhs = trim_leading_zeros(lhs);
    rhs = trim_leading_zeros(rhs);
    if (rhs.at(0) == '-') {
        rhs.erase(0, 1);
    }
    else if (rhs.at(0) != '-') {
        rhs.insert(0, "-");
    }
    subtraction = add(lhs, rhs);
    return subtraction;
}

string multiply(string lhs, string rhs) {
    bool neg = false;
    bool neg2 = false;
    if (lhs.at(0) == '-') {
        lhs.erase(0, 1);
        neg = true;
    }
    if (lhs.at(0) == '-') {
        lhs.erase(0, 1);
        neg2 = true;
    }

    while (lhs.size() > rhs.size()) {
        rhs.insert(0, "0");
    }
    while (lhs.size() < rhs.size()) {
        lhs.insert(0, "0");
    }
    // TODO(student): implement
    string multiplied = "";
    string final_multiple = "0";
    char fnum3 = ' ';
    char number2 = ' ';
    int num1 = 0;
    int num2 = 0;
    int num3 = 0;
    int carry = 0;
    int plus;
    bool x = false;
    num2 = digit_to_decimal(lhs.back());
    if (lhs.length() != 0) {
       

        if (rhs.length() != 1) {
            num1 = digit_to_decimal(rhs.back());
            
            
            rhs.erase(0, 1);
            num3 = (num2 * num1) + carry;
            carry = 0;
            if (num3 > 10) {
                carry = num3 / 10;
                num3 = num3 % 10;
            }
            fnum3 = decimal_to_digit(num3);
            string num_3(1, fnum3);
            multiplied.insert(0, num_3);
        }
        num1 = digit_to_decimal(rhs.back());
        num2 = digit_to_decimal(lhs.back());
        lhs.erase(0, 1);
        rhs.erase(0, 1);
        num3 = (num2 * num1) + carry;
        carry = 0;
        if (num3 > 10) {
            carry = num3/10;
            num3 = num3 % 10;
            cout << carry << endl;
            cout << num3 << endl;
        }
        
        fnum3 = decimal_to_digit(num3);
        string num_3(1, fnum3);
        multiplied.insert(0, num_3);

        fnum3 = decimal_to_digit(carry);
        string num_carry(1, fnum3);
        multiplied.insert(0, num_carry);
        
        for (int zeroes = 0; zeroes < x; x++) {
            multiplied.insert(multiplied.length()-1, "0");
        }
        final_multiple = add(final_multiple, multiplied);
        multiplied = "";
        if (lhs.length() != 0) {
            num2 = digit_to_decimal(lhs.back());
            lhs.erase(0, 1);
        }
    }
    if (neg xor neg2) {
        final_multiple.insert(0, "-");
    }

    return final_multiple;
}
