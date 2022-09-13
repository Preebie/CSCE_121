#include "LinkedList.h"
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;
using std::size_t;


int main() {
  LinkedList list;
  
  list.push_back(11);
  list.push_back(9);
  list.push_back(3);
  list.push_back(8);
  list.push_back(7);
  list.push_back(5);
  list.push_back(2);
  list.push_back(1);
  list.push_back(4);
  list.push_back(3);
  list.push_back(9);
  list.push_back(8);

  cout << list.length_max_decreasing() << endl;
  list.remove_duplicates();

  LinkedList Slist(list);
  LinkedList List2;
  List2 = Slist;

  for (Slist._marker = Slist._headPtr; Slist._marker != NULL; Slist._marker = Slist._marker->next) {
    cout << Slist._marker->data << endl;
  }
    return 0;
}
