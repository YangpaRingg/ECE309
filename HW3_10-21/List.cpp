#include "List.h"
#include <iostream>


void List::reverseInPlace()
{
    ListNode* p {head};
    ListNode* prev {nullptr};
    ListNode* r {nullptr};
    while (p != nullptr) {
        if (p == head) {
            tail = p;
            prev = p;
            p = p->next;
            prev->next = nullptr;
        }
        r = p->next;
        p->next = prev;
        prev = p;
        if (r == nullptr) {
            head = p;
        }
        p = r;
    }
}

// DON'T CHANGE ANYTHING BELOW THIS

List::List(const List& other) {
    auto p = other.head;
    while (p) {
        push_back(p->item);
        p = p->next;
    }
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
