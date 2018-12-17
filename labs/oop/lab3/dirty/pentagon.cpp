#include "pentagon.hpp"
#include <math.h>
#include <iostream>

Pentagon::Pentagon() : Pentagon(0) {
}

Pentagon::Pentagon(size_t i) : side_a(i) {
}

Pentagon::Pentagon(std::istream &is) {
    is >> side_a;
}

Pentagon::Pentagon(const Pentagon& orig) {
    side_a = orig.side_a;
}

double Pentagon::Square() {
    return double(pow(side_a,2)) * pow(25.0 + 10.0 * pow(5,0.5),0.5)/ 4.0;

}

void Pentagon::Print() {
    std::cout << side_a << std::endl;

}

Pentagon& Pentagon::operator=(const Pentagon& right) {
    if (this == &right) 
	    return *this;
    side_a = right.side_a;
    return *this;
}

Pentagon& Pentagon::operator++() {
    side_a++;
    return *this;
}

bool operator==(const Pentagon& left, const Pentagon& right) {
     return left.side_a == right.side_a;
}

bool operator!=(const Pentagon& left, const Pentagon& right) {
     return left.side_a != right.side_a;
}

Pentagon operator+(const Pentagon& left, const Pentagon& right) {
    return Pentagon(left.side_a + right.side_a);
}

std::ostream& operator<<(std::ostream& os, const Pentagon& pent) {
    os << "p = " << pent.side_a << std::endl;
    return os;
}

std::istream& operator>>(std::istream& is, const Pentagon& pent) {
    is >> pent.side_a;
    return is;
}

std::ostream *Pentagon::Show(std::ostream &os)
{
    os << *this;
    // std::cout << *this << '\n';
    return &os;
}

Pentagon::~Pentagon() {
}
