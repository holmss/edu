#include <iostream>
#include "TVector.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Square.h"
#include <chrono>

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

    TVector<int> intV;
    clock_t start = clock();
    int *j = nullptr;
    for (int i = 0; i < 100000; ++i) {
        j=new int(10);
        intV.FastPushBack(*j);
    }
    clock_t end = clock();
    double time = (double)(end-start);
    time/=CLOCKS_PER_SEC;

    std::cout << time;
    start = clock();
    TVector<TVectorItem<int>> *intB = new TVector<TVectorItem<int>>();
    for (int i = 0; i < 100000; ++i) {
        TVectorItem<int> *b = new TVectorItem<int>(*j);
        intB->FastPushBack(*b);
    }
    end = clock();
    time = (double)(end-start)/CLOCKS_PER_SEC;
    std::cout << time;
    //delete intV;
    /*
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
