#ifndef TTREE_H
#define TTREE_H

#include "pentagon.hpp"
#include <iostream>
class TTree
{
public:
  TTree();
  TTree(const TTree &orig);
  virtual ~TTree();

  Pentagon getItem();
  Pentagon getItem(char *path);

  void add(Pentagon pentagon);
  void Remove(TTree *node);

  TTree* get(char *path);
  int height() const;
  bool empty();

  friend std::ostream &operator<<(std::ostream &os, const TTree &tree);

  Pentagon value;
  TTree *left;
  TTree *right;
  TTree *prev;
};

#endif // TTREE_H
