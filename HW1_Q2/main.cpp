#include <string.h>

using namespace std;

class MyString {

private:

    char* p; // string pointer

public:

    MyString() {
        p = new char[1];
        p[0] = '\0';
    }
    MyString(const char* s) {
        int length = strlen(s);
        p = new char[length + 1];
        strcpy(p, s);
    }
    bool empty();
    int size();
    bool contains(char c);
    bool contains(const char* string);
    ~MyString() {
        delete[] p;
    }

};

bool MyString::empty() {
    bool emp = (p[0] == '\0');
    return emp;
}
int MyString::size() {
    int length = strlen(p);
    return length;
}
bool MyString::contains(char c) {
    bool cont = (strchr(p, c) != nullptr);
    return cont;
}
bool MyString::contains(const char* string) {
    bool cont = (strstr(p, string) != nullptr);
    return cont;
}

int main() {
    return 0;
}
