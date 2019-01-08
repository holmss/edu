#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Figure.hpp"
#include <iostream>

class Triangle : public Figure {
public:
    Triangle();
    explicit Triangle(std::istream& is);
    Triangle(size_t i, size_t j, size_t k);
    Triangle(const Triangle& orig);
    friend Triangle operator+(const Triangle& left, const Triangle& right);
    bool operator==(Triangle& right);
    bool operator!=(Triangle& right);
    Triangle& operator=(Triangle& right);
    friend std::ostream& operator<<(std::ostream& os, const Triangle& obj);
    friend std::istream& operator>>(std::istream& is, Triangle& obj);
    // friend Triangle& operator==(Triangle& lft, Triangle& rig);
    // friend Triangle& operator!=(Triangle& lft, Triangle& rig);
    double Square() override;
    void Print() override;
    ~Triangle() override;

private:
    size_t sideA;
    size_t sideB;
    size_t sideC;
};

#endif // !TRIANGLE_H