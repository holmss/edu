#ifndef TTREE_H
#define TTREE_H

#include "Triangle.hpp"
#include <iostream>
#include <memory>

#define pTriangle std::shared_ptr<Triangle>
class TTree {
public:
    TTree();
    TTree(const TTree& orig);
    virtual ~TTree();

    pTriangle getItem();
    pTriangle getItem(char* path);

    void add(pTriangle triangle);
    void Remove(TTree* node);

    TTree* get(char* path);
    int height() const;
    bool empty();
    TTree& operator=(const TTree&);
    friend std::ostream& operator<<(std::ostream& os, const TTree& tree);

private:
    pTriangle value;
    TTree* left;
    TTree* right;
    TTree* prev;
};

#endif // TTREE_H
