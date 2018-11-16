#include <cstdlib>
#include <iostream>
#include <memory>

#include "TStack.h"
#include "TStackItem.h"
#include "Triangle.h"

int main(int argc, char** argv)
{
    TStack<Triangle> stack;

    stack.push(std::shared_ptr<Triangle>(new Triangle(1, 1, 1)));
    stack.push(std::shared_ptr<Triangle>(new Triangle(2, 2, 2)));
    stack.push(std::shared_ptr<Triangle>(new Triangle(3, 3, 3)));

    for (auto i : stack)
        std::cout << *i << std::endl;

    return 0;
}
