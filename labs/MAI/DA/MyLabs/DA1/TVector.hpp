//
// Created by Maxim Spiridonov on 29.09.17.
//

#ifndef TVECTOR_HPP
#define TVECTOR_HPP

#include "TVector.h"

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
void TVector<T>::CountingSort () {

    time_t start = time(0);
    int max = 0;
    for (int i = 0; i < privateArrayOccupiedSize; i++) {
        if (privateArray[i].Key > max) {
            max = (privateArray)[i].Key;
        }
    }
    T *res = new T[privateArrayOccupiedSize];

    int *countMass = new int[max + 1]{0};
    for (int i = 0; i < privateArrayOccupiedSize; ++i) {
        countMass[privateArray[i].Key]++;
    }

    for (int i = 1; i <= max; ++i) {
        countMass[i] = countMass[i] + countMass[i - 1];
    }

    for (int i = privateArrayOccupiedSize - 1; i >= 0; i--) {
        int tmp = countMass[privateArray[i].Key] - 1;
        res[tmp] = privateArray[i];
        countMass[privateArray[i].Key] = countMass[privateArray[i].Key] - 1;
    }
    for (int i = 0; i < privateArrayOccupiedSize; ++i) {
        privateArray[i] = res[i];
    }
    delete[] countMass;
    delete[] res;

    time_t end = time(0);
    printf("\nCounter SortTime = %li\n",end - start);
}

template <class T>
TVector <T>::~TVector () {
    delete[] privateArray;
    privateArraySize = DEFAULT_INT_VALUE;
    privateArrayOccupiedSize = DEFAULT_INT_VALUE;
}

#endif // TVECTOR_HPP