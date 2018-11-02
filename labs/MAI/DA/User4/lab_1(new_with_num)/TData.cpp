#include <cstring>
#include "TData.h"
#include <iostream>
TData::TData(){
    key = 0;
    value = new char[MAX_SIZE_VALUE];
    keyString = new char[MAX_SIZE_KEY];
}

TData::TData(TData& orig) {
    key = orig.key;
    strcpy(value, orig.value);
    strcpy(keyString, orig.keyString);
}

TData& TData::operator=(const TData &obj){
    if (this == &obj)
        return *this;
    key = obj.key;
    strcpy(keyString, obj.keyString);
    strcpy(value, obj.value);
    return *this;
}

void TData::Print() {
    printf("%s\t%s\n", keyString, value);
}
int TData::InputStream() {
    if (scanf("%s", keyString) == EOF)
    {
        //delete [] keyString;
        return 0;
    }
    key = 0;
    if (keyString[0] == '0') return 0;
    int sizeDig = std::strlen(keyString);
    uint64_t degree = 1;
    for(int i = sizeDig - 1; i >= 1; i--) {
        if (keyString[i]!='-') {
            key += (int) (keyString[i] - '0') * degree;
            degree *= 10;
        }
    }
    scanf("%s", value);
    return 1;
}



uint64_t TData::FetchRadix(const int& left, const int& right) {
    uint64_t answer = (key << left);
    answer = answer >> right;
    return answer;
}
TData::~TData(){
    delete [] value;
    delete [] keyString;
}
