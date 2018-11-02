#include "TVector.h"

void TVector::FastPushBack (std::shared_ptr <Figure> &data) {
    if (privateArraySize == privateArrayOccupiedSize) {
        privateArraySize *= 2;
        std::shared_ptr <Figure> *result = new std::shared_ptr <Figure>[privateArraySize];

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
    privateArray = new std::shared_ptr <Figure>[privateArraySize];
}

std::shared_ptr <Figure> &TVector::operator [] (int index) {
    return this->privateArray[index];
}

std::shared_ptr <Figure> &TVector::operator [] (int index) const {
    return this->privateArray[index];
}

int TVector::Size () const {
    return privateArraySize;
}

int TVector::Capacity () const {
    return privateArrayOccupiedSize;
}

TVector &TVector::operator = (const TVector &inp) {
    return *this;
}

TVector::TVector () {
    privateArraySize = DEFAULT_INT_VALUE;
    privateArrayOccupiedSize = DEFAULT_INT_VALUE;
    privateArray = new std::shared_ptr <Figure>[privateArraySize];
}

TVector::TVector (const int n) {
    privateArraySize = n;
    privateArrayOccupiedSize = DEFAULT_INT_VALUE;
    privateArray = new std::shared_ptr <Figure>[privateArraySize];
}

TVector::TVector (const TVector &inp) {
    privateArraySize = inp.privateArraySize;
    privateArrayOccupiedSize = inp.privateArrayOccupiedSize;
    privateArray = inp.privateArray;
}

void TVector::Remove (int index){
    bool deleted = false;
    for(int i = 0; i<privateArrayOccupiedSize;++i){
        if(i==index && !deleted){
            deleted =true;
        }else if(i!=index && deleted){
            privateArray[i-1] = privateArray[i];
        }
    }
    --privateArrayOccupiedSize;
}

TVector::~TVector () {
    delete[] privateArray;
    privateArraySize = DEFAULT_INT_VALUE;
    privateArrayOccupiedSize = DEFAULT_INT_VALUE;
}

std::ostream &operator << (std::ostream &os, const TVector &obj) {
    for (int i = 0; i < obj.Capacity(); ++i) {
        obj[i]->Print();
    }
    return os;
}
