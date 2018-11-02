#include <iostream>
#include <cmath>
#include "rectangle.h"
Rectangle::Rectangle() : Rectangle(0, 0)
{
}

Rectangle::Rectangle(size_t sideA, size_t sideB) : _sideA(sideA), _sideB(sideB)
{
#ifndef NDEBUG
    std::cout << "Rectangle created(" << _sideA << _sideB << " )" << std::endl;
#endif
}
Rectangle::Rectangle(std::istream &is)
{
    bool ret = true;
    int sideA;
    int sideB;
    while (ret)
    {
        is >> sideA;
        is >> sideB;
        if (sideA > 0 && sideB > 0)
        {
            ret = false;
            _sideA = sideA;
            _sideB = sideB;
        }
        else
        {
            std::cout << "Invalid values, please input one again" << std::endl;
        }
    }
#ifndef NDEBUG
    std::cout << "Rectangle created(" << _sideA << _sideB << " )" << std::endl;
#endif
}
double Rectangle::Square()
{
    size_t res = 0.0;
    res = _sideA * _sideB;
    return (double)res;
}
void Rectangle::Print()
{
    std::cout << "Figure = Rectangle. Side: "
              << " " << _sideA << " " << _sideB
              << std::endl;
}
Rectangle::~Rectangle()
{
#ifndef NDEBUG
    std::cout << "Rectangle destructed" << std::endl;
#endif
}