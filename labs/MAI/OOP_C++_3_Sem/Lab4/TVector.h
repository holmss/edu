//
// Created by Maxim Spiridonov on 29.09.17.
//

#ifndef TVECTOR_H
#define TVECTOR_H

#include "iostream"
#include <memory>

template <class T>
class TVector {
public:

    void FastPushBack (T &data);

    void Clear ();

    T &operator [] (int index);

    int Size () const;

    int Capacity () const;

    TVector &operator = (const TVector <T> &inp);

    TVector ();

    TVector (const TVector <T> &inp);

    friend std::ostream &operator << (std::ostream &os, const TVector <T> &tVector);

    explicit TVector (int n);

    ~TVector ();

private:
    T *privateArray;
    int privateArraySize;
    int privateArrayOccupiedSize;
    static int const SIZE_DIFFERENCE = 1;
    static int const DEFAULT_INT_VALUE = 0;
};

#include "TVector.hpp"

#endif //TVECTOR_H
