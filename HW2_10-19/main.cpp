#include <iostream>

#include "ArrayList.h"

using namespace std;

int main() {

    ArrayList Groceries;
    Groceries.push_back("Lettuce");
    Groceries.push_back("Tomatoes");
    Groceries.push_front("Turkey");

    return 0;
}
