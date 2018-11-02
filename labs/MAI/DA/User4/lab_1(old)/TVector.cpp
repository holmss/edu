#include "TVector.h"
TVector::TVector() {
    array = new TData[1];
    size = 0;
}

Ttype MaxNumberDig(const Ttype& first, const Ttype& second){
    if (first > second)
        return first;
    return second;
}

TVector::TVector(const int& sizeVector) {
    size = sizeVector;
    delete [] array;
    array = new TData[sizeVector];
}
void TVector::Push_back(const TData &temp) {
    TData *result = new TData[++this->size];

    for(int index = 0; index < this->size; index++)
    {
        if(index != this->size - 1)
        {
            result[index] = this->array[index];
        }
        else
        {
            result[index] = temp;
            break;
        }
    }
    delete [] this->array;
    this->array = result;
}


size_t TVector::Size() const {
    return size;
}

TData& TVector::operator[](const int& index) {
    return array[index];
}

void TVector::CountingSort(const int& pos, const int& type, int *indexArr) {
    int *support = new int[NUMBERS]{0};
    int *digits = new int[this->Size()];
    int *result = new int[size];

    for (int i = 0; i < size; i++) {
        digits[i] = (array[indexArr[i]].GetKey(type)/pos)%BASE;
        support[ digits[i] ]++;
    }
    for (int i = 1; i < BASE; i++) {
        support[i] += support[i - 1];
    }
    for (int i = size - 1; i >= 0; i--) {
        result[support[digits[i]] - 1] = indexArr[i];
        support[digits[i]]--;
    }
    delete [] support;
    delete [] digits;
    for (int i = 0; i < size; i++) {
        indexArr[i] = result[i];
    }
    delete [] result;
}

void TVector::RadixSort(/*TVector& answer*/) {
    int *indexArray = new int[this->size];
    for (int i = 0; i < this->size; i++) {
        indexArray[i] = i;
    }
    for (int type = NUMBERS_KEY - 1; type >= 0; type--) {
        Ttype maxNumberOfDigits = 0;
        Ttype exp = 1;
        int length = 0;
        for (int k = 0; k < size; k++) {
            maxNumberOfDigits = MaxNumberDig((array+k)->GetKey(type),
                                             maxNumberOfDigits);
        }
        while (maxNumberOfDigits != 0) {
            maxNumberOfDigits /= BASE;
            length++;
        }
        while (length-- > 0) {
            CountingSort(exp, type, indexArray);
            exp *= BASE;
        }
    }

    for (int i = 0; i < size; i++) {
        array[indexArray[i]].Print();
    }
    delete [] indexArray;
}

TVector::~TVector() {
    delete [] array;
}
