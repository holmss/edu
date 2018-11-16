#ifndef TREE_H
#define TREE_H

#include "TIterator.hpp"
#include "TTree.hpp"

tp class Tree {

private:
    pTree root;

public:
    // friend class TTree<T>;

    Tree();
    ~Tree();

    TIterator<TTree<T>, T> begin();
    TIterator<TTree<T>, T> end();

    void add(T*);
    void Remove(char* path);

    TTree<T> get(char* path);
    std::shared_ptr<T> getItem(char* path);

    bool empty();
    // int count(pTree node);

    template <class A>
    friend std::ostream& operator<<(std::ostream& os, const Tree<A>& node);
};

#endif // !TREE_H