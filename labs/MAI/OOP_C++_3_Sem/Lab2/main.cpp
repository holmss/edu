#include "triangle.h"
#include "tMass.h"

int main (int argc, char **argv) {
    TMass *mass = new TMass();
    mass->AddToFirstFree(Triangle(1, 1, 1));
    mass->AddToFirstFree(Triangle(2, 2, 2));
    mass->AddToFirstFree(Triangle(3, 3, 3));
    mass->AddToFirstFree(Triangle(4, 4, 4));

    std::cout << " Internal mass size = " << mass->GetInternalMassSize()
              << std::endl;

    std::cout << " All mass:\n" << *mass << std::endl;

    std::cout << " " << mass->Replace(Triangle(1, 2, 2), Triangle(10, 10, 10))
              << std::endl;  //неудачная попытка замены
    std::cout << " " << mass->Replace(Triangle(3, 3, 3), Triangle(10, 10, 10))
              << std::endl;  //удачная попытка замены

    std::cout << " All mass:\n" << *mass << std::endl;
    delete mass;

    return 0;
}
