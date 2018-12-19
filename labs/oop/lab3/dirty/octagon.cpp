#include "octagon.hpp"
#include <iostream>
#include <math.h>

Octagon::Octagon() : Octagon(0) {
}

Octagon::Octagon(size_t i) : side_a(i) {
    std::cout << "Octagon created: " << side_a << std::endl;
}

Octagon::Octagon(std::istream &is) {
    is >> side_a;
}

Octagon::Octagon(const Octagon& orig) {
    std::cout << "Octagon copy created" << std::endl;
    side_a = orig.side_a;
}

double Octagon::Square() {
    return double(pow(side_a,2)) * 2.0 * (1.0 + pow(2,0.5));

}

void Octagon::Print() {
    std::cout << "a = " << side_a << std::endl;

}

Octagon& Octagon::operator=(const Octagon& right) {
    if (this == &right) 
	    return *this;
    side_a = right.side_a;
    return *this;
}

Octagon& Octagon::operator++() {
    side_a++;
    return *this;
}

bool operator==(const Octagon& left, const Octagon& right) {
     return left.side_a == right.side_a;
}

bool operator!=(const Octagon& left, const Octagon& right) {
     return left.side_a != right.side_a;
}

Octagon operator+(const Octagon& left, const Octagon& right) {
    return Octagon(left.side_a + right.side_a);
}

std::ostream& operator<<(std::ostream& os, const Octagon& pent) {
    os << "o = " << pent.side_a << std::endl;
    return os;
}

std::istream& operator>>(std::istream& is, const Octagon& pent) {
    is >> pent.side_a;
    return is;
}

std::ostream *Octagon::Show(std::ostream &os)
{
    os << *this;
    // std::cout << *this << '\n';
    return &os;
}

Octagon::~Octagon() {
    std::cout << "Octagon deleted" << std::endl;
}                                