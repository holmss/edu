#ifndef TTREE_H
#define TTREE_H

#include "pentagon.hpp"
#include "octagon.hpp"
#include "hexagon.hpp"
#include "tallocationblock.hpp"

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
    pTree GetNext();

    template <class B>
    friend std::ostream& operator<<(std::ostream& os, const TTree<B>& tree);

    void* operator new(size_t size);
    void operator delete(void* p);

    std::shared_ptr<T> value;
    pTree left;
    pTree right;
    wTree prev;

    static TAllocationBlock stackitem_allocator;
};

#include "TTree.h"

#endif // TTREE_H
