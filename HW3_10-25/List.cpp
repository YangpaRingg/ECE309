#include "List.h"

// IMPLEMENT MOVE CONSTRUCTOR
List::List(List&& other){
    head = other.head;
    tail = other.tail;
    other.head = nullptr;
    other.tail = nullptr;
}

// IMPLEMENT MOVE ASSIGNMENT OPERATOR
List& List::operator=(List &&rhs) {
    head = rhs.head;
    tail = rhs.tail;
    rhs.head = nullptr;
    rhs.tail = nullptr;
}

List::List(const List& other) {
    auto p = other.head;
    while (p) {
        push_back(p->item);
        p = p->next;
    }
}

List& List::operator=(const List& rhs) {
    if (&rhs == this) return *this;
    // delete old list
    auto p = head;
    while (p) {
        auto tmp = p->next;
        delete p;
        p = tmp;
    }
    head = tail = nullptr;
    // copy from rhs
    p = rhs.head;
    while (p) {
        push_back(p->item);
    }
    // return reference to self
    return *this;
}

List::~List() {
    auto p = head;
    while (p) {
        auto tmp = p->next;
        delete p;
        p = tmp;
    }
}

void List::push_back(const Item& a) {
    auto node {new ListNode(a)};
    if ( head == nullptr ) {
        // empty list
        head = node;
        tail = node;
    } else {
        tail->next = node;
        tail = node;
    }
}

void List::push_front(const Item& a) {
    auto node {new ListNode(a)};
    if (head == nullptr) {
        head = node;
        tail = node;
    }
    else {
        node->next = head;
        head = node;
    }
}
