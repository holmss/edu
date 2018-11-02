#ifndef PENTAGON_H
#define	PENTAGON_H
#include <cstdlib>
#include <iostream>

class Pentagon {
public:
    Pentagon();
    Pentagon(std::istream &is);
    Pentagon(size_t i);
    Pentagon(const Pentagon& orig);
     
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

