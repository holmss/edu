#ifndef OCTAGON_H
#define	OCTAGON_H
#include <cstdlib>
#include <iostream>
#include "Figure.hpp"

class Octagon : public Figure{
public:
    Octagon();
    Octagon(std::istream &is);
    Octagon(size_t i);
    Octagon(const Octagon& orig);

    std::ostream *Show(std::ostream &os) override;

    friend std::ostream& operator<<(std::ostream& os, const Octagon& pent); 
    friend std::istream& operator>>(std::istream& is, Octagon& pent);
    friend Octagon operator+(const Octagon& left, const Octagon& right);

    Octagon& operator=(const Octagon& right);
    Octagon& operator++();
    friend bool operator==(const Octagon& left, const Octagon& right);
    friend bool operator!=(const Octagon& left, const Octagon& right); 

    double Square() override;
    void   Print() override;

    virtual ~Octagon();

    size_t side_a;
};

#endif
