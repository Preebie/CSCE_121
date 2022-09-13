#include <iostream>
#include <string>

using std::string;
using namespace std;



string number_words(unsigned int n) {
    
 
    //define a number for values divisible by 10
     bool zero_change = false;
    if ((n == 0) && (!zero_change)) {
        return "zero";
    }
    //add words for numbers 1-15
    else if ((n == 0) && (zero_change)) {
        return "";
    }
    else if (n == 1) {
        return "one";  
    }
    else if (n == 2) {
        return "two";
    }
    else if (n == 3) {
        return "three";
    }
    else if (n == 4) {
        return "four";
    }
    else if (n == 5) {
        return "five";
    }
    else if (n == 6) {
        return "six";
    }
    else if (n == 7) {
        return "seven";
    }
    else if (n == 8) {
        return "eight";
    }
    else if (n == 9) {
        return "nine";
    }
    else if (n == 10) {
        return "ten";
    }
    else if (n == 11) {
        return "eleven";
    }
    else if (n == 12) {
        return "twelve";
    }
    else if (n == 13) {
        return "thirteen";
    }
    else if (n == 14) {
        return "fourteen";
    }
    else if (n == 15) {
        return "fifteen";
    }
    //add words for 16-20
    else if ((n >= 16) && (n < 20)) {
        int x = n % 10;
        string word = number_words(x) + "teen";
        return word;
    }
    //call function nest for values above 20
    else if ((n >= 20) && (n < 30)) {
        int x = n - 20;
         zero_change = true;
        string word = "twenty-" + number_words(x);
        return word;
    }
    else if ((n >= 30) && (n < 40)) {
        int x = n - 30;
         zero_change = true;

        string word = "thirty-" + number_words(x);
        return word;
    }
    else if ((n >= 40) && (n < 50)) {
        int x = n - 40;
         zero_change = true;

        string word = "forty-" + number_words(x);
        return word;
    }
    else if ((n >= 50) && (n < 60)) {
        int x = n - 50;
         zero_change = true;

        string word = "fifty-" + number_words(x);
        return word;
    }
    else if ((n >= 60) && (n < 70)) {
        int x = n - 60;
         zero_change = true;

        string word = "sixty-" + number_words(x);
        return word;
    }
    else if ((n >= 70) && (n < 80)) {
        int x = n - 70;
         zero_change = true;

        string word = "seventy-" + number_words(x);
        return word;
    }
    else if ((n >= 80) && (n < 90)) {
        int x = n - 80;
         zero_change = true;

        string word = "eighty-" + number_words(x);

        return word;
    }
    else if ((n >= 90) && (n < 100)) {
        int x = n - 90;
         zero_change = true;

        string word = "ninety-" + number_words(x);
        return word;
    }
    //throw error for wrong values
    else {
        throw std::invalid_argument("This is an invalid number!");
    }
    
}
//int main() {
//    cout << number_words(50);
//}
