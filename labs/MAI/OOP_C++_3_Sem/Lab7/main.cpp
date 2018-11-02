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
    int constT = 10;
    TVector <TVector <std::shared_ptr <Figure>>> toLevelVector(constT);
    int toLevelIndex = 0;
    TVector <std::shared_ptr <Figure>> tVector(constT);
    for (int j = 0; j < constT; ++j) {
        toLevelVector.FastPushBack(tVector);
    }
    int action = 0;
    auto tmp = std::shared_ptr <Figure>(new Triangle(3, 4, 5));

    do {
        Menu();
        std::cin >> action;
        switch (action) {
            case 1:
                tmp = std::shared_ptr <Figure>(new Triangle(std::cin));
                if (toLevelVector[toLevelIndex].Capacity() >= 5) {
                    ++toLevelIndex;
                }
                toLevelVector[toLevelIndex].FastPushBack(tmp);
                //tVector.FastPushBack(tmp);
                break;
            case 2:
                tmp = std::shared_ptr <Figure>(new Rectangle(std::cin));
                if (toLevelVector[toLevelIndex].Capacity() >= 5) {
                    ++toLevelIndex;
                }
                toLevelVector[toLevelIndex].FastPushBack(tmp);
                break;
            case 3:
                tmp = std::shared_ptr <Figure>(new TSquare(std::cin));
                if (toLevelVector[toLevelIndex].Capacity() >= 5) {
                    ++toLevelIndex;
                }
                toLevelVector[toLevelIndex].FastPushBack(tmp);
                break;
            case 4:
                std::cin >> action;
                int index;
                std::cin >> index;
                if ((action <= toLevelVector.Capacity() - 1)
                    && (index <= toLevelVector[action].Capacity() - 1))
                    //std::cout << tVector[action] << std::endl;
                    std::cout << toLevelVector[action][index] << std::endl;
                else {
                    std::cout << "Index out of range";
                }
                break;
            case 5:
                for (auto &i: toLevelVector) {
                    for(auto &k: i){
                        k->Print();
                    }
                }
                break;
            case 6:
                tVector.Sort(0, tVector.Capacity() - 1);
                break;
            case 0:
                break;
            default:
                std::cout << "Incorrect command" << std::endl;;
                break;
        }
    } while (action);
     /*

    std::shared_ptr <Figure> tmp = std::shared_ptr<Figure>(new Triangle(4, 7, 5));
    tVector.FastPushBack(tmp);
    tmp = std::shared_ptr<Figure>(new Rectangle(50,40));
    tVector.FastPushBack(tmp);
    tmp = std::shared_ptr<Figure>(new Rectangle(30,40));
    tVector.FastPushBack(tmp);
    tmp = std::shared_ptr<Figure>(new Rectangle(20,40));
    tVector.FastPushBack(tmp);
    tmp = std::shared_ptr<Figure>(new Rectangle(10,40));
    tVector.FastPushBack(tmp);
    tmp = std::shared_ptr<Figure>(new Triangle(5,6,7));
    tVector.FastPushBack(tmp);
    tmp = std::shared_ptr<Figure>(new Triangle(3,4,5));
    tVector.FastPushBack(tmp);


    tVector.Sort(0,6);
    std::cout << std::endl;
    for (const auto &i: tVector) {
        i->Print();
    }

    /*
    int action = 0;
    TVector <TVectorItem <Figure>> tVector(10);
    Figure *ptr = nullptr;
    TVectorItem<Figure> *tr;
    do {
        Menu();
        std::cin >> action;
        switch (action) {
            case 1:
                delete ptr;
                delete tr;
                ptr = new Triangle(std::cin);
                tr = new TVectorItem <Figure>(ptr);
                tVector.FastPushBack(*tr);
                break;
            case 2:
                delete ptr;
                delete tr;
                ptr = new Rectangle(std::cin);
                tr = new TVectorItem <Figure>(ptr);
                tVector.FastPushBack(*tr);
                break;
            case 3:
                delete ptr;
                delete tr;
                ptr = new TSquare(std::cin);
                tr = new TVectorItem <Figure>(ptr);
                tVector.FastPushBack(*tr);
                break;
            case 4:
                std::cin >> action;
                if (action <= tVector.Capacity() - 1)
                    std::cout << tVector[action] << std::endl;
                else {
                    std::cout << "Index out of range";
                }
                break;
            case 5:
                for (auto i: tVector) {
                    std::cout << i;
                }
                break;
            case 6:
                tVector.Sort(0,tVector.Capacity());
                break;
            case 0:
                break;
            default:
                std::cout << "Incorrect command" << std::endl;;
                break;
        }
    } while (action);
    delete ptr;
    delete tr;*/
    return 0;
}
