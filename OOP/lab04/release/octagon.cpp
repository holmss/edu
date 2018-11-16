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
    std::cout << "o " << side_a;

}

Octagon::~Octagon() {
    std::cout << "Octagon deleted" << std::endl;
}