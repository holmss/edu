#include <cstdlib>
#include <iostream>

// #include "Triangle.hpp"
#include "Tree.hpp"

int main()
{
    std::shared_ptr<Tree> node(new Tree());
    char inp;
    char path[100];

    std::cout << "Usage:\n"
              << "\t Add element:   \t figure_type path\n"
              << "\t Delete element:\t - path \n"
              << "\t\t path={r,l}*\n"
              << "\t Get element:   \t g path\n"
              << "\t\t path={r,l}*\n\n";

    std::cout << "command>> ";
    while (std::cin.get(inp))
    {

        if (inp == '\n')
            continue;
        if (inp == 'p')
        {
            node->add(new Pentagon(std::cin));
        }
        if (inp == 'o')
        {
            node->add(new Octagon(std::cin));
        }
        if (inp == 'h')
        {
            node->add(new Hexagon(std::cin));
        }
        else if (inp == '-')
        {
            std::cin >> path;
            node->Remove(path);
        }
        else if (inp == 'g')
        {
            std::cin >> path;
            std::cout << "————————————————————————————————————————————" << std::endl;
            std::cout << node->getItem(path)->Show(std::cout) << "\tSquare = " << node->getItem(path)->Square() << std::endl;
            std::cout << "————————————————————————————————————————————" << std::endl;

            continue;
        }
        std::cout << "————————————————————————————————————————————" << std::endl;
        if (node && !node->empty())
            std::cout << *node;
        else
            std::cout << "empty!\n";
        std::cout << "command>> ";
    }

    return 0;
}
