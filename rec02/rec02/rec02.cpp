//
//  rec02.cpp
//  rec02
//
//  Created by Kevin J. Zheng on 9/13/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Compound {
    int carbon;
    int hydrogen;
    vector<string> names;
};

// function that asks user for a file
void askFile(ifstream& inputFile) {
    string filename;
    cout << "Please provide a filename: ";
    cin >> filename;
    inputFile.open(filename);
//    if fails to open, recall askFile()
    while (!inputFile) {
        cerr << "Failed to open file. Please try again." << endl;
        inputFile.clear();
        askFile(inputFile);
    }
}

// groups hydrocarbons and fills vector which is passed by reference
void fillVector(ifstream& file, vector<Compound>& hydros) {
    string names;
    char junk;
    int numCarbon;
    int numHydrogen;
    while (file >> names >> junk >> numCarbon >> junk >> numHydrogen) {
        bool existingIdenticalProperties = false;
        Compound tempCompound;
        tempCompound.carbon = numCarbon;
        tempCompound.hydrogen = numHydrogen;
        for (Compound& hydro : hydros) {
            if (hydro.carbon  == tempCompound.carbon &&
                hydro.hydrogen == tempCompound.hydrogen) {
                hydro.names.push_back(names);
                existingIdenticalProperties = true;
            }
        }
        // checks if compound with same number of carbons and hydrogens exists
        if (!existingIdenticalProperties) {
            tempCompound.names.push_back(names);
            tempCompound.carbon = numCarbon;
            tempCompound.hydrogen = numHydrogen;
            hydros.push_back(tempCompound);
        }
    }
    file.close();
}

// selection sort which first compares number of carbon and then hydrogen
void sortCarbons(vector<Compound>& compounds) {
    for (int i = 0; i < compounds.size() - 1; i++)
    {
        int minIndex = i;
        for (int j = i+1; j < compounds.size(); j++)
            if (compounds[j].carbon < compounds[minIndex].carbon) {
                minIndex = j;
            } else if (compounds[j].carbon == compounds[minIndex].carbon) {
//                compare hydrogen atoms if carbons are equal
                if (compounds[j].hydrogen < compounds[minIndex].hydrogen) {
                    minIndex = j;
                }
            }
//        swap elements using temp variable
        Compound temp = compounds[minIndex];
        compounds[minIndex] = compounds[i];
        compounds[i] = temp;
    }
}

void printCompounds(const vector<Compound>& compounds) {
    for (int i = 0; i < compounds.size(); i++) {
        cout << "C" << compounds[i].carbon << "H";
        cout << compounds[i].hydrogen;
//        print all of the names of the compounds
        for (int j = 0; j < compounds[i].names.size(); j++) {
            cout << " " << compounds[i].names[j];
        }
        cout << endl;
    }
}

int main() {
    ifstream inputFile;
    askFile(inputFile);
    vector<Compound> compounds;
    fillVector(inputFile, compounds);
    sortCarbons(compounds);
    printCompounds(compounds);
}
