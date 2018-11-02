#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <iostream>
#include "Figure.h"

class Rectangle : public Figure {
public:
    Rectangle ();

    explicit Rectangle (std::istream &is);

    Rectangle (size_t sideA, size_t sideB);

    // Rectangle (const Rectangle &orig);

    friend std::ostream &operator << (std::ostream &os, Rectangle &obj);

    friend std::istream &operator >> (std::istream &is, Rectangle &obj);

    double Square ();

    void Print ();

    ~Rectangle ();

private:
    size_t _sideA;
    size_t _sideB;
};

#endif // !RECTANGLE_H