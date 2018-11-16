#ifndef TTREE_H
#define TTREE_H

#include "pentagon.hpp"
#include "octagon.hpp"
#include "hexagon.hpp"

#define pTree std::shared_ptr<TTree<T>>
#define wTree std::weak_ptr<TTree<T>>


template <class T>
class TTree {
public:
    TTree();
    virtual ~TTree();

    std::shared_ptr<T> getValue(char*, pTree);

    void add(T*, pTree);
    void Remove(pTree);

    pTree getItem(char*, pTree);
    bool empty();
    void stream(std::ostream& os, const TTree& node, int height) const;
    pTree GetNext();

    template <class B>
    friend std::ostream& operator<<(std::ostream& os, const TTree<B>& tree);

    std::shared_ptr<T> value;
    pTree left;
    pTree right;
    wTree prev;
};

#include "TTree.h"

#endif // TTREE_H
