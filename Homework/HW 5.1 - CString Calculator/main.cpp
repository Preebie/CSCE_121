// main.cpp
#include <iostream>
#include <limits>
#include "my_string.h"
#include "my_sstream.h"
#include "./string_calculator.h"

using std::cout;
using std::endl;
using std::cin;

int main() {
  my_string thing = "";
  my_string num1 = "";
  my_string num2 = "";
  char action = ' ';
  my_string ans = "0";
  cout << "String Calculator" << endl << "\"q\" or \"quit\" or ctrl+d to exit" << endl;

  while (true) {

    cout << ">> " << endl;
    cin >> num1;

    if ((num1 == "q") or (num1 == "quit"))
      break;

    if (num1 == "ans")
      num1 = ans;

    if (cin.get() == '\n') {
      ans = num1;
      cout << "ans = " << endl << endl << "     " << ans << endl << endl;
    }

    else {
      cin >> action >> num2;
      if (num2 == "ans") {
        num2 = ans;
      }

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

  cout << "farvel!" << endl;
    // TODO(student): put your existing implementation of main here
}
