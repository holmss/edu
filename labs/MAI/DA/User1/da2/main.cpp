#include <stdlib.h> //DO I NEED IT?
#include <iostream>
#include <fstream>
#include "PatriciaTree.h"
#include "PatriciaTreeNode.h"

int main() {
    TPatriciaTree* tree = new TPatriciaTree();

    unsigned long long data = 0;
    char* key = new char[257];
    //char option; //SIGN FOR ACTION

    std::cin >> key;
    std::cin >> data;

    tree->Insert(key, data);

    return 0;
}