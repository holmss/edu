#ifndef TTREE_H
#define TTREE_H

#include "pentagon.hpp"
#include <iostream>
#include <memory>

class TTree
{
public:
  TTree();
  TTree(const TTree &orig);
  virtual ~TTree();

  Pentagon getItem();
  Pentagon getItem(char *path);

  void add(std::shared_ptr<Pentagon> pentagon);
  void Remove(std::shared_ptr<TTree> *node);

  std::shared_ptr<TTree> * get(char *path);
  int height() const;
  bool empty();

  friend std::ostream &operator<<(std::ostream &os, const TTree &tree);

  std::shared_ptr<Pentagon> value;
  std::shared_ptr<TTree> *left;
  std::shared_ptr<TTree> *right;
  std::shared_ptr<TTree> *prev;
};

#endif // TTREE_H
