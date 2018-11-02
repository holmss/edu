#ifndef RECTANGLE_H
#define RECTANGLE_H
#include <iostream>
#include "figure.h"
class Rectangle : public Figure
{
public:
  Rectangle();
  Rectangle(std::istream &is);
  Rectangle(size_t sideA, size_t sideB);
  Rectangle(const Rectangle &orig);

  double Square() override;
  void Print() override;

  virtual ~Rectangle();

private:
  size_t _sideA;
  size_t _sideB;
};
#endif // !RECTANGLE_H