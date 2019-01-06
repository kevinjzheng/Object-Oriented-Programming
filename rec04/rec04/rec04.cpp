//
//  rec04.cpp
//  rec04
//
//  Created by Kevin J. Zheng on 9/27/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

//    int* p;     // it's very clear that the * is part of the type's name - the type is "pointer to int"
// PREFERRED
//    int *p;     // it looks the * is part of the variable name but the compiler reads it as above
//    int * p;    // it looks more like multiplication but the compiler again reads it as above
// (probably NOT a good idea to use)
//    int* p1, p2, *p3;   // This is compile-able code but's it's VERY unclear as the type of p2.
// Since the * is part of the type's name, it's clear that p1 is an int*; and it's pretty clear that
//  p3 is an int* but notice that it looks like p2 is also an int* - but it's not!
// (definitely NOT a good idea to mix int and int* definitions

struct Complex {
    double real;
    double img;
};

class Colour {
public:
    Colour(const string& name, unsigned r, unsigned g, unsigned b)
    : name(name), r(r), g(g), b(b) {}
    void display() const {
        cout << name << " (RBG: " << r << "," << g<< "," << b << ")";
    }
private:
    string name;      // what we call this colour
    unsigned r, g, b; // red/green/blue values for displaying
};

class SpeakerSystem {
public:
    void vibrateSpeakerCones(unsigned signal) const {
        
        cout << "Playing: " << signal << "Hz sound..." << endl;
        cout << "Buzz, buzzy, buzzer, bzap!!!\n";
    }
};

class Amplifier {
public:
    void attachSpeakers(/*const*/ SpeakerSystem& spkrs)
    {
        if(attachedSpeakers)
            cout << "Already have speakers attached!\n";
        else
            attachedSpeakers = &spkrs;
    }
    
    void detachSpeakers() { // should there be an "error" message if not attached?
        attachedSpeakers = nullptr;
    }
    
    void playMusic( ) const {
        if (attachedSpeakers)
            attachedSpeakers -> vibrateSpeakerCones(440);
        else
            cout << "No speakers attached\n";
    }
private:
    SpeakerSystem* attachedSpeakers = nullptr;
};

class Person {
public:
    Person(const string& name) : name(name) {}
    void movesInWith(Person& newRoomate) {
        if (this == &newRoomate ) {
            cout << "You can't move in with yourself!" << endl;
        } else {
            if (roomie || newRoomate.roomie) {
                cout << "Already has a roomie" << endl;
            }
            else {
                roomie = &newRoomate;        // now I have a new roomie
                newRoomate.roomie = this;    // and now they do too
            }
        }
        
    }
    const string& getName() const { return name; }
    // Don't need to use getName() below, just there for you to use in debugging.
    const string& getRoomiesName() const { return roomie->getName(); }
private:
    Person* roomie;
    string name;
};

