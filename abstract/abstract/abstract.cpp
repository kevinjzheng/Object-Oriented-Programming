//
//  abstract.cpp
//  abstract
//
//  Created by Kevin J. Zheng on 10/31/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.
//

#include <iostream>
using namespace std;

class Shape { // Abstract Class: any class with at least one abstract method
public:
    Shape(int x, int y) : x(x), y(y) { }
    void move (int x, int y) { this->x = x; this->y = y;}
    // virtual void draw() { }
    virtual void draw() = 0; // abstract method, aka "pure virtual"
    /* a method that is stated to be present saying that all the derived classes
     must have this method but the way is implemented could be different for its
     derived classes and its pure because in the base no info is provided about
     the method. Other derived classes will not work until each derived class
     has overwritten the draw method */
    /* Will get a compile error is a derived class is being called to create
     an instance of it, else, compiling it without calling to make an instance
     of it will not throwback a compilation error */
    void commonDrawCode() { cout << "commonDrawCode\n"; }
private:
    int x, y;
};

// works as long as you define it outside of the class
// providing default code for the abstract class
void Shape::draw() { cout << "common drawing code\n"; }

class Triangle : public Shape {
public:
    Triangle(int x, int y) : Shape(x,y) {}
    void draw() {
//        commonDrawCode();
        Shape::draw();
        cout << "Triangle drawing. ";
    }
};

class Circle : public Shape {
public:
    Circle(int x, int y) : Shape(x,y) {}
};

class Square : public Shape {
public:
    Square(int x, int y) : Shape(x,y) {}
};

int main() {
    Triangle(2,3);
}
