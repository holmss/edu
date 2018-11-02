#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <iostream>
#include "figure.h"
class Triangle : public Figure {
 public:
  Triangle();
  Triangle(std::istream& is);
  Triangle(size_t i, size_t j, size_t k);
  Triangle(const Triangle& orig);

  double Square() override;
  void Print() override;

  virtual ~Triangle();

 private:
  size_t _sideA;
  size_t _sideB;
  size_t _sideC;
};
#endif  // !TRIANGLE_H