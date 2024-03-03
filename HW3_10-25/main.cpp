#include <iostream>
#include "List.h"

int main() {
    List l;
    l.push_back("one");
    l.push_back("two");
    l.push_back("three");
    l.push_back("four");

    List r {l};
    return 0;
}
