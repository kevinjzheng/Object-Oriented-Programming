//
//  library.cpp
//  library
//
//  Created by Kevin J. Zheng on 10/3/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;

class Book {
public:
    Book(const string& title) : title(title) {}
private:
    string title;
};

class Library {
    friend ostream& operator << (ostream& os, const Library& lib) {
        return os;
    }
    
public:
    // Destructor
    ~Library() {
        for (size_t i = 0; i < books.size(); i++) {
            delete books[i];
        }
        books.clear();  // vector is size 0
    }
private:
    vector<Book*> books;
    
};
 
int main () {
    
}
