#ifndef PATRICIATREE_H
#define PATRICIATREE_H

#include <cstring> //DO I NEED IT?
#include "PatriciaTreeNode.h"

class TPatriciaTree {
public:
    TPatriciaTree();

    TPatriciaTreeNode* Insert(char* key, unsigned long long data);
    unsigned long long LookUp(char* key);
    TPatriciaTreeNode* LookUpNode(char* key);
    bool Delete(char* key);

    virtual ~TPatriciaTree();
private:
    void RecursiveRemove(TPatriciaTreeNode* node);
    int GetBit(char* key, int bitIndex);
    int FirstDiffBit(char* key1, char* key2);
    bool KeysCompare(char* key1, char* key2);
    void KeyCopy(TPatriciaTreeNode* node1, TPatriciaTreeNode* node2);

    TPatriciaTreeNode* head;
};

#endif //PATRICIATREE_H