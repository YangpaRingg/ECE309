#include <iostream>
#include <string>
using namespace std;

int GetNumOfNonWSCharacters(const string& in) {
    int count {0};
    for (auto i : in) {
        if (i != ' ') {
            ++count;
        }
    }
    return count;
}

int GetNumOfWords(const string& in) {
    int count{0};
    bool prevSpace{false};
    for (auto i: in) {
        if (i == ' ' && prevSpace == false) {
            ++count;
            prevSpace = true;
        } else if (i != ' ') {
            prevSpace = false;
        }
    }
    ++count;
    return count;
}

int FindText(string& sub, string& str) {
    int count {0};
    while (str.find(sub) != string::npos) {
        ++count;
        str = str.substr(str.find(sub) + sub.size(), str.size());
    }
    return count;
}

void ReplaceExclamation(string& str) {
    int size = str.size();
    for (int i {0}; i < size; ++i ) {
        if (str[i] == '!') {
            str[i] = '.';
        }
    }
}

void ShortenSpace(string& str) {
    int size = str.size();
    for (int i {0}; i < size; ++i) {
        if (str[i] == ' ') {
            int j = 1;
            while (str[i+j] == ' ') {
                ++j;
            }
            str.erase(i, j-1);
            size = str.size();
        }
    }
}

void PrintMenu() {
    cout << "c - Number of non-whitespace characters" << endl;
    cout << "w - Number of words" << endl;
    cout << "f - Find text" << endl;
    cout << "r - Replace all !'s" << endl;
    cout << "s - Shorten spaces" << endl;
    cout << "q - Quit" << endl << endl;
}

void ExecuteMenu (char c, string in) {
    if (c == 'c') {
        cout << "Number of non-whitespace characters: " << GetNumOfNonWSCharacters(in) << endl << endl;
    }
    if (c == 'w') {
        cout << "Number of words: " << GetNumOfWords(in) << endl << endl;
    }
    if (c == 'f') {
        cout << "Enter a word or phrase to be found:" << endl;
        string sub;
        getline(cin, sub);
        cout << "\"" << sub << "\" instances: " << FindText(sub, in) << endl << endl;
    }
    if (c == 'r') {
        ReplaceExclamation(in);
        cout << "Edited text: " << in << endl << endl;
    }
    if (c == 's') {
        ShortenSpace(in);
        cout << "Edited text: " << in << endl << endl;
    }
}

int main() {
    string input;
    char c;

    cout << "Enter a sample text:" << endl << endl;
    getline(cin, input);
    cout << "You entered: " << input << endl << endl;

    while (c != 'q') {
        cout << "MENU" << endl;
        PrintMenu();
        cout << "Choose an option:" << endl;
        cin >> c;
        cin.ignore();
        ExecuteMenu(c, input);
    }

    return 0;
}