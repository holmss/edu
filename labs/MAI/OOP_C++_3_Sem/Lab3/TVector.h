#ifndef TVECTOR_H
#define TVECTOR_H

#include <memory>
#include "Figure.h"
#include <ctime>
#include <iostream>
#include <cstdio>

class TVector {
public:

    void FastPushBack (std::shared_ptr<Figure> &data);

    void Remove(int index);

    void Clear ();

    std::shared_ptr<Figure>& operator [] (int index);

    std::shared_ptr<Figure>& operator [] (int index) const;

    int Size () const;

    int Capacity () const;

    TVector &operator = (const TVector &inp);

    TVector ();

    TVector (const TVector &inp);

    TVector (const int n);

    friend std::ostream &operator << (std::ostream &os, const TVector &obj);

    ~TVector ();

private:
    std::shared_ptr<Figure> *privateArray;
    int privateArraySize;
    int privateArrayOccupiedSize;
    static int const SIZE_DIFFERENCE = 1;
    static int const DEFAULT_INT_VALUE = 0;
};

#endif //TVECTOR_H
