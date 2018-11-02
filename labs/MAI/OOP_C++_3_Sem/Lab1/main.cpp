#include "triangle.h"
#include "square.h"
#include "rectangle.h"

int main(int argc, char **argv)
{
    //triangle
    std::cout << "Enter Triangle Sides: " << std::endl;
    Figure *ptr = new Triangle(std::cin);
    ptr->Print();
    std::cout << "Square = " << ptr->Square() << std::endl;
    delete ptr;

    //square
    std::cout << "Enter Square Sides: " << std::endl;
    Figure *psq = new TSquare(std::cin);
    psq->Print();
    std::cout << "Square = " << psq->Square() << std::endl;
    delete psq;

    //rectangle
    std::cout << "Enter Rectangle Sides: " << std::endl;
    Figure *prec = new Rectangle(std::cin);
    prec->Print();
    std::cout << "Square = " << prec->Square() << std::endl;
    delete prec;

#ifndef NDEBUG
    int deb;
    std::cin >> deb;
#endif // !DEBUG

    return 0;
}