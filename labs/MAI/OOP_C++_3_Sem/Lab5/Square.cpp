#include <iostream>
#include <cmath>
#include "Square.h"
TSquare::TSquare()
{
    TSquare::TSquare(0);
}

TSquare::TSquare(size_t side)
{
    _side = side;
#ifndef NDEBUG
    std::cout << "TSquare created(" << _side << " )" << std::endl;
#endif
}
TSquare::TSquare(std::istream &is)
{
    bool ret = true;
    int side;
    while (ret)
    {
        is >> side;
        if (side > 0)
        {
            ret = false;
            _side = side;
        }
        else
        {
            std::cout << "Invalid values, please input one again" << std::endl;
        }
    }
#ifndef NDEBUG
    std::cout << "TSquare created(" << _side << " )" << std::endl;
#endif
}
double TSquare::Square()
{
    double res = 0.0;
    res = (double)_side * _side;
    return res;
}
void TSquare::Print()
{
    std::cout << "Figure = TSquare. Side: " << _side << std::endl;
}
TSquare::~TSquare()
{
#ifndef NDEBUG
    std::cout << "TSquare destructed" << std::endl;
#endif
}

std::istream &operator >> (std::istream &is, TSquare &obj) {
    is >> obj._side;
    return is;
}

std::ostream &operator << (std::ostream &os, const TSquare &obj) {
    os << obj._side;
    return os;
}