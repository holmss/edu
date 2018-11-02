#include <cstring>
#include "TString.h"
TString::TString() {
    data = new char[1];
    data[0] ='\0';
    size = 0;
}
TString::TString (const char *string) {
    size = std::strlen(string);
    data = new char[size+1];
    std::strcpy(data, string);
}

TString::TString (const TString &string) {
    size = string.size;
    data = new char[size+1];
    strcpy(data, string.data);
}

size_t& TString::Size() {
    return size;
}

TString& TString::operator=(const TString &obj){
    if (this == &obj)
        return *this;
    delete [] data;
    size = obj.size;
    data = new char[size+1];
    std::strcpy(data, obj.data);
    return *this;
}

TString &TString::operator=(const char *string) {
    delete [] data;
    size = std::strlen(string);
    data = new char[size+1];
    std::strcpy(data, string);
    return *this;
}


char*& TString::GetSting(){
    return data;
}
char& TString::operator[](unsigned long& index) {
    return data[index];
}

const char& TString::operator [] (unsigned long index) const {
    return data[index];
}


TString::~TString(){
    delete [] data;
}
