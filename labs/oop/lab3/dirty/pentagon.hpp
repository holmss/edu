#ifndef PENTAGON_H
#define	PENTAGON_H
#include <cstdlib>
#include <iostream>
#include "Figure.hpp"

class Pentagon : public Figure {
public:
    Pentagon();
    Pentagon(std::istream &is);
    Pentagon(size_t i);
    Pentagon(const Pentagon& orig);

    std::ostream *Show(std::ostream &os) override;
     
    friend std::ostream& operator<<(std::ostream& os, const Pentagon& pent); 
    friend std::istream& operator>>(std::istream& is, Pentagon& pent);
    friend Pentagon operator+(const Pentagon& left, const Pentagon& right);

    Pentagon& operator=(const Pentagon& right);
    Pentagon& operator++();
    friend bool operator==(const Pentagon& left, const Pentagon& right);
    friend bool operator!=(const Pentagon& left, const Pentagon& right); 


    double Square();
    void   Print();

    virtual ~Pentagon();

    size_t side_a;
};

#endif                    