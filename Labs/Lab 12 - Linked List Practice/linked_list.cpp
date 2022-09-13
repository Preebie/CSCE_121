#include "linked_list.h"
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

void MyList::add(string name, int score) {
  _marker = new MyNode(name, score); 

  if (empty()) {
    _headPtr = _marker;
  }else {
    _tailPtr->setNext(_marker);
  }
  _tailPtr = _marker;
  _size++;
}

void MyList::clear() {
  _marker = _headPtr;
  while (_marker != NULL) {
    _prevPtr = _marker->next();
    delete _marker;
    _marker = _prevPtr;
  }
  _headPtr = NULL;
  _tailPtr = NULL;
  _size = 0;
  // TODO
}


bool MyList::remove(string name) {
  for (_marker = _headPtr; _marker != NULL; _marker = _marker-> next()) {
    if (_marker->name() == name) 
      break;

    _prevPtr = _marker;
  }

  if (_marker == NULL) 
    return false;
  
  else {
     if ((_marker == _headPtr) && (_marker == _tailPtr)) {
     _headPtr = NULL;
     _tailPtr = NULL;
    }

    else if (_marker == _tailPtr) {
      _tailPtr = _prevPtr;
      _prevPtr->setNext(nullptr);
    }

    else if (_marker == _headPtr)
      _headPtr = _marker->next();

    else
      _prevPtr->setNext(_marker->next());
  }
  _marker->setNext(nullptr);
  delete _marker;
  _marker = nullptr;
  _size--;
  return true;
}

bool MyList::insert(string name, int score, size_t index) {
    // TODO
    return false;
}

MyList::MyList() {
    _size = 0;
    _headPtr = nullptr;
    _tailPtr = nullptr;
    _prevPtr = nullptr;
    _marker = nullptr;
}

MyList::~MyList() {
    clear();
}

size_t MyList::size() {
    return _size;
}

bool MyList::empty() {
    return _headPtr == nullptr;
}

MyNode* MyList::head() {
    return _headPtr;
}

void MyList::printList() {
    _marker = _headPtr;
    if (_marker == nullptr) {
        cout << "Linked list is empty" << endl;
        return;
    }

    while (_marker != nullptr) {
        cout << "[ " << _marker->name() << ", " << _marker->score() << " ]" << endl;
        _marker = _marker->next();
    }
}

MyNode::MyNode(std::string name, int score) {
    _name = name;
    _score = score;
    _nextPtr = nullptr;
}

std::string MyNode::name()  {
    return _name;
}

int MyNode::score() {
    return _score;
}

void MyNode::setNext(MyNode* other) {
    _nextPtr = other;
}

MyNode* MyNode::next() {
    return _nextPtr;
}
