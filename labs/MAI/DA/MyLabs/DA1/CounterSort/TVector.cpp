//
// Created by Maxim Spiridonov on 06.10.17.
//

#include "TVector.h"

void TVector::FastPushBack (TPair &data) {
    if (privateArraySize == privateArrayOccupiedSize) {
        privateArraySize *= 2;
        TPair *result = new TPair[privateArraySize];

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

void TVector::Clear () {
    delete[] privateArray;
    privateArraySize = DEFAULT_INT_VALUE;
    privateArrayOccupiedSize = DEFAULT_INT_VALUE;
    privateArray = new TPair[privateArraySize];
}

TPair &TVector::operator [] (int index) {
    return this->privateArray[index];
}

int TVector::Size () const {
    return privateArraySize;
}

int TVector::Capacity () const {
    return this->privateArrayOccupiedSize;
}

TVector &TVector::operator = (const TVector &inp) {
    return *this;
}

TVector::TVector () {
    privateArraySize = DEFAULT_INT_VALUE;
    privateArrayOccupiedSize = DEFAULT_INT_VALUE;
    privateArray = new TPair[privateArraySize];
}

TVector::TVector (const int n) {
    privateArraySize = n;
    privateArrayOccupiedSize = DEFAULT_INT_VALUE;
    privateArray = new TPair[privateArraySize];
}

TVector::TVector (const TVector &inp) {
    privateArraySize = inp.privateArraySize;
    privateArrayOccupiedSize = inp.privateArrayOccupiedSize;
    privateArray = inp.privateArray;
}

void TVector::CountingSort () {

    //clock_t start = clock();
    int max = 0;
    for (int i = 0; i < privateArrayOccupiedSize; i++) {
        if (privateArray[i].Key > max) {
            max = (privateArray)[i].Key;
        }
    }
    TPair *res = new TPair[privateArrayOccupiedSize];

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
    //clock_t end = clock();
    //printf("\nCounter SortTime = %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
}

TVector::~TVector () {
    delete[] privateArray;
    privateArraySize = DEFAULT_INT_VALUE;
    privateArrayOccupiedSize = DEFAULT_INT_VALUE;
}
