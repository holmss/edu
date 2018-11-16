#ifndef TTREE_H
#define TTREE_H

#include "Rectangle.hpp"
#include "Sqr.hpp"
#include "Triangle.hpp"
#include "TIterator.hpp"

#define tp template <class T>
#define pTree std::shared_ptr<TTree<T>>
#define pFigure std::shared_ptr<Figure>

tp class TTree {
public:
    TTree();
    virtual ~TTree();

    std::shared_ptr<T> getValue(char* path, pTree curr);

    void add(Figure* triangle);
    void Remove(std::shared_ptr<TTree<T>> node, std::shared_ptr<TTree<T>> prev);

    pTree getItem(char* path, pTree curr);
    bool empty();
    std::ostream* stream(std::ostream& os, const TTree<T>& node, int height) const;
    template <class B>
    friend std::ostream& operator<<(std::ostream& os, const TTree<B>& tree);
// private:
int count();
    std::shared_ptr<T> value;
    pTree left;
    pTree right;
};

#endif // TTREE_H
