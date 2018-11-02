#ifndef TData_H
#define TData_H

#include <cstdint>
#include "cstdio"
int const MAX_SIZE_VALUE = 2100;
int const MAX_SIZE_KEY = 30;

class TData{
private:
    uint64_t key;
    char* keyString;
    char* value;
public:
    TData();
    TData(TData& orig);
    TData& operator=(const TData &obj);
    void Print();
    int InputStream();
    //find
    uint64_t FetchRadix(const int &, const int &) ;
    ~TData();
};

#endif
