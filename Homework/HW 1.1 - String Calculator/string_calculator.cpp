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

    while (zero == check) {
        num.erase(0, 1);
        check = num.substr(0, 1);

    }
    while (neg_zero == neg_check) {
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

        while ((lhs.size() != 1) and (rhs.size() != 1)) {
            num1 = rhs.back();
            num2 = lhs.back();
            rhs.erase(rhs.size() - 1, 1);
            lhs.erase(lhs.size() - 1, 1);
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
        rhs.erase(rhs.size() - 1, 1);
        lhs.erase(lhs.size() - 1, 1);
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

        
        if (lhs < rhs) {
            string switcher = rhs;
            rhs = lhs;
            lhs = switcher;
            x = true;
        }
        int carry = 0;
        //cout << rhs << "\n";
        //cout << lhs << "\n";

        addition = "";

        while ((lhs.size() != 1) and (rhs.size() != 1)) {

            num1 = rhs.back();
            num2 = lhs.back();
            rhs.erase(rhs.size() - 1, 1);
            lhs.erase(lhs.size() - 1, 1);
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
        rhs.erase(rhs.size() - 1, 1);
        lhs.erase(lhs.size() - 1, 1);
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
        
        if (lhs > rhs) {
            x = true;
        }
        if (lhs < rhs) {
            string switcher = rhs;
            rhs = lhs;
            lhs = switcher;
        }
        int carry = 0;

        addition = "";
        while ((lhs.size() != 1) and (rhs.size() != 1)) {
            char num1 = rhs.back();
            char num2 = lhs.back();
            rhs.erase(rhs.size() - 1, 1);
            lhs.erase(lhs.size() - 1, 1);
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
        rhs.erase(rhs.size() - 1, 1);
        lhs.erase(lhs.size() - 1, 1);
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

  bool neg = 0;
  if ((lhs.at(0) == '-') xor (rhs.at(0) == '-')) {
    neg = 1;
  }
  if (lhs.at(0) == '-')
    lhs.erase(0, 1);
  if (rhs.at(0) == '-')
    rhs.erase(0, 1);
  int rhs_len = rhs.size();
  int lhs_len = lhs.size();
  
  string ans = "";
  for (int n = 0; n < rhs_len + lhs_len; n++) {
    ans.insert(0, "0");
  }
  for (int n = rhs_len - 1; n >= 0; n--) {
    for (int x = lhs_len - 1; x >= 0; x--) {
      int p = (rhs.at(n) - '0') * (lhs.at(x) - '0') + (ans.at(n + x + 1) - '0');
      ans.at(n + x + 1) = p % 10 + '0';
      ans.at(n + x) += p / 10;
    }
  }
  for (int i = 0; i < rhs_len + lhs_len; i++) {
    if (ans[i] != '0') {
      if (neg)
        return '-' + ans.substr(i);
      else
        return ans.substr(i);
    }
  }
  return "0";

  
}
