//
//  rec10.cpp
//  rec10
//
//  Created by Kevin J. Zheng on 11/8/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;

class Instrument {
public:
    virtual void makeSound() const = 0;
    virtual void playSound() const = 0;
};

void Instrument::makeSound() const { cout << "To make a sound... "; }

class Brass : public Instrument {
public:
    Brass(const unsigned mouthpiece) : mouthpiece(mouthpiece) { }
    void makeSound() const {
        Instrument::makeSound();
        cout << "blow on a mouthpiece of size " << mouthpiece << endl;
    }
    virtual void playSound() const = 0;
private:
    unsigned mouthpiece;
};
class String : public Instrument {
public:
    String(const unsigned pitch) : pitch(pitch) { }
    void makeSound() const {
        Instrument::makeSound();
        cout << "bow a string with pitch " << pitch << endl;
    }
    virtual void playSound() const = 0;
private:
    unsigned pitch;
};
class Percussion : public Instrument {
public:
    Percussion() { }
    void makeSound() const {
        Instrument::makeSound();
        cout <<  "hit me!" << endl;
    }
    virtual void playSound() const = 0;
};

class Trombone : public Brass {
public:
    Trombone(const unsigned mouthpiece) : Brass(mouthpiece) { }
    void playSound() const { cout << "Blat"; }
};
class Trumpet : public Brass {
public:
    Trumpet(const unsigned mouthpiece) : Brass(mouthpiece) { }
    void playSound() const { cout << "Toot"; }
};
class Cello : public String {
public:
    Cello(const unsigned pitch) : String(pitch) { }
    void playSound() const { cout << "Squawk"; }
};
class Violin : public String {
public:
    Violin(const unsigned pitch) : String(pitch) { }
    void playSound() const { cout << "Screech"; }
};
class Drum : public Percussion {
public:
    Drum() : Percussion() { }
    void playSound() const { cout << "Boom"; }
};
class Cymbal : public Percussion {
public:
    Cymbal() : Percussion() { }
    void playSound() const { cout << "Crash"; }
};

class MILL {
public:
    MILL() {}
    void receiveInstr(Instrument& rhs) {
        for (size_t i = 0; i < inventory.size(); i++) {
            if (inventory[i] == nullptr) {
                inventory[i] = &rhs;
                return;
            }
        }
        inventory.push_back(&rhs);
    }
    void dailyTestPlay() const {
        for (Instrument* instrument : inventory) {
            if (instrument != nullptr) {
                instrument->makeSound();
            }
        }
    }
    Instrument* loanOut() {
        for (size_t i = 0; i < inventory.size(); i++) {
            Instrument* instrument = inventory[i];
            if (instrument != nullptr) {
                inventory[i] = nullptr;
                return instrument;
            }
        }
        return nullptr;
    }
private:
    vector<Instrument*> inventory;
};

class Musician {
public:
    Musician() : instr(nullptr) {}
    
    void acceptInstr(Instrument* instPtr) { instr = instPtr; }
    
    Instrument* giveBackInstr() {
        Instrument* result(instr);
        instr = nullptr;
        return result;
    }
    
    void testPlay() const {
        if (instr) instr->makeSound();
        else cerr << "have no instr\n";
    }
    
    void orchPlay() const {
        if (instr) instr->playSound();
//        else cerr << "orch player has no instr\n";
    }
    
private:
    Instrument* instr = nullptr;
};

class Orch {
public:
    Orch() { }
    void addPlayer(Musician& musician) {
        orchestra.push_back(&musician);
    }
    void play() const {
        for (Musician* musician : orchestra) {
            musician->orchPlay();
        }
        cout << "\n";
    }
private:
    vector<Musician*> orchestra;
};

