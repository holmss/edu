#include <iostream>
#include "TVector.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Square.h"

void Menu () {
    std::cout << "Choose an operation:" << std::endl;
    std::cout << "1) Add triangle" << std::endl;
    std::cout << "2) Add rectangle" << std::endl;
    std::cout << "3) Add square" << std::endl;
    std::cout << "4) Get by Index" << std::endl;
    std::cout << "5) Print vector" << std::endl;
    std::cout << "0) Exit" << std::endl;
}

int main () {
    int action = 0;
    TVector<std::shared_ptr<Figure>> tVector(5);
    std::shared_ptr <Figure> ptr;
    do {
        Menu();
        std::cin >> action;
        switch (action) {
            case 1:
                ptr = std::make_shared <Triangle>(std::cin);
                tVector.FastPushBack(ptr);
                break;
            case 2:
                ptr = std::make_shared <Rectangle>(std::cin);
                tVector.FastPushBack(ptr);
                break;
            case 3:
                ptr = std::make_shared <TSquare>(std::cin);
                tVector.FastPushBack(ptr);
                break;
            case 4:
                std::cin >> action;
                if (action <= tVector.Capacity() - 1)
                    tVector[action]->Print();
                else {
                    std::cout << "Index out of range";
                }
                break;
            case 5:
                for(Iter<std::shared_ptr<Figure>> i = tVector.begin(); i != tVector.end(); i++){
                    i->Print();
                }
                for(auto i: tVector){
                    i->Print();
                }
                break;
            case 0:
                tVector.Clear();
                break;
            default:
                std::cout << "Incorrect command" << std::endl;;
                break;
        }
    } while (action);
    return 0;
}
