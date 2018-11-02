#include <iostream>
#include <fstream>
#include "PatriciaTree.h"

void ToLower (char *t, int len) {
    for (int i = 0; i < len; ++i) {
        if (t[i] >= 'A' && t[i] <= 'Z') {
            t[i] = 'a' + t[i] - 'A';
        }
    }
}

unsigned int LengthString (const char *string) {
    unsigned int length = 0;

    while ((string + length != nullptr) && string[length] != '\0') {
        ++length;
    }

    return length;
}

int main () {
   // std::ios::sync_with_stdio(false); //make_faster
    char choice;
    if (!std::cin.get(choice)) {
        return 0;
    }
    TPatriciaTree *p = new TPatriciaTree;
    const int size = 1025; //1024+1
    char temp[size];
    unsigned long long data;

    int len;



    std::cin.putback(choice);

    while (std::cin >> choice) {
        switch (choice) {
            case '+': {
                std::cin >> temp >> data;
                len = LengthString(temp);
                ToLower(temp, len);

                if (p->Insert(temp, len, data)) {
                    std::cout << "OK\n";
                } else {
                    std::cout << "Exist\n";
                }
            }
                break;
            case '-': {
                std::cin >> temp;
                len = LengthString(temp);
                ToLower(temp, len);

                if (p->Remove(temp, len)) {
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
                    std::cin >> temp >> temp;

                    p->Save(temp);
                } else {
                    std::cin >> temp >> temp;
                    delete p;

                    p = new TPatriciaTree;
                    p->Load(temp);
                }

            }
                break;
            default: {
                int len;
                std::cin.putback(choice);
                std::cin >> temp;

                len = LengthString(temp);
                ToLower(temp, len);
                const unsigned long long *d = p->Search(temp, len);

                if (d == nullptr) {
                    std::cout << "NoSuchWord\n";
                } else {
                    std::cout << "OK: " << *d << '\n';
                    d= nullptr;
                }
            }
        }

    }

    delete p;

    return 0;
}