int main() {
//     PART ONE
//
//     cout << "Define some instruments ----------------------------------------\n";
//     Drum drum;
//     Cello cello(673);
//     Cymbal cymbal;
//     Trombone tbone(4);
//     Trumpet trpt(12) ;
//     Violin violin(567) ;
//
//     // use the debugger to look at the mill
//     cout << "Define the MILL ------------------------------------------------\n";
//     MILL mill;
//
//     cout << "Put the instruments into the MILL ------------------------------\n";
//     mill.receiveInstr(trpt);
//     mill.receiveInstr(violin);
//     mill.receiveInstr(tbone);
//     mill.receiveInstr(drum);
//     mill.receiveInstr(cello);
//     mill.receiveInstr(cymbal);
//
//     cout << "Daily test -----------------------------------------------------\n";
//     cout << endl;
//     cout << "dailyTestPlay()" << endl;
//     mill.dailyTestPlay();
//     cout << endl;
//
//     cout << "Define some Musicians-------------------------------------------\n";
//     Musician harpo;
//     Musician groucho;
//
//     cout << "TESTING: groucho.acceptInstr(mill.loanOut());-----------------------\n";
//     groucho.testPlay();
//     cout << endl;
//     groucho.acceptInstr(mill.loanOut());
//     cout << endl;
//     groucho.testPlay();
//     cout << endl;
//     cout << "dailyTestPlay()" << endl;
//     mill.dailyTestPlay();
//
//     cout << endl << endl;
//
//     groucho.testPlay();
//     cout << endl;
//     mill.receiveInstr(*groucho.giveBackInstr());
//     harpo.acceptInstr(mill.loanOut());
//     groucho.acceptInstr(mill.loanOut());
//     cout << endl;
//     groucho.testPlay();
//     cout << endl;
//     harpo.testPlay();
//     cout << endl;
//     cout << "dailyTestPlay()" << endl;
//     mill.dailyTestPlay();
//
//     cout << "TESTING: mill.receiveInstr(*groucho.giveBackInstr()); ----\n";
//
//     // fifth
//     mill.receiveInstr(*groucho.giveBackInstr());
//     cout << "TESTING: mill.receiveInstr(*harpo.giveBackInstr()); ------\n";
//     mill.receiveInstr(*harpo.giveBackInstr());
//
//
//     cout << endl;
//     cout << "dailyTestPlay()" << endl;
//     mill.dailyTestPlay();
//     cout << endl;
//
//     cout << endl;

//    PART TWO
//    The initialization phase
    
    Drum drum;
    Cello cello(673);
    Cymbal cymbal;
    Trombone tbone(4);
    Trumpet trpt(12);
    Violin violin(567);

    MILL mill;
    mill.receiveInstr(trpt);
    mill.receiveInstr(violin);
    mill.receiveInstr(tbone);
    mill.receiveInstr(drum);
    mill.receiveInstr(cello);
    mill.receiveInstr(cymbal);

    Musician bob;
    Musician sue;
    Musician mary;
    Musician ralph;
    Musician jody;
    Musician morgan;

    Orch orch;

//  //   THE SCENARIO

//  //   Bob joins the orchestra without an instrument.
    orch.addPlayer(bob);

//    //The orchestra performs
    cout << "orch performs\n";
    orch.play();

    //Sue gets an instrument from the MIL2 and joins the orchestra.
    sue.acceptInstr(mill.loanOut());
    orch.addPlayer(sue);

    //Ralph gets an instrument from the MIL2.
    ralph.acceptInstr(mill.loanOut());

    //Mary gets an instrument from the MIL2 and joins the orchestra.
    mary.acceptInstr(mill.loanOut());
    orch.addPlayer(mary);

    //Ralph returns his instrument to the MIL2.
    mill.receiveInstr(*ralph.giveBackInstr());

    //Jody gets an instrument from the MIL2 and joins the orchestra.
    jody.acceptInstr(mill.loanOut());
    orch.addPlayer(jody);

    // morgan gets an instrument from the MIL2
    morgan.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Ralph joins the orchestra.
    orch.addPlayer(ralph);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    // bob gets an instrument from the MIL2
    bob.acceptInstr(mill.loanOut());

    // ralph gets an instrument from the MIL2
    ralph.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Morgan joins the orchestra.
    orch.addPlayer(morgan);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

}

