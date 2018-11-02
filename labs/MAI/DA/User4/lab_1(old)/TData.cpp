#include <cstring>
#include "TData.h"
#include <iostream>
TData::TData(){
    keyCountry = 0;
    keyCity = 0;
    keyNumbers = 0;
    sizeCountry = 0;
    sizeCity = 0;
    sizeNumbers = 0;
    value = TString();
}

TData::TData(Ttype keyC, Ttype keyCt, Ttype keyN,
             TString valuePair):
        keyCountry(keyC), keyCity(keyCt),
        keyNumbers(keyN), value(valuePair){}

TData::TData(TData& orig) {
    keyCountry = orig.keyCountry;
    keyCity = orig.keyCity;
    keyNumbers = orig.keyNumbers;
    value = orig.value;
}

TData& TData::operator=(const TData &obj){
    if (this == &obj)
        return *this;
    this->keyCountry = obj.keyCountry;
    this->sizeCountry = obj.sizeCountry;
    this->keyCity = obj.keyCity;
    this->sizeCity = obj.sizeCity;
    this->keyNumbers = obj.keyNumbers;
    this->sizeNumbers = obj.sizeNumbers;
    this->value = obj.value;
    return *this;
}

void TData::Print() {
    printf("+");
    int base = 1;
    int count = 0;
    while (keyCountry/base != 0) {
        base *= 10;
        count++;
    }
    for (int i = 0; i < sizeCountry-count; i++) {
        printf("0");
    }
    if (keyCountry == 0)
        count++;
    printf("%d-", keyCountry);
    base = 1;
    count = 0;
    while (keyCity/base != 0) {
        base *= 10;
        count++;
    }
    if (keyCity == 0)
        count++;
    for (int i = 0; i < sizeCity-count; i++) {
        printf("0");
    }
    printf("%d-", keyCity);
    base = 1;
    count = 0;
    while (keyNumbers/base != 0) {
        base *= 10;
        count++;
    }
    if (keyNumbers == 0)
        count++;
    for (int i = 0; i < sizeNumbers-count; i++) {
        printf("0");
    }
    printf("%d", keyNumbers);
    printf("%s", value.GetSting());
//    printf("+%d-%d-%d%s", keyCountry, keyCity,
//           keyNumbers, value.GetSting());
}
int TData::NewInputStream(){
    char temp_1;
    if (scanf("%c", &temp_1) == EOF) {
        return 0;
    }

    return 0;
}
int TData::InputStream() {
    char temp_1;
    if (scanf("%c", &temp_1) == EOF) {
        return 0;
    }
    //scanf("%d%c%d%c%d", &keyCountry, &temp_1, &keyCity, &temp_2, &keyNumbers);
    int countKey = 0;
    int pos = -1;
    int i = -1;
    char *enter = new char[MAX_SIZE_STRING];
    char *job = new char[MAX_SIZE_STRING];
    scanf("%s", enter);
    do {
        pos++;
        i++;
        if (enter[pos] == '-' || enter[pos] == '\0') {
            job[i] = '\0';
            GetKey(countKey) = std::atoi(job);
            GetKeySize(countKey) = std::strlen(job);
            delete [] job;
            job = new char[MAX_SIZE_STRING];
            i = -1;
            countKey++;
            continue;
        }
        job[i] = enter[pos];
    } while (enter[pos] != '\0');
    delete [] job;
    delete [] enter;
    enter = new char[MAX_SIZE_VALUE];
    fgets(enter, MAX_SIZE_VALUE, stdin);
    value = enter;
    delete [] enter;
    return 1;
}
int& TData::GetKeySize(int index){
    if (index == 0)
        return sizeCountry;
    if (index == 1)
        return sizeCity;
    if (index == 2)
        return sizeNumbers;
    return sizeCountry;
}
Ttype& TData::GetKey(int index){
    if (index == 0)
        return keyCountry;
    if (index == 1)
        return keyCity;
    if (index == 2)
        return keyNumbers;
    return keyCountry;
}
TString& TData::GetData() {
    return value;
}

TData::~TData() = default;
