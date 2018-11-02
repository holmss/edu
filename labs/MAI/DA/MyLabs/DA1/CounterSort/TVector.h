//
// Created by Maxim Spiridonov on 29.09.17.
//

#ifndef TVECTOR_H
#define TVECTOR_H

#include "Model.h"
#include <ctime>
#include <cstdio>

class TVector {
public:

    void FastPushBack (TPair &data);

    void Clear ();

    TPair& operator [] (int index);

    int Size () const;

    int Capacity () const;

    TVector &operator = (const TVector &inp);

    TVector ();

    TVector (const TVector &inp);

    TVector (const int n);

    void CountingSort();

    ~TVector ();

private:
    TPair *privateArray;
    int privateArraySize;
    int privateArrayOccupiedSize;
    static int const SIZE_DIFFERENCE = 1;
    static int const DEFAULT_INT_VALUE = 0;
};

#endif //TVECTOR_H
