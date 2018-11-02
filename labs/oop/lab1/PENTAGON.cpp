#include "PENTAGON.h"
#include <iostream>
#include <math.h>

Pentagon::Pentagon() : Pentagon(0) {
}

Pentagon::Pentagon(size_t i) : side_a(i) {
    std::cout << "Pentagon created: " << side_a << std::endl;
}

Pentagon::Pentagon(std::istream &is) {
    is >> side_a;
}

Pentagon::Pentagon(const Pentagon& orig) {
    std::cout << "Pentagon copy created" << std::endl;
    side_a = orig.side_a;
}

double Pentagon::Square() {
    return double(pow(side_a,2)) * pow(25.0 + 10.0 * pow(5,0.5),0.5)/ 4.0;

}

void Pentagon::Print() {
    std::cout << "a = " << side_a << std::endl;

}

Pentagon::~Pentagon() {
    std::cout << "Pentagon deleted" << std::endl;
}
