#include <iostream>
#include <vector>
using namespace std;

int main() {

    // Declare variables
    int num;
    int input;
    int first;
    int second;
    vector<int> list;

    // Take number of integers
    cin >> num;

    // Take integers and put into list vector
    for(int i = 0; i < num; i++) {
        cin >> input;
        list.push_back(input);
    }

    // Find smallest number
    first = list[0];
    for(int j = 1; j < num; j++) {
        if (list[j] < first) {
            first = list[j];
        }
    }

    // Find second smallest number
    int k = 1;
    second = list[0];
    if (second = first) {
        second = list[1];
        k++;
    }
    for(k; k < num; k++) {
        if (list[k] > first && list[k] < second) {
            second = list[k];
        }
    }

    // Output smallest and second smallest numbers
    cout << first << " and " << second << endl;

    return 0;
}
