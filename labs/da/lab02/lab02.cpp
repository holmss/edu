//#include <cctype>
#include <stdio.h>
#include "rbt.hpp"

int main()
{
    std::cin.tie(0);
    std::ios::sync_with_stdio(false);
    Trbt tree;
    // return 0;
    const int size = 257;
    char buffer[size];
    char rdn;
    ull key;

    while (std::cin >> rdn) { //stdinp std::cin >> rdn;
        TNode* temp = new TNode;
        switch (rdn) {
        case '+':
	    scanf("%s%llu", buffer, &key); //stdinp
            //std::cin >> buffer >> key;

            for (int i = 0; i < strlen(buffer); i++) {
                buffer[i] = tolower(buffer[i]);
            }
            temp->word = new char[strlen(buffer) + 1];
            strcpy(temp->word, buffer);
            temp->key = key;
            temp->clr = RED;

            if (!tree.Search(buffer)) {
                tree.Insert(*temp);
                printf("OK\n"); //stdin
	       	//std::cout << "OK\n";
            } else {
                delete temp;
		printf("Exist\n"); //stdin
                //std::cout << "Exist\n";
            }

            break;

        case '-':
	    scanf("%s", buffer); //stdin
            //std::cin >> buffer;

            for (int i = 0; i < strlen(buffer); i++) {
                buffer[i] = tolower(buffer[i]);
            }

            if (tree.Search(buffer)) {
                tree.RBDelete(tree.Search(buffer));
                printf("OK\n"); //stdin
		//std::cout << "OK\n";
            } else {
                printf("NoSuchWord\n"); //stdin
		//std::cout << "NoSuchWord\n";
            }

            break;

        case '!':

            scanf("%s", buffer); //stdin
	    //std::cin >> buffer;

            if (*buffer == 'S') {
                scanf("%s", buffer); //stdin
		//std::cin >> buffer;
                tree.Save(buffer);
            } else if (*buffer == 'L') {
                scanf("%s", buffer); //stdin
		//std::cin >> buffer;
                tree.Load(buffer);
            }

            break;

        default:
            std::cin.putback(rdn);
            scanf("%s", buffer); //stdin
	    //std::cin >> buffer;

            for (int i = 0; i < strlen(buffer); i++) {
                buffer[i] = tolower(buffer[i]);
            }

            TNode* tmp = tree.Search(buffer);
            if (tmp) {
                printf("OK: %lld\n", tmp->key); //stdin
		//std::cout << "OK: " << tmp->key << '\n';
            } else
                printf("NoSuchWord\n"); //stdin
		//std::cout << "NoSuchWord\n";

            break;
        }
    }
    // delete[] buffer;
    // delete tree;
    return 0;
}
