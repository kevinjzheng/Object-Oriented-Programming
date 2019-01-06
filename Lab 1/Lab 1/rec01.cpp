//
//  main.cpp
//  Lab 1 - Game of Life
//  Kevin J. Zheng
//

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream inputFile("/Users/lightning/Documents/Fall2018/OOP/Lab 1/Lab 1/life.txt");
    if (!inputFile) { // checks for opening file before trying to read from it
        cerr << "failed to open life" << endl;
        exit(1);
    }
    
    vector<string> oldState;
//    vector<string> newState;
    string line;
    int genNum = 1;
    while (getline(inputFile, line)) {
        oldState.push_back(line);
    }
    inputFile.close();
    
//    for (int i = 0; i < oldState.size(); i++ ) {
//        newState.push_back(oldState[i]);
//    }
    cout << "Intial Generation" << endl;
    for (size_t col = 0; col < oldState.size(); ++col) {
        string newLine;
        for (size_t row = 0; row < oldState[col].size(); ++row) {
            cout << oldState[col][row] << /* col << row << */' ';
        }
        cout << endl;
    }
    for (int n = 0; n < 10; n++) {
        vector<string> newState;
        for (size_t col = 0; col < oldState.size(); ++col) {
            string newLine;
            for (size_t row = 0; row < oldState[col].size(); ++row) {
                int neighbors = 0;
//                cout << oldState[col][row] << /* col << row << */' ';
                if (oldState[col][row] == '*') {    // test cases for alive
                    if (oldState[col-1][row-1] == '*') {
                        neighbors++;
                    }
                    if (oldState[col][row-1] == '*') {
                        neighbors++;
                    }
                    if (oldState[col+1][row-1] == '*') {
                        neighbors++;
                    }
                    if (oldState[col-1][row] == '*') {
                        neighbors++;
                    }
                    if (oldState[col+1][row] == '*') {
                        neighbors++;
                    }
                    if (oldState[col-1][row+1] == '*') {
                        neighbors++;
                    }
                    if (oldState[col][row+1] == '*') {
                        neighbors++;
                    }
                    if (oldState[col+1][row+1] == '*') {
                        neighbors++;
                    }
                    if (neighbors < 2) {
                        newLine += '-';
                    }
                    if (neighbors >= 2)  {
                        if(neighbors > 3) {
                            newLine += '-';
                        }
                        else {
                            newLine += '*';
                        }
                    }
                }
                if (oldState[col][row] == '-') {    // test cases for dead
                    if (oldState[col-1][row-1] == '*') {
                        neighbors++;
                    }
                    if (oldState[col][row-1] == '*') {
                        neighbors++;
                    }
                    if (oldState[col+1][row-1] == '*') {
                        neighbors++;
                    }
                    if (oldState[col-1][row] == '*') {
                        neighbors++;
                    }
                    if (oldState[col+1][row] == '*') {
                        neighbors++;
                    }
                    if (oldState[col-1][row+1] == '*') {
                        neighbors++;
                    }
                    if (oldState[col][row+1] == '*') {
                        neighbors++;
                    }
                    if (oldState[col+1][row+1] == '*') {
                        neighbors++;
                    }
                    if (neighbors == 3) {
                        newLine += '*';
                    }
                    if (neighbors != 3) {
                        newLine += '-';
                    }
                }
            }
            newState.push_back(newLine);
            //cout << endl;
        }
        cout << "Generation " << genNum << endl;
        for (size_t col = 0; col < newState.size(); ++col) {
            for (size_t row = 0; row < newState[col].size(); ++row) {
                cout << newState[col][row] << /* col << row << */ ' ';
            }
            cout << endl;
        }
        oldState = newState;
        genNum++;
    }
}
