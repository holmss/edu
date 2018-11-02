#ifndef SQUARE_H
#define SQUARE_H

#include <iostream>
#include "Figure.h"

class TSquare : public Figure {
public:
    TSquare ();

    TSquare (std::istream &is);

    TSquare (size_t side);

    friend std::ostream &operator << (std::ostream &os, const TSquare &obj);

    friend std::istream &operator >> (std::istream &is, TSquare &obj);

    double Square () override;

    void Print () override;

    virtual ~TSquare ();

private:
    size_t _side;
};

#endif // !SQUARE_H