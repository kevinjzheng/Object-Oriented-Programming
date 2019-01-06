//
//  recursion.cpp
//  recursion
//
//  Created by Kevin J. Zheng on 12/5/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.
//

// Towers of Hinoy

#include <iostream>
using namespace std;

void tower(int count, char start, char target, char spare) {
    if (count > 0) {
        tower(count - 1, start, spare, target);
        cout << "Move disk: " << count << " from spindle " << start
        << " to spindle " << target << endl;
        tower(count - 1, spare, target, start);
    }
    // or
    // if (count == 0) { return; }
    
}

void printDigits(int n) {
    if (n < 10) {
        cout << n << ' ';
    }
    else {
        printDigits(n/10);
        cout << n % 10 << ' ';
    }
}

int main() {
    printDigits(123456);
}