int main() {
    int x;
    x = 10;
    cout << "x = " << x << endl;
    cout << 0xB << endl;
    int* p;
    p = &x;
//    p = 0x00007ffeefbff5cc;
    cout << "p = " << p << endl;
    
    *p = -2763;
    cout << "p points to where " << *p << " is stored\n";
    cout << "*p contains " << *p << endl;
    cout << "x now contains " << x << endl;
    
    int y(13);
    cout << "y contains " << y << endl;
    p = &y;
    cout << "p now points to where " << *p << " is stored\n";
    cout << "*p now contains " << *p << endl;
    *p = 980;
    cout << "p points to where " << *p << " is stored\n";
    cout << "*p now contains " << *p << endl;
    cout << "y now contains " << y << endl;

    int* q;
    q = p;
    cout << "q points to where " << *q << " is stored\n";
    cout << "*q contains " << *q << endl;

    double d(33.44);
    double* pD(&d);
    *pD = *p;
    *pD = 73.2343;
    *p  = *pD;
    *q  = *p;
//    pD  = p;
//    p   = pD;
    
//    int joe = 24;
//    const int sal = 19;
//    int*  pI;
//      pI = &joe;
//     *pI = 234;
//      pI = &sal;    // cant assign const int* to int*
//     *pI = 7623;
//
//    const int* pcI; // type const int*, you can't change the value of the
//                         pointer but you can change where its pointing to
//      pcI = &joe;
//     *pcI = 234;    // read only variable is not assignable
//      pcI = &sal;
//     *pcI = 7623;   // read only variable is not assignable
//
//    int* const cpI; // error because when creating the const pointer there is no given value
//    int* const cpI(&joe); // won't complain because it is intialized with a value
//    /int* const cpI(&sal);
//      cpI = &joe;   // won't check if its the same value as intialized and thus give an error
//     *cpI = 234;    // you can change the value
//      cpI = &sal;  // but you cant change the pointer
//     *cpI = 7623;
//
//    const int* const cpcI; // again, if you cant change the value of the pointer and where
//                             if intialized without a value then will return error
//    const int* const cpcI(&joe); // wont return an error because intialized with a value
//                                  but it wont allow reassignment
//    const int* const cpcI(&sal);    // error because redefinition
//      cpcI = &joe;  // *cpcI = 234;  error because can't reassign
//      cpcI = &sal;
//     *cpcI = 7623;
    
//    TYPE* variableName; // can hold a pointer to TYPE value

    Complex c = {11.23,45.67};
    Complex* pC(&c);
//    cout << "real: " << *pC.real << "\nimaginary: " << *pC.img << endl;
    cout << "real: " << (*pC).real << "\nimaginary: " << (*pC).img << endl;
    cout << "real: " << pC->real << "\nimaginary: " << (*pC).img << endl;
    
//    class PlainOldClass {
//    public:
//        PlainOldClass() : x(-72) {}
//        int getX() const { return x; }
//        void setX( int val )  { x = val; }
//    private:
//        int x;
//    };
//
//    PlainOldClass poc;
//    PlainOldClass* ppoc( &poc );
//    cout << ppoc->getX() << endl;
//    ppoc->setX( 2837 );
//    cout << ppoc->getX() << endl;
//
//    class PlainOldClassV2 {
//    public:
//        PlainOldClassV2() : x(-72) {}
//        int getX() const { return x; }
//        void setX( int x )  { x = x; } // HMMMM???
//    private:
//        int x
//    };
//
//    int getX( const PlainOldClass* const this = &poc ) const { return x; }
//    void setX( PlainOldClass* const this= &poc, int x )  { x = x; } // Still HMMMM???
//    void setX( int x )  { this->x = x; } // No confusion!
    
    int* pDyn = new int(3); // p points to an int initialized to 3 on the heap
    *pDyn = 17;

    cout << "The " << *pDyn
    << " is stored at address " << pDyn
    << " which is in the heap\n";

    cout << pDyn << endl;
    delete pDyn;
    cout << pDyn << endl;

    cout << "The 17 might STILL be stored at address " << pDyn<< " even though we deleted pDyn\n";
    cout << "But can we dereference pDyn?  We can try.  This might crash... " << *pDyn << ".  Still here?\n";

//    Note if your system modified pDyn when you used delete, then copy pDyn to a second pointer, say pDyn2, and ue in the above print statements.

    pDyn = nullptr;

//    double* pDouble = nullptr;
    
//    cout << "Can we dereference nullptr?  " << *pDyn << endl;
//    cout << "Can we dereference nullptr?  " << *pDouble << endl;
    
    double* pTest = new double(12);
    delete pTest;
    pTest = nullptr;    // pointing to nullptr
    delete pTest; // safe

    short* pShrt = new short(5);
    delete pShrt;
//    delete pShrt;   // can't delete twice?
    
    
//    long jumper = 12238743;
//    delete jumper;
//    long* ptrTolong = &jumper;
//    delete ptrTolong;
//    Complex cmplx;
//    delete cmplx;
    
    vector<Complex*> complV; // can hold pointers to Complex objects
    Complex* tmpPCmplx;      // space for a Complex pointer
    for (size_t ndx = 0; ndx < 3; ++ndx) {
        tmpPCmplx = new Complex; // create a new Complex object on the heap
        tmpPCmplx->real = ndx;   // set real and img to be the
        tmpPCmplx->img  = ndx;   // value of the current ndx
        complV.push_back(tmpPCmplx); // store the ADDRESS of the object in a vector or pointer to Complex
    }
    // display the objects using the pointers stored in the vector
    for (size_t ndx = 0; ndx < 3; ++ndx) {
        cout << complV[ ndx ]->real << endl;
        cout << complV[ ndx ]->img  << endl;
    }
    // release the heap space pointed at by the pointers in the vector
    for (size_t ndx = 0; ndx < 3; ++ndx) {
        delete complV[ndx];
    }
    // clear the vector
    complV.clear();

    vector<Colour*> colours;
    string inputName;
    unsigned inputR, inputG, inputB;

    // fill vector with Colours from the file
    // this could be from an actual file but here we are using the keyboard instead of a file
    // (so we don't have to create an actual file)
    // Do you remember the keystroke combination to indicate "end of file" at the keyboard?
    // somehow the while's test has to fail - from keyboard input
    while (cin >> inputName >> inputR >> inputG >> inputB) {
        colours.push_back(new Colour(inputName, inputR, inputG, inputB));
    }

    // display all the Colours in the vector:
    for (size_t ndx = 0; ndx < colours.size(); ++ndx) {
        colours[ndx]->display();
        cout << endl;
    }


    SpeakerSystem sys1;
    SpeakerSystem sys2;
    Amplifier amp1;
    Amplifier amp2;

    amp1.attachSpeakers(sys1);
//    amp1.attachSpeakers(sys2);
    amp1.playMusic();
    amp1.detachSpeakers();
    amp1.attachSpeakers(sys2);
    amp1.playMusic();
    amp1.detachSpeakers();
    amp1.playMusic();

    // write code to model two people in this world
    Person joeBob("Joe Bob"), billyJane("Billy Jane");
    
    // now model these two becoming roommates
    joeBob.movesInWith(billyJane);
    
    // did this work out?
    cout << joeBob.getName() << " lives with " << joeBob.getRoomiesName() << endl;
    cout << billyJane.getName() << " lives with " << billyJane.getRoomiesName() << endl;
    
    Person spongeBob("Sponge Bob");
    spongeBob.movesInWith(joeBob);
    joeBob.movesInWith(spongeBob);
    spongeBob.movesInWith(spongeBob);
    
}
