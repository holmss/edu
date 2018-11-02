#include <iostream>
#include "TVector.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Square.h"

void menu () {
    std::cout << "Choose an operation:" << std::endl;
    std::cout << "1) Add triangle" << std::endl;
    std::cout << "2) Add rectangle" << std::endl;
    std::cout << "3) Add square" << std::endl;
    std::cout << "4) Get by Index" << std::endl;
    std::cout << "5) Print list" << std::endl;
    std::cout << "6) Delete by Index" << std::endl;
    std::cout << "0) Exit" << std::endl;
}

int main () {
    int32_t action = 0;
    TVector tVector(1);
    std::shared_ptr <Figure> ptr;
    do {
        menu();
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
                    std::cout << "Index out of range" << std::endl;
                }
                break;
            case 5:
                std::cout << tVector << std::endl;
                break;
                case 6:
                std::cin >> action;
                if (action <= tVector.Capacity() - 1)
                tVector.Remove(action);
            else {
                std::cout << "Index out of range" << std::endl;
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
