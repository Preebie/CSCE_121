// string_calculator.cpp
#include <iostream>
#include <limits>
#include "my_string.h"
#include "my_sstream.h"
#include "./string_calculator.h"

using std::cout;
using std::endl;

unsigned int digit_to_decimal(char digit) {
  // TODO(student): put your existing implementation here
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
  decimal = static_cast <char> (decimal);
  return decimal;
}

my_string trim_leading_zeros(const my_string& fnum) {
  my_string num = fnum;
  my_string zero = "0";
  my_string neg_zero = "-0";
  my_string check = num.substr(0, 1);
  my_string neg_check = num.substr(0, 2);

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
  return 0;
}

my_string add(const my_string& flhs, const my_string& frhs) {
  my_string lhs = flhs;
  my_string rhs = frhs;

  my_string addition = "0";
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
      rhs.insert(0, 1, '0');
    }
    while (lhs.size() < rhs.size()) {
      lhs.insert(0, 1, '0');
    }


    int carry = 0;
    addition = "";

    while ((lhs.size() != 1) and (rhs.size() != 1)) {
      num1 = rhs.at(rhs.size() - 1);
      num2 = lhs.at(lhs.size() - 1);
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
      addition.insert(0, 1, fnum3);
    }
    num1 = rhs.at(rhs.size() - 1);
    num2 = lhs.at(lhs.size() - 1);

    rhs.erase(rhs.size() - 1, 1);
    lhs.erase(lhs.size() - 1, 1);

    fnum1 = digit_to_decimal(num1);
    fnum2 = digit_to_decimal(num2);

    num3 = (fnum2 + carry) + fnum1;
    carry = 0;
    if (num3 >= 10) {
      int num4 = 1;
      int num5 = num3 - 10;

      fnum3 = decimal_to_digit(num5);
      addition.insert(0, 1, fnum3);
      fnum3 = decimal_to_digit(num4);
      addition.insert(0, 1, fnum3);
    }
    else {
      fnum3 = decimal_to_digit(num3);
      addition.insert(0, 1, fnum3);
    }
  }

  else if ((lhs.at(0) == '-') and (rhs.at(0) == '-')) {

    lhs.erase(0, 1);
    rhs.erase(0, 1);
    addition = add(lhs, rhs);
    addition.insert(0, 1, '-');

  }
  else if ((lhs.at(0) != '-') and (rhs.at(0) == '-')) {

    int num1 = 0;
    int num2 = 0;
    int num3 = 0;
    int fnum1 = 0;
    int fnum2 = 0;
    char fnum3 = '0';
    bool x = false;
    rhs.erase(0, 1);
    while (lhs.size() > rhs.size()) {
      rhs.insert(0, 1, '0');
    }
    while (lhs.size() < rhs.size()) {
      lhs.insert(0, 1, '0');
    }
    x = true;

    for (size_t n = 0; n < lhs.size(); n++) {
      if (lhs.at(n) < rhs.at(n)) {
        my_string switcher = rhs;
        rhs = lhs;
        lhs = switcher;
        x = false;
        break;
      }
      else {
        continue;
      }
    }

    int carry = 0;

    addition = "";
    while ((lhs.size() != 1) and (rhs.size() != 1)) {
      char num1 = rhs.at(rhs.size() - 1);
      char num2 = lhs.at(lhs.size() - 1);
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
      addition.insert(0, 1, fnum3);
    }

    num1 = rhs.at(rhs.size() - 1);
    num2 = lhs.at(lhs.size() - 1);
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
    addition.insert(0, 1, fnum3);

    if (!x) {
      addition.insert(0, 1, '-');
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
      rhs.insert(0, 1, '0');
    }
    while (lhs.size() < rhs.size()) {
      lhs.insert(0, 1, '0');
    }
    x = true;

    for (size_t n = 0; n < lhs.size(); n++) {
      if (lhs.at(n) < rhs.at(n)) {
        my_string switcher = rhs;
        rhs = lhs;
        lhs = switcher;
        x = false;
        break;
      }
      else {
        continue;
      }
    }

    int carry = 0;

    addition = "";
    while ((lhs.size() != 1) and (rhs.size() != 1)) {
      char num1 = rhs.at(rhs.size() - 1);
      char num2 = lhs.at(lhs.size() - 1);
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
      addition.insert(0, 1, fnum3);
    }

    num1 = rhs.at(rhs.size() - 1);
    num2 = lhs.at(lhs.size() - 1);
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
    addition.insert(0, 1, fnum3);

    if (x) {
      addition.insert(0, 1, '-');
    }
  }

  addition = trim_leading_zeros(addition);
  return addition;
}

my_string subtract(const my_string& flhs, const my_string& frhs) {
  my_string lhs = flhs;
  my_string rhs = frhs;
  my_string subtraction = "0";
  lhs = trim_leading_zeros(lhs);
  rhs = trim_leading_zeros(rhs);
  if (rhs.at(0) == '-') {
    rhs.erase(0, 1);
  }
  else if (rhs.at(0) != '-') {
    rhs.insert(0, 1, '-');
  }
  subtraction = add(lhs, rhs);
  return subtraction;
  return "0";
}
//
my_string multiply(const my_string& flhs, const my_string& frhs) {
  my_string rhs = frhs;
  my_string lhs = flhs;
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

  my_string ans = "";
  for (int n = 0; n < rhs_len + lhs_len; n++) {
    ans.insert(0, 1, '0');
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
      ans = trim_leading_zeros(ans);
      if (neg)
        ans.insert(0, 1, '-');
      
      return ans;
    }
  }
  return "0";
}
