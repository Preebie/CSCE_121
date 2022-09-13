#include "LinkedList.h"
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;
using std::size_t;

Node::Node(int data) {
  this->data = data;
  this -> next = nullptr;
}
size_t LinkedList::size() const {
  return _size;
}

void Node::setNext(Node* other) {
  this->next = other;
}

void LinkedList::push_back(int value) {
  _marker = new Node(value);

  if (this->_size == 0) {
    _headPtr = _marker;
  }
  else {
    _tailPtr->setNext(_marker);
  }
  _tailPtr = _marker;
  _size++;
}

void LinkedList::clear() {
  _marker = _headPtr;
  while (_marker != NULL) {
    _prevPtr = _marker->next;
    delete _marker;
    _marker = _prevPtr;
  }
  _headPtr = NULL;
  _tailPtr = NULL;
  _size = 0;
}

LinkedList::LinkedList() {
  _size = 0;
  _headPtr = nullptr;
  _tailPtr = nullptr;
  _prevPtr = nullptr;
  _marker = nullptr;
}

LinkedList::LinkedList(const LinkedList& list) {
  Node* marker;
  _size = 0;
  _headPtr = nullptr;
  _tailPtr = nullptr;
  _prevPtr = nullptr;
  _marker = nullptr;

  for (marker = list._headPtr; marker != NULL; marker = marker->next) {
    this->push_back(marker->data);
  }
  
}

void LinkedList::operator=(const LinkedList& list) {
  if (this != &list) {
    this->clear();
    Node* marker;
    for (marker = list._headPtr; marker != NULL; marker = marker->next) {
      this->push_back(marker->data);
    }
  }
  
}

LinkedList::~LinkedList() {
  clear();
}

const Node* LinkedList::head() const {
  if (_size == 0) {
    return nullptr;
  }
  return _headPtr;
}

void LinkedList::remove_duplicates() {
  if (this->_headPtr == nullptr)
    return;

  bool existing = false;
  LinkedList temp;
  temp.push_back(this->_headPtr->data);
  
  for (this->_marker = this->_headPtr->next; this->_marker != NULL; this->_marker = this->_marker->next)
  {
    for (temp._marker = temp._headPtr; temp._marker != NULL; temp._marker = temp._marker->next)
    {
      if (this->_marker->data == temp._marker->data)
        existing = true;
    }
    if (!existing) {
      temp.push_back(this->_marker->data);
    }
    existing = false;
  }

  this->clear();
  for (temp._marker = temp._headPtr; temp._marker != NULL; temp._marker = temp._marker->next) {
      this->push_back(temp._marker->data);
  }
}

size_t LinkedList::length_max_decreasing() const {
  if (this->_headPtr == nullptr) return 0;

  int maxLen = 1, count = 1;
  Node* marker = this->_headPtr;

  while (marker->next != nullptr)
  {
    count = (marker->data > marker->next->data) ? count + 1 : 1;
    maxLen = (maxLen < count) ? count : maxLen;
    marker = marker->next;
  }
  return maxLen;
}
