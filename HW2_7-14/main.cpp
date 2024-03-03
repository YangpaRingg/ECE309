#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

int main() {

    /* TODO: Declare any necessary variables here. */
    string fileName;

    vector<string> lastNames;
    vector<string> firstNames;
    vector<int> mid1;
    vector<int> mid2;
    vector<int> fin;
    vector<char> letter;

    /* TODO: Read a file name from the user and read the tsv file here. */
    ifstream inFS;
    cin >> fileName; // Read file name
    inFS.open(fileName); // Open file

    if(!inFS.is_open()) {
        cout << "Failed to open input file" << endl;
    }

    while(!inFS.eof() && inFS.good()) {
        string last;
        string first;
        int grade1;
        int grade2;
        int final;

        // Take input from StudentInfo.tsv
        inFS >> last;
        if (inFS.eof()) { // If end of file reached, end loop.
            break;
        }
        inFS >> first;
        inFS >> grade1;
        inFS >> grade2;
        inFS >> final;

        // Put values into respective vectors
        lastNames.push_back(last);
        firstNames.push_back(first);
        mid1.push_back(grade1);
        mid2.push_back(grade2);
        fin.push_back(final); // ISSUE: WHILE LOOP REPEATS ONE EXTRA TIME THAN NEEDED
    }

    inFS.close();

    /* TODO: Compute student grades and exam averages, then output results to a text file here. */
    // Give letter grades to students
    for (int i = 0; i < mid1.size(); i++) {
        int avg;
        avg = (mid1[i] + mid2[i] + fin[i]) / 3;
        if (avg >= 90) {
            letter.push_back('A');
        }
        else if (avg < 90 && avg >= 80) {
            letter.push_back('B');
        }
        else if (avg < 80 && avg >= 70) {
            letter.push_back('C');
        }
        else if (avg < 70 && avg >= 60) {
            letter.push_back('D');
        }
        else if (avg < 60) {
            letter.push_back('F');
        }
    }

    // Compute averages of each exam
    double tot1 = 0;
    double avg1;
    for (int i = 0; i < mid1.size(); i++) {
        tot1 += mid1[i];
    }
    avg1 = tot1 / mid1.size();

    double tot2 = 0;
    double avg2;
    for (int i = 0; i < mid2.size(); i++) {
        tot2 += mid2[i];
    }
    avg2 = tot2 / mid2.size();

    double totfin = 0;
    double avgfin;
    for (int i = 0; i < fin.size(); i++) {
        totfin += fin[i];
    }
    avgfin = totfin / fin.size();

    // Output results to report.txt
    ofstream outFS;
    outFS.open("report.txt");

    if (!outFS.is_open()) {
        cout << "Failed to open output file";
    }

    for (int i = 0; i < lastNames.size(); i++) {
        outFS << lastNames[i] << "\t" << firstNames[i] << "\t" << mid1[i] << "\t" << mid2[i] << "\t" << fin[i] << "\t" << letter[i] << endl;
    }
    outFS << endl;
    outFS << "Averages: midterm1 " << fixed << setprecision(2) << avg1 << ", midterm2 " << avg2 << ", final " << avgfin << endl;

    return 0;
}