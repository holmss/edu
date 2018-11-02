//
// Created by Maxim Spiridonov on 29.09.17.
//

#include "String.h"

TString::TString (const char *string) {
    privateString = new char[strlen(string) + SIZE_DIFFERENCE];
    strcpy(privateString, string);
}

TString::TString (TString const &string) {
    privateString = new char[strlen(string.privateString) + SIZE_DIFFERENCE];
    strcpy(privateString, string.privateString);
}

TString & TString::operator = (const TString &string) {
    char *newString = new char[strlen(string.privateString) + SIZE_DIFFERENCE];
    delete[] privateString;

    privateString = newString;
    strcpy(privateString, string.privateString);

    return *this;
}

TString &TString::operator = (const char *string){
    char *newString = new char[strlen(string) + SIZE_DIFFERENCE];
    delete[] privateString;

    privateString = newString;
    strcpy(privateString, string);

    return *this;
}

bool TString::operator == (const TString &string) const {
    return !strcmp(privateString, string.privateString);
}

char &TString::operator [] (int i) const {
    return *(privateString + i);
}

char &TString::operator [] (int i) {
    return *(privateString + i);
}

const std::size_t TString::Length () const {
    return strlen(privateString);
}

TString::~TString () {
    delete[] privateString;
}

std::istream &operator >> (std::istream &is, TString& str) {
    is >> str.privateString;
    return is;
}

std::ostream &operator << (std::ostream &os, const TString &str) {
    os << str.privateString;
    return os;
}

TString::TString (const int bufferSize) {
    privateString = new char[bufferSize + SIZE_DIFFERENCE];
}

void TString::ToLower () {
    for (int i = 0; i < this->Length(); ++i) {
        if (this->operator[](i) >= 'A' && this->operator[](i) <= 'Z') {
            this->operator[](i) = 'a' + this->operator[](i) - 'A';
        }
    }
}

TString &TString::operator + (const TString &str) {
    char* newStr = new char[this->Length()+str.Length()+SIZE_DIFFERENCE];
    strcpy(newStr,this->privateString);
    strcpy(newStr+this->Length(),str.privateString);
    TString *result = new TString(newStr);
    delete [] newStr;
    return *result;
}

TString::operator const char * () const {
    return this->privateString;
}

TString::operator const char * () {
    return this->privateString;
}

TString &TString::operator += (const TString &str) {
    *this=*this+str;
    return *this;
}
