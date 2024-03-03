#include <iostream>
#include <string>
#include "List.h"

void printList(const List&);
List reverse(const List &list) {
    List rlist;
    for (auto i : list) {
        rlist.push_front(i);
    }
    return rlist;
}

int main()
{
  List l;
  l.push_back("one");
  l.push_back("two");
  l.push_back("three");
  l.push_back("four");

  std::cout << "List in order: ";
  printList(l);

  List l2 = reverse(l);
  std::cout << "New list in reverse order: ";
  printList(l2);

  l.reverseInPlace();
  std::cout << "Reverse in place: ";
  printList(l);

  return 0;
}

void printList(const List &l) {
    List::iterator i = l.begin();
    while(i != l.end()) {
        std::cout << *i << ", ";
        ++i;
    }
    std::cout << std::endl;
}
