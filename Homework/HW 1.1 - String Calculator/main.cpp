#include <iostream>
#include <string>
#include <limits>
#include "./string_calculator.h"

using std::cout;
using std::endl;
using std::cin;
using std::string;

int main() {
  string thing = " ";
  string num1 = " ";
  string num2 = "Priyanshu Barnwal";
  char action = ' ';
  string ans = "0";
  bool LHS_valid = 1;
  bool RHS_valid = 1;

  cout << "String Calculator" << endl << "\"q\" or \"quit\" or ctrl+d to exit" << endl;
  while (true) {

    cout << ">> " << endl;
    cin >> num1;
    if ((num1 == "q") or (num1 == "quit") or cin.eof()) {
      break;
    }

    LHS_valid = 1;
    for (int n = 0; n < num1.length(); n++) {

      if (num1.at(n) == ' ')
        break;

      else if (!isdigit(num1.at(n)) && (num1.at(0) != '-')) {
        cout << "invalid LHS" << endl << endl;
        LHS_valid = 0;
        break;
      }
    }


    if (!LHS_valid) {
      while (cin.get() != '\n') {
        cin.ignore();
      }
    }

    else {
      if (num1 == "ans") {
        num1 = ans;
      }
      if (cin.get() == '\n') {
        ans = num1;
        cout << "ans = " << endl << endl << "     " << ans << endl << endl;
      }
      else {
        cin >> action >> num2;

        if (cin.get() == '\n') {
          cout << "invalid RHS" << endl;
        }
        
        if (num2 == "ans") {
          num2 = ans;
        }
        RHS_valid = 1;
        for (int n = 0; n < num2.length(); n++) {

          if (num2.at(n) == ' ')
            break;

          else if (!isdigit(num2.at(n)) && (num2.at(0) != '-')) {
            cout << "invalid RHS" << endl << endl;
            RHS_valid = 0;
            break;
          }
        }
        
        if (!RHS_valid) {
          while (cin.get() != '\n') {
            cin.ignore();
          }
        }
        else {
          cout << "ans =" << endl << endl << "    ";
          switch (action) {

          case('+'):
            ans = add(num1, num2);
            cout << ans;
            break;

          case('-'):
            ans = subtract(num1, num2);
            cout << ans;
            break;

          case('*'):
            ans = multiply(num1, num2);
            cout << ans;
            break;
          }
          cout << endl << endl;
        }
      }
    }
  }
  cout << "farvel!" << endl << endl;
}

