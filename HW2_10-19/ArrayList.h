#ifndef ZYBOOK_ARRAYLIST_H_
#define ZYBOOK_ARRAYLIST_H_

#include <string>
using std::string;

class ArrayList {
public:
    ArrayList() = default;
    ArrayList(const ArrayList& copyList);  // copy constructor
    ArrayList& operator=(const ArrayList&);  // assignment
    ~ArrayList();
    bool empty() const;
    int size() const {return numItems;};
    void push_back(const string& str);  // makes a copy of data item
    void push_front(const string& str);
    bool pop_back(string& str);  // sets str to a copy of the item removed
    bool pop_front(string& str);
private:
    string array[12];
    string* head {&array[0]};
    string* tail {&array[0]};
    int numItems {0};
};

#endif