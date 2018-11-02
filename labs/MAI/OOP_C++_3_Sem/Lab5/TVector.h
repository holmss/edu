//
// Created by Maxim Spiridonov on 29.09.17.
//

#ifndef TVECTOR_H
#define TVECTOR_H

#include "iostream"
#include <memory>

template <class T>
class Iter {
public:
    Iter (int n, T *arr) {
        _n = n;
        _arr = arr;
    }

    Iter (Iter *i) {
        this->_n = i->_n;
        this->_arr = i->_arr;
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
        Iter *tmp = new Iter(*this);
        ++(*this);
        return *tmp;
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
    T *privateArray;
    int privateArraySize;
    int privateArrayOccupiedSize;
    static int const SIZE_DIFFERENCE = 1;
    static int const DEFAULT_INT_VALUE = 0;
};

#include "TVector.hpp"

#endif //TVECTOR_H
