#include "Tree.hpp"
#include <iostream>

int main()
{
    std::shared_ptr<Tree<Figure>> node(new Tree<Figure>());
    char choice;
    char path[100];

    std::cout << "Usage:\n"
              << "\t Add element:   \t + side_a side_b side_c\n"
              << "\t Delete element:\t - path \n"
              << "\t\t path={r,l}*\n"
              << "\t Get element:   \t g path\n"
              << "\t\t path={r,l}*\n\n";

    std::cout << "command>> ";
    while (std::cin.get(choice)) {
        switch (choice) {
        case '\n':
            continue;
        case '+': {
            std::cin >> choice;
            switch (choice) {
            case 't':
                node->add(new Triangle(std::cin));
                break;
            case 'r':
                node->add(new Rectangle(std::cin));
                break;
            case 's':
                node->add(new Sqr(std::cin));
                break;
            }
            break;
        }
        case '-': {
            std::cin >> path;
            node->Remove(path);
            break;
        }

        case 'g': {
            std::cin >> path;

            if (!node->empty()) {

                std::cout << "————————————————————————————————————————————" << std::endl;
                node->getItem(path)->Show(std::cout);
                std::cout << "\tSquare = " << node->getItem(path)->Square() << std::endl;
                goto end;
                // break;
            }
            // continue;
            goto end;
        }
        case 's':{
            for(auto i: *node)
            {
                std::cout << *i << '\n';
            }
        }
        }
        std::cout << "————————————————————————————————————————————" << std::endl;
        if (node && !node->empty())
            std::cout << *node;
        else
            std::cout << "empty!\n";
    end:
        std::cout << "command>> ";
    }

    return 0;
}
