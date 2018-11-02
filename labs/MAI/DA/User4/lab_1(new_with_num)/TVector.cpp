#include "TVector.h"
TVector::TVector() {
    array = nullptr;
    size = 0;
    capacity = 0;
}

size_t MaxNumberDig(size_t& first, size_t& second){
    if (first > second)
        return first;
    return second;
}

TVector::TVector(const int& sizeVector) {
    size = sizeVector;
    capacity = 0;
    array = new TData[sizeVector];
}
void TVector::Push_back(const TData &temp) {

    if (size == capacity) {
        size *= 2;
        TData *result = new TData[size];
        for (int index = 0; index < capacity; index++) {
            result[index] = array[index];
        }
        delete[] array;
        this->array = result;

    }
    array[capacity++] = temp;
}


int TVector::Size() const {
    return size;
}

int TVector::Capacity() const {
    return capacity;
}

TData& TVector::operator[](const int& index) {
    return array[index];
}

void TVector::CountingSort(const int& pos, const int& left, const int& right, int *indexArr) {
    int *support = new int[pos+1]{0};
    uint64_t *digits = new uint64_t[this->capacity];

    for (int i = 0; i < capacity; i++) {
        digits[i] = array[indexArr[i]].FetchRadix(left, right);
        support[digits[i]]++;
    }
    for (int i = 1; i <= pos; i++) {
        support[i] = support[i]+support[i-1];
    }
    uint64_t *result = new uint64_t[capacity];
    for (int i = (int)capacity - 1; i >= 0; i--) {
        result[support[digits[i]] - 1] = indexArr[i];
        support[digits[i]]--;
    }
    delete [] support;
    delete [] digits;
    for (int i = 0; i < capacity; i++) {
       indexArr[i] = result[i];
    }
    delete [] result;
}

int RoundDown (double t) {
    double val;
    modf(t, &val);
    return (int)val;
}
int SetLogNum (int r) {
    int counter=1;
    while(counter<r){
        counter*=2;
    }
    int prevCounter = counter/2;
    if(counter-r<=r-prevCounter){
        r=counter;
    }else{
        r=prevCounter;
    }
    if(r>64){
        r=64;
    }
    return r;
}
void TVector::RadixSort(/*TVector& answer*/) {
    int *indexArray = new int[capacity];
    for (int i = 0;i < capacity; i++) indexArray[i] = i;
    int b = sizeof(uint64_t) * 8;
    int r = SetLogNum(RoundDown(log2(capacity)));
    int maxDigits = static_cast<int>(pow(2, r));
    maxDigits--;
    int left = b - r;
    int right = b - r;
    for (int i = r; i <= b; i += r) {
        CountingSort(maxDigits, left, right, indexArray);
        left -= r;
    }
    for (int i = 0; i < capacity; i++) {
        array[indexArray[i]].Print();
    }
    delete [] indexArray;
}

TVector::~TVector() {
    delete [] array;
}
