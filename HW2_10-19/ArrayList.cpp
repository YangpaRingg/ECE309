#include "ArrayList.h"

using namespace std;

ArrayList::ArrayList(const ArrayList& origList) {
    head = array;
    tail = head;
    for (int i {0}; i < origList.numItems; i++) {
        array[i] = origList.array[i];
        tail++;
    }
    numItems = origList.numItems;
}

ArrayList::~ArrayList() {
    string* p = tail-1;
    for (int i {0}; i < numItems; i++) {
        *p="\0";
        p--;
    }
}

bool ArrayList::empty() const {
    if (array[0] == "\0") return true;
    else return false;
}

void ArrayList::push_back(const string& str) {
    numItems++;
    *tail = str;
    tail++;
}

void ArrayList::push_front(const string& str) {
    numItems++;
    string* p {tail};
    for (int i {1}; i < numItems; i++) {
        *p = *(p-1);
        p--;
    }
    *head = str;
    tail++;
}

bool ArrayList::pop_back(string& str) {
    if ((tail == &array[0]) || (*(tail-1) == "\0" && numItems == 0)) {
        return false;
    }
    else {
        str = *(tail-1);
        *(tail-1) = "\0";
        tail--;
        numItems--;
        return true;
    }
}

bool ArrayList::pop_front(string& str) {
    if ((tail == &array[0]) || (*(tail-1) == "\0" && numItems == 0)) {
        return false;
    }
    else {
        str = *head;
        *head = "\0";
        numItems--;
        string* p = head;
        for (int i {0}; i < numItems; i++) {
            *p = *(p+1);
            p++;
        }
        *p = "\0";
        tail--;
        return true;
    }
}