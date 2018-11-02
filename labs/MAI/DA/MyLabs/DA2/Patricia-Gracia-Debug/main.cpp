//
// Created by Maxim Spiridonov on 21.10.17.
//

#include <iostream>
#include <fstream>
#include "PatriciaTree.h"

int main () {
    TPatriciaTree *p = new TPatriciaTree();
    //char temp[size];
    TPair *tmp = new TPair();
    //unsigned long long data;
    char choice;
    //int len;

    if (!std::cin.get(choice)) {
        return 0;
    }

    std::cin.putback(choice);

    while (std::cin >> choice) {
        switch (choice) {
            case '+': {
                std::cin >> tmp->Key >> tmp->Value;
                //len = LengthString(temp);
                //ToLower(temp, tmp.Value.Length());
                tmp->Key.ToLower();

                if (p->Insert(*tmp)) {
                    std::cout << "OK\n";
                } else {
                    std::cout << "Exist\n";
                }
            }
                break;

            case '-': {
                std::cin >> tmp->Key;
                //len = LengthString(temp);
                //ToLower(temp, len);
                tmp->Key.ToLower();
                if (p->Remove(*tmp)) {
                    std::cout << "OK\n";
                } else {
                    std::cout << "NoSuchWord\n";
                }
            }
                break;
            case '!': {
                std::cin.get(choice);
                std::cin.get(choice);

                if (choice == 'S') {
                    std::cin >> tmp->Key >> tmp->Key;

                    p->Save(tmp->Key);
                } else {
                    std::cin >> tmp->Key >> tmp->Key;
                    delete p;

                    p = new TPatriciaTree();
                    p->Load(tmp->Key);
                }
                break;
            }

            default: {
                //int len;
                std::cin.putback(choice);
                std::cin >> tmp->Key;

                //len = LengthString(tmp.Key);

                //ToLower(temp, tmp.Key.Length());
                tmp->Key.ToLower();
                const unsigned long long *d = p->Search(*tmp);

                if (d == nullptr) {
                    std::cout << "NoSuchWord\n";
                } else {
                    std::cout << "OK: " << *d << '\n';
                }
            }
        }

    }
    delete p;

    return 0;
}



