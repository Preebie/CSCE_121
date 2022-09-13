#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <string>

using std::size_t;
using std::string;

struct Node {
    int data;
    Node* next;

    Node(int data);
    void setNext(Node* other);
};

class LinkedList {
  public:
    size_t _size;
    Node* _headPtr;
    Node* _tailPtr;
    Node* _prevPtr;
    Node* _marker;
    const Node* head() const;

    LinkedList();
    ~LinkedList();
    LinkedList(const LinkedList& list);

    void remove_duplicates();
    void push_back(int data);
    void clear();
    void operator=(const LinkedList& list);
    size_t length_max_decreasing() const;
    size_t size() const;
};

#endif