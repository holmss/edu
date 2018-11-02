#include <cstring>
#include "BRTree.h"
#include <iostream>

void ToLower (char *t) {
    int len = strlen(t);
    for (int i = 0; i < len; ++i) {
        if (t[i] >= 'A' && t[i] <= 'Z') {
            t[i] = 'a' + t[i] - 'A';
        }
    }
}

int main () {
    clock_t start = clock();
    //std::ios::sync_with_stdio(false);
    //std::cin.tie(NULL);
    TRBTree *tree = new TRBTree();
    const int size = 257;
    char *temp = new char[size];
    unsigned long long data = 0;
    char choice;

    if (!std::cin.get(choice)) {
        return 0;
    }

    std::cin.putback(choice);

    while (std::cin >> choice) {
        switch (choice) {
            case '+': {
                std::cin >> temp >> data;
                ToLower(temp);

                if (tree->RBInsert(temp, data)) {
                    std::cout << "OK\n";
                } else {    
                    std::cout << "Exist\n";
                }
                //delete newNode;
            }
                break;
            case '-': {
                std::cin >> temp;
                ToLower(temp);

                TRBNode *tempNode = tree->Search(temp);
                if (tempNode != (tree->nil)) {
                    tree->RBDelete(tempNode);
                    std::cout << "OK\n";
                } else {
                    std::cout << "NoSuchWord\n";
                }
                //tempNode= nullptr;
            }
                break;
            case '!': {
                std::cin.get(choice);
                std::cin.get(choice);

                if (choice == 'S') {
                    std::cin >> temp >> temp;

                    std::ofstream file(temp, std::ofstream::binary);

                    if (!file) {
                        std::cout << "ERROR: couldn't create file!\n";
                    }
                    else{
                        tree->Serialize(tree->root,file);
                        std::cout << "OK\n";
                    }
                    file.close();
                    //tree->Serialize(tree->root, fIn);
                } else {
                    std::cin >> temp >> temp;
                    delete tree;
                    tree = new TRBTree();
                    std::ifstream file(temp,std::ifstream::binary);
                    if (!file) {
                        std::cout << "ERROR: couldn't open file!\n";
                    }
                    else{
                        tree->DeSerialize(file);
                        file.close();
                    }
                }
            }
                break;
            default: {
                std::cin.putback(choice);
                std::cin >> temp;

                ToLower(temp);

                TRBNode *answer = tree->Search(temp);

                if (answer == (tree->nil)) {
                    std::cout << "NoSuchWord\n";
                } else {
                    std::cout << "OK: " << answer->value << '\n';
                }
                //delete answer;
            }
        }
    }
    delete tree;
    delete [] temp;
    clock_t end = clock();
    double time = (double)(end-start)/CLOCKS_PER_SEC;

    std::ofstream file("time");
    file << "Time : " << time << std::endl;
    file.close();
    
    return 0;
}
