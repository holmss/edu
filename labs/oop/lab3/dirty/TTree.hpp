#ifndef TTREE_H
#define TTREE_H

#include "pentagon.hpp"
#include "octagon.hpp"
#include "hexagon.hpp"
#include <iostream>

#define pFigure std::shared_ptr<Figure>
#define pTree std::shared_ptr<TTree>
#define wTree std::weak_ptr<TTree>

class TTree
{
public:
  TTree();
  virtual ~TTree();

  pFigure getValue(char *path, pTree curr);

  void add(Figure *triangle);
  void Remove(pTree node, pTree prev);

  pTree getItem(char *path, pTree curr);
  bool empty();
  std::ostream *stream(std::ostream &os, const TTree &node, int height) const;
  friend std::ostream &operator<<(std::ostream &os, const TTree &tree);

// private:
  pFigure value;
  pTree left;
  pTree right;
};

#endif // TTREE_H
