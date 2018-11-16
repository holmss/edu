#ifndef TTREE_H
#define TTREE_H

#include "Triangle.hpp"
#include <iostream>
class TTree {
public:
    TTree();
    TTree(const TTree& orig);
    virtual ~TTree();

    Triangle getItem();
    Triangle getItem(char* path);

    void add(Triangle triangle);
    void Remove(TTree* node);

    TTree* get(char* path);
    int height() const;
    bool empty();

    friend std::ostream& operator<<(std::ostream& os, const TTree& tree);

private:
    Triangle value;
    TTree* left;
    TTree* right;
    TTree* prev;
};

#endif // TTREE_H
