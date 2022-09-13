#include <iostream>
#include "cstring.h"
using std::string;
using std::cout;
using std::endl;



unsigned int length(char str[]) {
    int size_str = strlen(str);
        
    return size_str;
}

string convertToStr(char str[]) {
    int a = strlen(str);
    string new_string = "";
    new_string.resize(a);
    for (int n = 0; n <= a; n++) {
        new_string[n] = str[n];
    }
    return new_string;
}

unsigned int find(char str[], char character) {
    int a = strlen(str);
    string true_str = convertToStr(str);
    int position = true_str.find_first_of(character);
    if (position == string::npos) {
        return a;
    }
    else {
        return position;
    }
}

bool equalStr(char str1[], char str2[]) {
    string first_str = convertToStr(str1);
    string second_str = convertToStr(str2);
    int truth = first_str.compare(second_str);
    if (truth == 0) {
        return true;
    }
    else {
        return false;
    }
}