#ifndef RBT_H
#define RBT_H

#include <cstring>
#include <iostream>
#include <fstream>

using ull = unsigned long long;

const short LEAF = -1;

enum color {BLACK, RED};

class Trbt {
public:
    class TNode {
    public:
        TNode() {};
        TNode(color, ull, char*);
        ~TNode();

        TNode* prev;
        TNode* left;
        TNode* right;
        char* word;
        ull key;
        color clr;
    };

    Trbt();
    ~Trbt();
    void Reborn();
    TNode* Search(const char*);

    void Insert(TNode&);
    void Fix(TNode*);

    void LeftRotate(TNode&);
    void RightRotate(TNode&);

    void Exchange(TNode*, TNode*);
    TNode* FindMin(TNode*);

    void RBDelete(TNode*);
    void FixD(TNode*);

    void Save(const char*);
    void Save(std::ofstream&, TNode*);
    void Load(const char*);
    void Load(std::ifstream&, TNode*&);

    friend std::istream& operator>>(std::istream& is, color& clr);

private:
    TNode* root;
    TNode* leaf;
};

#endif