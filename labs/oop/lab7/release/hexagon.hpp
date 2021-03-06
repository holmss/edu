#ifndef HEXAGON_H
#define	HEXAGON_H
#include <cstdlib>
#include <iostream>
#include "Figure.hpp"

class Hexagon : public Figure{
public:
    Hexagon();
    Hexagon(std::istream &is);
    Hexagon(size_t i);
    Hexagon(const Hexagon& orig);

    double Square() override;
    void   Print() override;

    virtual ~Hexagon();
private:
    size_t side_a;
};

#endif