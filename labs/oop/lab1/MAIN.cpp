#include <cstdlib>
#include "PENTAGON.h"
#include "HEXAGON.h"
#include "OCTAGON.h"

int main() {

	std::cout << "Enter the pentagon side value" << std::endl;
    Figure *ptrP = new Pentagon(std::cin);
    
    std::cout << "Enter the hexagon side value" << std::endl;
    Figure *ptrH = new Hexagon(std::cin);
    
    std::cout << "Enter the octagon side value" << std::endl;
    Figure *ptrO = new Octagon(std::cin);
    
    std::cout << "Pentagon side and square: " << std::endl;
    ptrP->Print();
    std::cout << ptrP->Square() << std::endl;
    
    std::cout << "Hexagon side and square: " << std::endl;
    ptrH->Print();
    std::cout << ptrH->Square() << std::endl;
    
    std::cout << "Octagon side and square: " << std::endl;
    ptrO->Print();
	std::cout << ptrO->Square() << std::endl;

    delete ptrP;
    delete ptrH;
    delete ptrO;
    
    return 0;
}
