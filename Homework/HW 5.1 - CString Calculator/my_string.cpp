// my_string.cpp
#include <iostream>
#include "my_string.h"
#include "my_sstream.h"

// TODO(student): define all necessary my_string methods
// NOTE: some methods suggested here may not be required for you.
//       if you don't need a method, then you are not required to implement it
// NOTE: some methods not suggested here may be required for you.
//       if you need a method, then you are required to implement it (or re-engineer your solution to no longer need the method).

// my_string methods

// constructors
//   default (done for you.  you're welcome.)
my_string::my_string() : _data(new char[1]{ 0 }), _size(0) {}
//   rule of "3"
//     my_string copy constructor
my_string::my_string(const my_string& other) : _data(new char[other._size]{}), _size(other._size) {
  for (size_t i = 0; i < other._size; i++)
    _data[i] = other._data[i];

}
//     my_string copy assignment
my_string& my_string::operator=(const my_string& right) {
  if (this != &right) {
    delete[] _data;
    _size = right._size;
    _data = new char[_size];
    for (size_t i = 0; i < _size; i++)
      _data[i] = right._data[i];
  }
  return *this;
}
//     destructor
my_string::~my_string() {
  delete[] _data;
  _data = nullptr;
  _size = 0;
}
//   c-string copy constructor
my_string::my_string(const char* other) : _data(), _size() {
  size_t count = 0;
  while (other[count] != '\0') {
    count++;
  }
  _size = count;
  _data = new char[count] {};
  for (size_t i = 0; i < count; i++)
    _data[i] = other[i];
}
bool operator==(const my_string& left, const my_string& right) {
  if (left.size() != right.size()) {
    return false;
  }
  else {
    for (size_t i = 0; i < right.size(); i++) {
      if (right[i] != left[i]) {
        return false;
      }
    }
  }
  return true;
}
bool operator==(const my_string& left, const char* right) {
  size_t count = 0;
  while (right[count] != '\0') {
    count++;
  }
  if (left.size() != count) {
    return false;
  }
  else {
    for (size_t i = 0; i < left.size(); i++) {
      if (right[i] != left[i]) {
        return false;
      }
    }
  }
  return true;
}

bool operator==(const my_string& left, const char right) {
  if (left[0] != right) {
    return false;
  }
  else {
    return true;
  }
}

bool operator!=(const my_string& left, const char right) {
  return (!(left == right));
}

bool operator!=(const my_string& left, const char* right) {
  return (!(left == right));
}
my_string& my_string::operator+=(char right) {
  _size += 1;
  char* Copycat = new char[_size];
  for (size_t i = 0; i < (_size - 1);i++) {
    Copycat[i] = _data[i];
  }
  Copycat[_size - 1] = right;
  delete[] _data;
  this->_data = Copycat;
  return *this;
}

void my_string::erase(size_t index, size_t length) {
  size_t x = 0;
  char* Copycat = new char[_size - length];

  for (size_t i = 0; i < _size; i++) {
    if ((i < index) || (i > (index + (length - 1)))) {
      Copycat[x] = _data[i];
      x++;
    }
  }
  delete[] _data;
  _size -= length;
  _data = Copycat;
}
void my_string::insert(size_t index, size_t length, const char toInsert) {
  length = length;
  _size += 1;
  size_t y = 0;
  char* NewVar = new char[_size];
  for (size_t i = 0; i < _size; i++) {
    if ((i == index)) {
      NewVar[i] = toInsert;
    }
    else {
      NewVar[i] = _data[y];
      y++;
    }
  }
  delete[] _data;
  _data = NewVar;

}

//my_string my_string::substr(size_t one, size_t two) {
//  size_t size = (two - one);
//  my_string Returned;
//  delete[] Returned._data;
//  Returned._size = size;
//  Returned._data = new char[size];
//  for (size_t i = one; i < two; i++) {
//    Returned[i] = _data[i];
//  }
//  return Returned;
//}
// element access
//   at
//   front
//   operator[]

// capacity
//   empty
//   size

// operations
//   concatenation
//     my_string + my_string (non-member, friend)
//     my_string + c-string (non-member, friend)
//     my_string + char (non-member, friend)
//     c-string + my_string (non-member, friend)
//     char + my_string (non-member, friend)
//     my_string += my_string
//     my_string += c-string
//     my_string += char

// search
//   find

// non-member functions
//   relational operators
//     my_string == my_string
//     my_string == c-string
//   stream operators
//     ostream instertion operator
std::ostream& operator<<(std::ostream& os, const my_string& str) {
  for (size_t i = 0; i < str.size(); i++) {
    os << str.at(i);
  }
  return os;
}
//     istream extraction operator
//     getline
//   numeric conversions
//     to_string


// my_istringstream methods

my_istringstream::my_istringstream(const my_string& str) : _str(str), idx(0), state_fail(false), state_eof(str.empty()) {}

void my_istringstream::eat_whitespaces() {
  while (idx < _str.size() && isspace(_str[idx])) {
    idx++;
  }
}

my_istringstream& my_istringstream::operator>>(my_string& str) {
  eat_whitespaces();
  if (eof()) {
    state_fail = true;
  }
  if (fail()) {
    return *this;
  }
  my_string s;
  while (idx < _str.size() && !isspace(_str[idx])) {
    s += _str[idx++];
  }
  if (idx == _str.size()) {
    state_eof = true;
  }
  str = s;
  return *this;
}

my_istringstream& my_istringstream::operator>>(char& c) {
  eat_whitespaces();
  if (eof()) {
    state_fail = true;
  }
  if (fail()) {
    return *this;
  }
  if (idx < _str.size()) {
    c = _str[idx++];
  }
  if (idx == _str.size()) {
    state_eof = true;
  }
  return *this;
}

bool my_istringstream::good() const { return !(state_fail || state_eof); }
bool my_istringstream::fail() const { return state_fail; }
bool my_istringstream::eof() const { return state_eof; }

// TODO(student): define other my_istringstream methods, if any
std::istream& operator>>(std::istream& os, my_string& str) {
  char* charray = new char[1000];
  os >> charray;
  str = my_string{ charray };
  delete[] charray;
  return os;
}

