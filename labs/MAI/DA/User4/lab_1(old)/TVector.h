#include "TData.h"
#include "iostream"

#ifndef TVECTOR_H
#define TVECTOR_H
const int NUMBERS = 10;
const int NUMBERS_KEY = 3;
const int BASE = 10;
class TVector {
private:
    size_t size;
    TData *array;
public:
    TVector();

    TVector(const int &);

    TData &operator[](const int &);

    size_t Size() const;

    void Push_back(const TData &);

    void CountingSort(const int &, const int &, int*);

    void RadixSort(/*TVector&*/);
    friend Ttype MaxNumberDig(const Ttype&, const Ttype&);
    ~TVector();
};


#endif //LAB1_TVECTOR_H
