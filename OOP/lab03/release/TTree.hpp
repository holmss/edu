#ifndef TTREE_H
#define TTREE_H

#include "Rectangle.hpp"
#include "Sqr.hpp"
#include "Triangle.hpp"

// #define pFigure std::shared_ptr<Figure>
#define pTree std::shared_ptr<TTree<T>>
#define wTree std::weak_ptr<TTree<T>>


template <class T>
class TTree {
public:
    TTree();
    virtual ~TTree();

    std::shared_ptr<T> getValue(char* path, pTree curr);

    void add(T* triangle, pTree node);
    void Remove(pTree node);

    pTree getItem(char* path, pTree curr);
    bool empty();
    void stream(std::ostream& os, const TTree& node, int height) const;
    template <class B>
    friend std::ostream& operator<<(std::ostream& os, const TTree<B>& tree);

    std::shared_ptr<T> value;
    pTree left;
    pTree right;
    wTree prev;
};

#include "TTree.h"

#endif // TTREE_H
