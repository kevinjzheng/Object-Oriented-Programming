//
//  main.cpp
//  rec13
//
//  Created by Kevin J. Zheng on 12/6/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.
//
// rec13_test.cpp

#include <iostream>
#include <fstream>
#include <vector>      // task 1
#include <list>        // task 2
#include <algorithm>   // task 3
#include <string>      // task 21
#include <set>         // task 22
#include <map>         // task 23
using namespace std;

class IsEven{
public:
    bool operator() (int target) { return target % even == 0; }
private:
    int even = 2;
};

void print(const list<int>& lst) {
    for (list<int>::const_iterator iter = lst.begin(); iter != lst.end();
         ++iter) {
        cout << *iter << ' ';
    }
}

void print2(const list<int>& lst) {
    for (int num : lst) {
        cout << num << ' ';
    }
}

void printAuto(const list<int>& lst) {
    for (auto iter = lst.begin(); iter != lst.end(); ++++iter) {
        cout << *iter << ' ';
    }
}

list<int>::const_iterator searchList(const list<int>& lst, int target) {
    for (list<int>::const_iterator iter = lst.begin(); iter != lst.end(); ++iter) {
        if (*iter == target) {
            return iter;
        }
    }
    return lst.end();
}

auto searchAuto(const list<int>& lst, int target) {
    for (auto iter = lst.begin(); iter != lst.end(); ++iter) {
        if (*iter == target) {
            return iter;
        }
    }
    return lst.end();
}

bool isEven(int target) {
    return target % 2 == 0;
}

/* not const-iterator because when ourFind was called on list it was passed
 non-const iterators and thus went to the templated one instead, so in this case
 its just iterator */
list<int>::iterator ourFind(list<int>::iterator start, list<int>::iterator stop,
                            int target) {
    cout << "In ourFind!" << endl;
    for (list<int>::iterator iter = start; iter != stop; ++iter) {
        if (*iter == target) {
            cout << "Found!";
            return iter;
        }
    }
    cout << "Not Found!";
    return stop;
}

template <typename Iter, typename T>
Iter ourFind(Iter start, Iter stop, T target) {
    cout << "In ourFind Template!" << endl;
    for (Iter iter = start; iter != stop; ++iter) {
        if (*iter == target) {
            cout << "Found!";
            return iter;
        }
    }
    cout << "Not Found!";
    return stop;
}

bool hasSeen(vector<string>& dict, string word) {
    for(size_t i = 0; i < dict.size(); i++) {
        if (word == dict[i]) {
            return true;
        }
    }
    return false;
}
         
