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
    std::cout << "h " << side_a;

}

Hexagon::~Hexagon() {
    std::cout << "Hexagon deleted" << std::endl;
}
