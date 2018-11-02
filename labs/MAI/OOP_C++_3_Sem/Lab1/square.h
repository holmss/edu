#ifndef SQUARE_H
#define SQUARE_H
#include <iostream>
#include "figure.h"
class TSquare : public Figure
{
public:
  TSquare();
  TSquare(std::istream &is);
  TSquare(size_t side);
  TSquare(const TSquare &orig);

  double Square() override;
  void Print() override;

  virtual ~TSquare();

private:
  size_t _side;
};
#endif // !SQUARE_H