int main() {
    // 1. Create a vector with some values and display using ranged for
    cout << "Task 1:\n";

    vector<int> numVec({82,25,3,16});
    for (int num : numVec) {
        cout << num << ' ';
    }
    
    cout << "\n=======\n";
    
    // 2. Initalize a list as a copy of values from the vector
    cout << "Task 2:\n";
    
    list<int> numList(numVec.begin(), numVec.end());
    for (int num : numList) {
        cout << num << ' ';
    }
    
    cout << "\n=======\n";
    
    // 3. Sort the original vector.  Display both the vector and the list
    cout << "Task 3:\n";
    
    sort(numVec.begin(), numVec.end());
    for (int num : numVec) {
        cout << num << ' ';
    }
    cout << endl;
    for (int num : numList) {
        cout << num << ' ';
    }
    
    cout << "\n=======\n";
    
    // 4. print every other element of the vector.
    cout << "Task 4:\n";
    
    for (size_t i = 0; i < numVec.size(); ++++i) {
        cout << numVec[i] << ' ';
    }
    
    cout << "\n=======\n";
    
    // 5. Attempt to print every other element of the list using the
    //    same technique.
    cout << "Task 5:\n";
    
    for (size_t i = 0; i < numList.size(); ++++i) {
//        cout << numList[i] << ' ';    // list type has no subscript operator
    }
    
    cout << "\n=======\n";
    
    //
    // Iterators
    //
    
    // 6. Repeat task 4 using iterators.  Do not use auto;
    cout << "Task 6:\n";
    
    for (vector<int>::iterator numIter = numVec.begin();
         numIter != numVec.end(); ++++numIter) {
        cout << *numIter << ' ';
    }
    
    cout << "\n=======\n";
    
    // 7. Repeat the previous task using the list.  Again, do not use auto.
    //    Note that you cannot use the same simple mechanism to bump
    //    the iterator as in task 6.
    cout << "Task 7:\n";
    
    for (list<int>::iterator numIter = numList.begin();
         numIter != numList.end(); ++++numIter) {
        cout << *numIter << ' ';
    }
    
    cout << "\n=======\n";
    
    // 8. Sorting a list
    cout << "Task 8:\n";
    
    numList.sort();
    for (list<int>::iterator numIter = numList.begin();
         numIter != numList.end(); ++numIter) {
        cout << *numIter << ' ';
    }
    
    cout << "\n=======\n";
    
    // 9. Calling the function to print the list
    cout << "Task 9:\n";
    
    print(numList);
    
    cout << "\n=======\n";
    
    // 10. Calling the function that prints the list, using ranged-for
    cout << "Task 10:\n";
    
    print2(numList);
    
    cout << "\n=======\n";
    
    //
    // Auto
    //
    
    // 11. Calling the function that, using auto, prints alterate
    // items in the list
    cout << "Task 11:\n";
    
    printAuto(numList);
    
    cout << "\n=======\n";
    
    
    // 12.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 12:\n";
    
    if ((searchList(numList, 3)) != numList.end()) cout << "Found" << endl;
    if ((searchList(numList, 5)) == numList.end()) cout << "Not Found";
    
    cout << "\n=======\n";
    
    // 13.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 13:\n";
    
    if ((searchAuto(numList, 3)) != numList.end()) cout << "Found" << endl;
    if ((searchAuto(numList, 5)) == numList.end()) cout << "Not Found";
    
    cout << "\n=======\n";
    
    //
    // Generic Algorithms
    //
    
    // 14. Generic algorithms: find
    cout << "Task 14:\n";
    
    if ((find(numList.begin(), numList.end(), 3)) != numList.end()) cout << "Found" << endl;
    if ((find(numList.begin(), numList.end(), 5)) == numList.end()) cout << "Not Found";
    
    cout << "\n=======\n";
    
    // 15. Generic algorithms: find_if
    cout << "Task 15:\n";
    
    cout << *(find_if(numList.begin(), numList.end(), isEven));
    
    cout << "\n=======\n";
    
    // 16. Functor
    cout << "Task 16:\n";
    
    IsEven isEvenFunctor;
    /* A functor is an instance of a class that has implemented the
     "parenthesis operator", aka the function call operator. */
    cout << *(find_if(numList.begin(), numList.end(), isEvenFunctor));
    
    cout << "\n=======\n";
    
    // 17. Lambda
    cout << "Task 17:\n";
    
    /* The syntax for defining a lambda expression requires a pair of square
     brackets. Inside the square brackets there may be specified a list of
     variables that would be "captured". */
    
    /* And the point of lamda expressions is to minimize what you need to
     write. So if you don't need any parameters, then you dodn't even need a
     parameter list! If you do need parameters, then the parameter list would
     go right after the square brackets. */
    
//    [] (int a, int b) { cout << a + b << endl; } (4, 5); // example
    
    /*
    // without return type
    int result = [] (int a, int b) { return a + b; } (4, 5);
    cout << "the result is: " << result << endl;
    
    // with return type -> int
    int result2 = [] (int a, int b) -> int { return a + b; } (4, 5);
    cout << "the result is: " << result2 << endl;
     */
    
    for (auto iter = numList.begin(); iter != numList.end(); ++iter) {
        bool isEvenLambda = [] (int num) { return num % 2 == 0; } (*iter);
        if (isEvenLambda) {
            cout << "The first even number is: " << *iter;
            break;
        }
    }
    
    cout << "\n=======\n";
    
    // 18. Generic algorithms: copy to an array
    cout << "Task 18:\n";
    
    int array[4];
    copy(numList.begin(), numList.end(), array);
    for (const int& num : array) {
        cout << num << ' ';
    }
    cout << endl;
    if (find(array, array+4, 3) != array+4) cout << "Found" << endl;
    if (find(array, array+4, 5) == array+4) cout << "Not Found";
    
    cout << "\n=======\n";
    
    //
    // Templated Functions
    //
    
    // 19. Implement find as a function for lists
    cout << "Task 19:\n";
    
    ourFind(numList.begin(), numList.end(), 5);
    /* numList was never const but in task 9 it was passed as a const ref as a
     param. So inside the function print, in that scope, the list was a const so
     the iterators were const_iterators and the compiler doesnt like casting
     an iterator to a const_iterator so it would default to template one instead
     of casting an iterator to const_iterator */
    
    cout << "\n=======\n";
    
    // 20. Implement find as a templated function
    cout << "Task 20:\n";
    
    ourFind(numVec.begin(), numVec.end(), 3);
    cout << endl;
    ourFind(numList.begin(), numList.end(), 3);
    
    cout << "\n=======\n";
    
    //
    // Associative collections
    //
    
    // 21. Using a vector of strings, print a line showing the number
    //     of distinct words and the words themselves.
    cout << "Task 21:\n";
    
    ifstream inFile("read.txt");
    string word;
    vector<string> seen;
    while (inFile >> word) {
        if (!hasSeen(seen,word)) {
            seen.push_back(word);
        }
    }
    for (const string& word : seen) {
        cout << word << ' ';
    }
    cout << "\nVector size: " << seen.size();
    inFile.close();
    
    cout << "\n=======\n";
    
    // 22. Repeating previous step, but using the set
    cout << "Task 22:\n";
    
    // set uses find and insert
    
    ifstream ifs("read.txt");
    set<string> seenSet;
    while (ifs >> word) {
        seenSet.insert(word);
    }
    for (const string& word : seenSet) {
        cout << word << ' ';
    }
    cout << "\nSet size: " << seenSet.size();
    ifs.close();
    
    cout << "\n=======\n";
    
    // 23. Word co-occurence using map
    cout << "Task 23:\n";
    
    ifstream mapRead("read.txt");
    map<string, vector<int>> wordMap;
    int count = 0;
    while (mapRead >> word) {
        wordMap[word].push_back(count);
        count ++;
    }
    for (const auto& string : wordMap) {
        cout << string.first << ' ';
        for (size_t i = 0; i < string.second.size(); i++) {
            cout << string.second[i] << ' ';
        }
        cout << endl;
    }
    mapRead.close();
    cout << "\n=======\n";
}
