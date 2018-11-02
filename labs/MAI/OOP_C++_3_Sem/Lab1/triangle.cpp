#include <iostream>
#include <cmath>
#include "triangle.h"
Triangle::Triangle() : Triangle(0, 0, 0)
{
}

Triangle::Triangle(size_t i, size_t j, size_t k) : _sideA(i), _sideB(j), _sideC(k)
{
#ifndef NDEBUG
    std::cout << "T created(" << _sideA + ", " << _sideB + ", " << _sideC + ")" << std::endl;
#endif
}
Triangle::Triangle(std::istream &is)
{
    bool ret = true;
    int sideA;
    int sideB;
    int sideC;
    while (ret)
    {
        is >> sideA;
        is >> sideB;
        is >> sideC;
        if (sideA > 0 && sideB > 0 && sideC > 0)
        {
            ret = false;
            _sideA = sideA;
            _sideB = sideB;
            _sideC = sideC;
        }
        else
        {
            std::cout << "Invalid value, please input one again" << std::endl;
        }
    }
#ifndef NDEBUG
    std::cout << "T created(" << _sideA << ", " << _sideB << ", " << _sideC << ")" << std::endl;
#endif
}
double Triangle::Square()
{
    double res = 0.0;
    double perimetr = (double)(_sideA + _sideB + _sideC);
    double p = perimetr / 2.;
    res = sqrt(p * (p - _sideA) * (p - _sideB) * (p - _sideC));
    return res;
}
void Triangle::Print()
{
    std::cout << "Figure = Triangle. Sides:" << std::endl;
    std::cout << "A=" << _sideA << " "
              << "B=" << _sideB << " "
              << "C=" << _sideC << " "
              << std::endl;
}
Triangle::~Triangle()
{
#ifndef NDEBUG
    std::cout << "T destructed" << std::endl;
#endif
}