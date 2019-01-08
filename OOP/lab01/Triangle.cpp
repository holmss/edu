#include "Triangle.hpp"
#include <cmath>

Triangle::Triangle () : Triangle(0, 0, 0) {
}

Triangle::Triangle (size_t i, size_t j, size_t k)
        : sideA(i), sideB(j), sideC(k) {
#ifndef NDEBUG
    std::cout << "T created(" << sideA << ", " << sideB << ", " << sideC << ")"
              << std::endl;
#endif
}

Triangle::Triangle (std::istream &is) {
    is >> sideA;
    is >> sideB;
    is >> sideC;
#ifndef NDEBUG
    std::cout << "T created(" << sideA << ", " << sideB << ", " << sideC << ")"
              << std::endl;
#endif
}

bool Triangle::operator == (Triangle &right) {
    bool res = false;
    if (this->sideA == right.sideA && this->sideB == right.sideB &&
        this->sideC == right.sideC) {
        res = true;
    }
    return res;
}

bool Triangle::operator!=(Triangle& right)
{
    return !(*this == right);
}
Triangle& Triangle::operator=(Triangle& right)
{
    if (this != &right) {
#ifndef NDEBUG
        std::cout << "Triangle copied" << std::endl;
#endif
        sideA = right.sideA;
        sideB = right.sideB;
        sideC = right.sideC;
    }
    return *this;
}

Triangle operator + (const Triangle &left, const Triangle &right) {
    return Triangle(left.sideA + right.sideA, left.sideB + right.sideB,
                    left.sideC + right.sideC);
}

std::istream &operator >> (std::istream &is, Triangle &obj) {
    is >> obj.sideA;
    is >> obj.sideB;
    is >> obj.sideC;
    return is;
}

std::ostream &operator << (std::ostream &os, const Triangle &obj) {
    os << obj.sideA << " " << obj.sideB << " " << obj.sideC;
    return os;
}

double Triangle::Square () {
    double res = 0.0;
    double perimetr = (double) (sideA + sideB + sideC);
    double p = perimetr / 2.;
    res = sqrt(p * (p - sideA) * (p - sideB) * (p - sideC));
    return res;
}

void Triangle::Print () {
    std::cout << "Figure = Triangle. Sides: ";
    std::cout << "a=" << sideA << " "
              << "b=" << sideB << " "
              << "c=" << sideC << " " << std::endl;
}

Triangle::~Triangle () {
#ifndef NDEBUG
    std::cout << "T destructed" << std::endl;
#endif
}

Triangle::Triangle (const Triangle &orig) {
    this->sideA = orig.sideA;
    this->sideB = orig.sideB;
    this->sideC = orig.sideC;
}
