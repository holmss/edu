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

    std::ostream *Show(std::ostream &os) override;

    friend std::ostream& operator<<(std::ostream& os, const Hexagon& pent); 
    friend std::istream& operator>>(std::istream& is, Hexagon& pent);
    friend Hexagon operator+(const Hexagon& left, const Hexagon& right);

    Hexagon& operator=(const Hexagon& right);
    Hexagon& operator++();
    friend bool operator==(const Hexagon& left, const Hexagon& right);
    friend bool operator!=(const Hexagon& left, const Hexagon& right); 

    double Square() override;
    void   Print() override;

    virtual ~Hexagon();

    size_t side_a;
};

#endif 