#include "hexagon.hpp"
#include <iostream>
#include <math.h>

Hexagon::Hexagon() : Hexagon(0) {
}

Hexagon::Hexagon(size_t i) : side_a(i) {
    std::cout << "Hexagon created: " << side_a << std::endl;
}

Hexagon::Hexagon(std::istream &is) {
    is >> side_a;
}

Hexagon::Hexagon(const Hexagon& orig) {
    std::cout << "Hexagon copy created" << std::endl;
    side_a = orig.side_a;
}

double Hexagon::Square() {
    return double(pow(side_a,2)) * 3.0 * pow(3,0.5)/ 2.0;

}

void Hexagon::Print() {
    std::cout << "h = " << side_a << std::endl;

}

Hexagon& Hexagon::operator=(const Hexagon& right) {
    if (this == &right) 
	    return *this;
    side_a = right.side_a;
    return *this;
}

Hexagon& Hexagon::operator++() {
    side_a++;
    return *this;
}

bool operator==(const Hexagon& left, const Hexagon& right) {
     return left.side_a == right.side_a;
}

bool operator!=(const Hexagon& left, const Hexagon& right) {
     return left.side_a != right.side_a;
}

Hexagon operator+(const Hexagon& left, const Hexagon& right) {
    return Hexagon(left.side_a + right.side_a);
}

std::ostream& operator<<(std::ostream& os, const Hexagon& pent) {
    os << "h = " << pent.side_a << std::endl;
    return os;
}

std::istream& operator>>(std::istream& is, const Hexagon& pent) {
    is >> pent.side_a;
    return is;
}

std::ostream *Hexagon::Show(std::ostream &os)
{
    os << *this;
    // std::cout << *this << '\n';
    return &os;
}

Hexagon::~Hexagon() {
    std::cout << "Hexagon deleted" << std::endl;
}
