#ifndef TData_H
#define TData_H

#include "TString.h"
#include "cstdio"
//int const NUMBERS_KEY = 3;
using Ttype = int;
int const MAX_SIZE_VALUE = 30000;
int const MAX_SIZE_KEY = 3000;
class TData{
private:
    Ttype keyCountry;
    Ttype keyCity;
    Ttype keyNumbers;
    int sizeCountry;
    int sizeCity;
    int sizeNumbers;
    TString value;
public:
    TData();
    TData(Ttype keyC, Ttype keyCt, Ttype keyN,
          TString valuePair);
    TData(TData& orig);
    void Print();
    Ttype& GetKey(int);
    int& GetKeySize(int);
    TString& GetData();
    int InputStream();
    int NewInputStream();
    TData& operator=(const TData &);
    ~TData();
};

#endif
