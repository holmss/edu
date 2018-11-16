// #include <cctype>

#include "rbt.hpp"

int main()
{
    Trbt tree;
    // return 0;
    const int size = 257;
    char buffer[size];
    char rdn;
    ull key;

    while (std::cin >> rdn) {
        TNode* temp = new TNode;
        switch (rdn) {
        case '+':
            std::cin >> buffer >> key;

            for (int i = 0; i < strlen(buffer); i++) {
                buffer[i] = tolower(buffer[i]);
            }
            temp->word = new char[strlen(buffer) + 1];
            strcpy(temp->word, buffer);
            temp->key = key;
            temp->clr = RED;

            if (!tree.Search(buffer)) {
                tree.Insert(*temp);
                std::cout << "OK\n";
            } else {
                delete temp;
                std::cout << "Exist\n";
            }

            break;

        case '-':
            std::cin >> buffer;

            for (int i = 0; i < strlen(buffer); i++) {
                buffer[i] = tolower(buffer[i]);
            }

            if (tree.Search(buffer)) {
                tree.RBDelete(tree.Search(buffer));
                std::cout << "OK\n";
            } else {
                std::cout << "NoSuchWord\n";
            }

            break;

        case '!':

            std::cin >> buffer;

            if (*buffer == 'S') {
                std::cin >> buffer;
                tree.Save(buffer);
            } else if (*buffer == 'L') {
                std::cin >> buffer;
                tree.Load(buffer);
            }

            break;

        default:
            std::cin.putback(rdn);
            std::cin >> buffer;

            for (int i = 0; i < strlen(buffer); i++) {
                buffer[i] = tolower(buffer[i]);
            }

            TNode* tmp = tree.Search(buffer);
            if (tmp) {
                std::cout << "OK: " << tmp->key << '\n';
            } else
                std::cout << "NoSuchWord\n";

            break;
        }
    }
    // delete[] buffer;
    // delete tree;
    return 0;
}
