#ifndef PATRICIATREEITEM_H
#define PATRICIATREEITEM_H

class TPatriciaTreeNode {
public:
    TPatriciaTreeNode();
    TPatriciaTreeNode(char* key, unsigned long long data, int bitIndex, TPatriciaTreeNode* left, TPatriciaTreeNode* right);

    void Initialize(char* key, unsigned long long data, int bitIndex, TPatriciaTreeNode* left, TPatriciaTreeNode* right);
    unsigned long long GetData();
    bool SetData(unsigned long long data);
    char* GetKey();
    TPatriciaTreeNode* GetLeft();
    TPatriciaTreeNode* GetRight();

    virtual ~TPatriciaTreeNode();
private:
    friend class TPatriciaTree; //DO I NEED IT?

    int bitIndex;
    char* key;
    unsigned long long data;
    TPatriciaTreeNode* left;
    TPatriciaTreeNode* right;
};

#endif //PATRICIATREEITEM_H