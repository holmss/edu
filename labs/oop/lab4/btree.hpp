#ifndef TTREE_H
#define TTREE_H

#include "pentagon.hpp"
#include <iostream>
#include <memory>

template <class T>
class TTree
{
public:
  TTree();
  TTree(const TTree &orig);
  virtual ~TTree();

  std::shared_ptr<T> getItem();
  std::shared_ptr<T> getItem(char *path);


  void add(std::shared_ptr<T> pentagon);
  void Remove(std::shared_ptr<TTree<T>> *node);

  std::shared_ptr<TTree<T> > * get(char *path);
  int height() const;
  bool empty();

  template <class A> friend std::ostream &operator<<(std::ostream &os, const TTree<A> &tree);

  std::shared_ptr<T> value;
  std::shared_ptr<TTree <T> > *left;
  std::shared_ptr<TTree <T> > *right;
  std::shared_ptr<TTree <T> > *prev;
};

#endif // TTREE_H

#include "figure.hpp"
template class TTree<Figure>;
//template std::ostream &operator<<(std::ostream &os, const TTree<Figure> &tree);

