#ifndef TVECTOR_HPP
#define TVECTOR_HPP

#include "TVector.h"

template <class T>
std::ostream &operator << (std::ostream &os, const TVector <T> &tVector) {
    for (int i = 0; i < tVector.Capacity(); ++i) {
        os << tVector[i] << std::endl;
    }
    return os;
}

template <class T>
void TVector <T>::FastPushBack (T &data) {
    if (privateArraySize == privateArrayOccupiedSize) {
        privateArraySize *= 2;
        T *result = new T[privateArraySize];

        for (int index = DEFAULT_INT_VALUE; index <= privateArrayOccupiedSize; index++) {
            if (index != privateArrayOccupiedSize) {
                result[index] = privateArray[index];
            } else {
                result[index] = data;
                break;
            }
        }
        delete[] privateArray;
        privateArray = result;
        privateArrayOccupiedSize++;
    } else {
        privateArray[privateArrayOccupiedSize] = data;
        privateArrayOccupiedSize++;
    }
}

template <class T>
void TVector <T>::Clear () {
    delete[] privateArray;
    privateArraySize = DEFAULT_INT_VALUE;
    privateArrayOccupiedSize = DEFAULT_INT_VALUE;
    privateArray = new T[privateArraySize];
}

template <class T>
T &TVector <T>::operator [] (int index) {
    return this->privateArray[index];
}

template <class T>
int TVector <T>::Size () const {
    return privateArraySize;
}

template <class T>
int TVector <T>::Capacity () const {
    return this->privateArrayOccupiedSize;
}

template <class T>
TVector <T> &TVector <T>::operator = (const TVector <T> &inp) {
    return *this;
}

template <class T>
TVector <T>::TVector () {
    privateArraySize = DEFAULT_INT_VALUE;
    privateArrayOccupiedSize = DEFAULT_INT_VALUE;
    privateArray = new T[privateArraySize];
}

template <class T>
TVector <T>::TVector (const int n) {
    privateArraySize = n;
    privateArrayOccupiedSize = DEFAULT_INT_VALUE;
    privateArray = new T[privateArraySize];
}

template <class T>
TVector <T>::TVector (const TVector <T> &inp) {
    privateArraySize = inp.privateArraySize;
    privateArrayOccupiedSize = inp.privateArrayOccupiedSize;
    privateArray = inp.privateArray;
}

template <class T>
TVector <T>::~TVector () {
    delete[] privateArray;
    privateArraySize = DEFAULT_INT_VALUE;
    privateArrayOccupiedSize = DEFAULT_INT_VALUE;
}

#endif // TVECTOR_HPP