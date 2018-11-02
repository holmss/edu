#ifndef TVECTOR_H
#define TVECTOR_H

#include "iostream"
#include "TAllocationBlock.h"
#include "TVectorItem.h"
//#include <memory>

template <class T>
class Iter {
public:
    Iter (int n, T *arr) {
        _n = n;
        _arr = arr;
    }

    T &operator * () {
        return _arr[_n];
    }

    T &operator -> () {
        return _arr[_n];
    }

    void operator ++ () {
        _n++;
    }

    Iter operator ++ (int) {
        ++(*this);
        return &this;
    }

    bool operator == (Iter const &i) {
        return _n == i._n &&
               _arr == i._arr;
    }

    bool operator != (Iter const &i) {
        return !(*this == i);
    }

private:
    int _n;
    T *_arr;
};

template <class T>
class TVector {
public:

    void FastPushBack (T &data);

    void Clear ();

    T &operator [] (int index);

    int Size () const;

    int Capacity () const;

    Iter <T> begin ();

    Iter <T> end ();

    TVector &operator = (const TVector <T> &inp);

    TVector ();

    TVector (const TVector <T> &inp);

    friend std::ostream &operator << (std::ostream &os, const TVector <T> &tVector);

    explicit TVector (int n);

    ~TVector ();

private:
    //static TAllocationBlock vector_allocator;
    T *privateArray;
    int privateArraySize;
    int privateArrayOccupiedSize;
    static int const SIZE_DIFFERENCE = 1;
    static int const DEFAULT_INT_VALUE = 0;
};

#include "TVector.hpp"

#endif //TVECTOR_H
