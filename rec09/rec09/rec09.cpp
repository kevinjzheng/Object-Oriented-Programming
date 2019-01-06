//
//  rec09.cpp
//  rec09
//
//  Created by Kevin J. Zheng on 11/1/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;

// Abstract Class
class PrintedMaterial {
    // Output Operator
    friend ostream& operator<<(ostream& os, const PrintedMaterial& rhs) {
        os << rhs.numberOfPages << endl;
        return os;
    }
public:
    PrintedMaterial(unsigned pages) : numberOfPages(pages) {}
    // Task 11
//    virtual void displayNumPages() const { cout << numberOfPages << endl; }
    // Task 13
    virtual void displayNumPages() const = 0;
//    void displayNumPages() const { cout << numberOfPages << endl; }
protected:
private:
    // unsigned because # of pages can't be negative so it won't be an int
    // positive numbers and 0
    unsigned numberOfPages;
};

void PrintedMaterial::displayNumPages() const {
    cout << numberOfPages << endl;
}

class Magazine : public PrintedMaterial {
public:
    Magazine(unsigned pages) : PrintedMaterial(pages) {}
    void displayNumPages() const { PrintedMaterial::displayNumPages(); }
protected:
private:
};

class Book : public PrintedMaterial {
public:
    Book(unsigned pages) : PrintedMaterial(pages) {}
    void displayNumPages() const { PrintedMaterial::displayNumPages(); }
protected:
private:
};

class TextBook : public Book {
public:
    TextBook(unsigned pages) : Book(pages) {}
    TextBook(unsigned numPages, unsigned numIndxPgs ) :
        Book(numPages), numOfIndexPages(numIndxPgs) {}
    /* Since Textbook has a displayNumPages method of its own, it uses this
     definition of the method instead of the definition provided in the base
     class */
    void displayNumPages() const {
        cout << "Pages: ";
        // this allows me to acces and get the base class's private variable
        PrintedMaterial::displayNumPages();
        cout << "Index Pages: " << numOfIndexPages << endl;
//        cout << numOfIndexPages << endl;
        /* won't work because its a private of Printed Material */
//        cout << numberOfPages;
    }
protected:
private:
    unsigned numOfIndexPages;
};

class Novel : public Book {
public:
    Novel(unsigned pages) : Book(pages) {}
    void displayNumPages() const { PrintedMaterial::displayNumPages(); }
protected:
private:
};

//void displayNumberOfPages(const PrintedMaterial& rhs) {
//    rhs.displayNumPages();
//}

// tester/modeler code
int main()
{
    //    TextBook t;
    //    Novel n;
    //    Magazine m;

    TextBook t(5430, 234);
    Novel n(213);
    Magazine m(6);
    
    t.displayNumPages();
    n.displayNumPages();
    m.displayNumPages();
//    cout << t;
//    cout << n;
//    cout << m;
    
    // Task 9
    // THIS IS SLICING!!!
//    PrintedMaterial pm = t; // like putting a t into a vector of PrintedMaterials
//    pm.displayNumPages();
    
    cout << "\nA PrintedMaterial material object!\n";
//    PrintedMaterial pm(2345);
    /* the display method of the base class is called */
//    pm.displayNumPages();
    
    cout << "\nA PrintedMaterial variable containing a TextBook value\n";
//    pm = t; // like putting a t into a vector of PrintedMaterials
    /* Although assigned t to pm (Textbook to PrintedMaterials) calling
     displayNumPages on pm would call the display method of the base class and
     not the display method of the textbook derived class */
//    pm.displayNumPages();
    
    PrintedMaterial* pmPtr;
    pmPtr = &t;
    // instead of putting an actual PrintedMaterial
    // object into the vector, we put a pointer to
    // a PrintedMaterial object (t) into a vector
    // of pointers-to-PrintedMaterial
    // (that is, pointers to the Base class)
    // we'll be "managing" our objects by using
    // pointers to PrintedMaterial values.
    
    pmPtr->displayNumPages();
    /* Even though at this point we are using pointers and we created a Printed
     Material pointer and made it point to the address of the Textbook, the
     displayNumPages is called on the PrintedMaterial pointer and there is a
     displayNumPages method in the base class so that is going to compile and
     execute, before the Textbook display was working because you call the display
     method on each derived class itself so if the derived class doesn't have
     that method then it would refer to the method in the base class but if the
     display method is called on the base class and the method is present then
     the method in the base class will be the method that is executed */
    
    /* When you dereference a pointer to an base class in an inheritance
     hierarchy which holds the address of an object of a type that was publicly
     derived from the base class, you get the BASE part of the derived class! */
    
    /* When you dereference a pointer to an base class which has a virtual
     method in an inheritance hierarchy which holds the address of an object of
     a type that was publicly derived from the base class, you get the DERIVED
     class. */
    /* By adding a virtual in front of the method in the base, it allows you to
     make the display method call on the method provided in the derived class as
     compared to the method providedi in the base class */
    
    /* A place that can hold a Base class pointer value can hold a pointer to
     ANY object that inherits from Base. The virtual mechanism is only invoked
     when pointer to base classes are used (or reference to base class in
     function parameters). */
    
//    cout << "----- Task 12 -----" << endl;
//    displayNumberOfPages(t);
//    displayNumberOfPages(n);
//    displayNumberOfPages(m);
    
    /* It also means that any class deriving from that abstract class must
     override that pure virutal method to create a concrete class - that means
     that C++ will allow objects to be created.
    (A concrete class is a class with no pure virtual methods - all pureness
     has been overridden.) */
    
    // Task 15
    cout << "----- Task 15 -----" << endl;
    vector<PrintedMaterial*> printedMats;
    printedMats.push_back(&t);
    printedMats.push_back(&n);
    printedMats.push_back(&m);
    
    for (size_t i = 0; i < printedMats.size(); i++) {
        printedMats[i]->displayNumPages();
    }
    
}
