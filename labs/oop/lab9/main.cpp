#include "Tree.hpp"
#include <functional>
#include <iostream>
#include <mutex>
#include <random>

#define line std::cout << "____________________________________________" << std::endl

int main()
{
    typedef std::function<void(int)> Command;
    Tree<Figure> node;
    Tree<Command> cmd;
    char choice;
    char path[200];
    int num = 200;
    Command cmdRnd = [&](int num) {
        for (int i = 0; i < num; ++i) {
            switch (rand() % 3) {
            case 0:
                node.add(new Pentagon(unsigned(rand())));
                break;
            case 1:
                node.add(new Octagon(unsigned(rand())));
                break;
            case 2:
                node.add(new Hexagon(unsigned(rand())));
                break;
            }
        }
    };

    Command cmdDel = [&](int num) {
    del:
        for (auto i = node.begin(); i != node.end(); ++i) {
            if (i->Square() < num) {
                node.Remove(i.get());
                goto del;
            }
        }
    };

    Command cmdPrnt = [&](int) {
        std::cout << "Show:" << '\n';
        for (auto i : node) {
            i->Print();
            std::cout << "->";
        }
        std::cout << "nullptr\n";
    };

    std::cout << "Usage:\n"
              << "\t Add element:   \t + {elem_type} {sides}\n"
              << "\t Delete element:\t - path \n"
              << "\t\t path={r,l}*\n"
              << "\t Get element:   \t g path\n"
              << "\t\t path={r,l}*\n"
              << "\t Show container:\t s\n"
              << "\t Command: c\n\n";

    std::cout << "command>> ";
    while (std::cin.get(choice)) {
        switch (choice) {
        case 'c': {
            std::cout << "Choose command: \n\t [R]andom generator\n\t [D]elete by value\n\t [P]rint container\nYour choice: ";
        input:
            std::cin >> choice;
            switch (choice) {
            case 'R':
                std::cout << "Enter number of elements: ";
                std::cin >> num;
                cmdRnd(num);
                break;
            case 'D':
                std::cout << "Enter deleting value: ";
                std::cin >> num;
                cmdDel(num);
                break;
            case 'P':
                cmdPrnt(num);
                break;
            default:
                std::cout << "Enter right command: ";
                goto input;
            }

            break;
        }
        case '+': {
            std::cin >> choice;
            switch (choice) {
            case 'p':
                node.add(new Pentagon(std::cin));
                break;
            case 'o':
                node.add(new Octagon(std::cin));
                break;
            case 'h':
                node.add(new Hexagon(std::cin));
                break;
            }
            break;
        }
        case '-': {
            std::cin.getline(path, 200);
            node.Remove(path);
            break;
        }

        case 'g': {
            std::cin.getline(path, 200);
            if (!node.empty()) {

                line;
                std::weak_ptr<Figure> temp = node.getItem(path);
                temp.lock()->Print();
                std::cout << "\tSquare = " << temp.lock()->Square() << std::endl;
                goto end;
            }
            goto end;
        }
        case 's': {
            std::cout << "Show:" << '\n';
            for (auto i : node) {
                i->Print();
                std::cout << "->";
            }
            std::cout << "nullptr\n";
            goto end;
        }
        default:
            continue;
        }
        line;
        if (!node.empty())
            std::cout << node;
        else
            std::cout << "empty!\n";
    end:
        std::cout << "command>> ";
    }

    cmd.add(std::shared_ptr<Command>(&cmdRnd, [](Command*) {}));
    cmd.add(std::shared_ptr<Command>(&cmdPrnt, [](Command*) {}));
    cmd.add(std::shared_ptr<Command>(&cmdDel, [](Command*) {}));
    cmd.add(std::shared_ptr<Command>(&cmdPrnt, [](Command*) {}));

    for (auto i: cmd)
        (*i)(num);

    return 0;
}