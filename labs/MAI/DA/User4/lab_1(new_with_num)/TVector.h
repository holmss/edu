#ifndef TVECTOR_H
#define TVECTOR_H

#include "TData.h"
#include "cstring"
#include <cmath>

const int NUMBERS = 10;
const int NUMBERS_KEY = 3;

class TVector {
private:
    int size;
    int capacity;
    TData *array;
public:
    TVector();

    TVector(const int &);

    TData &operator[](const int &);

    int Size() const;

    int Capacity() const;

    void Push_back(const TData &);

    void CountingSort(const int &, const int &, const int &, int*);

    void RadixSort(/*TVector&*/);

    ~TVector();
};


#endif //LAB1_TVECTOR_H
