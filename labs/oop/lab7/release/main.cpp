#include "Tree.hpp"
#include <iostream>

#define line std::cout << "————————————————————————————————————————————" << std::endl

int main()
{
    //std::shared_ptr<Tree<Figure>> node(new Tree<Figure>());
    TList<TTree<Figure>,Figure> list;
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
        case '+': {
            std::cin >> choice;
            switch (choice) {
            case 'p':
                //node->add(new Pentagon(std::cin));
                
                break;
            case 'o':
                node->add(new Octagon(std::cin));
                break;
            case 'h':
                node->add(new Hexagon(std::cin));
                break;
            }
            break;
        }
        case '-': {
            std::cin.getline(path, 100);
            node->Remove(path);
            break;
        }

        case 'g': {
            std::cin.getline(path, 100);
            if (!node->empty()) {

                std::cout << "————————————————————————————————————————————" << std::endl;
                std::weak_ptr<Figure> temp = node->getItem(path);
                temp.lock()->Print();
                std::cout << "\tSquare = " << temp.lock()->Square() << std::endl;
                goto end;
            }
            goto end;
        }
        case 's': {
            std::cout << "Show:" << '\n';
            for (auto i : *node) {
                i.get()->Print();
                std::cout << "->";
            }
            std::cout << "nullptr\n";
            goto end;
        }
        default:
            continue;
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
