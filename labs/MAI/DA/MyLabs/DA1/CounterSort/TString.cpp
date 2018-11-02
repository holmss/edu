//
// Created by Maxim Spiridonov on 29.09.17.
//

#include "TString.h"

TString::TString (const char *string) {
    privateString = new char[strlen(string) + SIZE_DIFFERENCE];
    strcpy(privateString, string);
}

TString::TString (TString const &string) {
    privateString = new char[strlen(string.GetCharArray()) + SIZE_DIFFERENCE];
    strcpy(privateString, string.GetCharArray());
}

TString &TString::operator = (const TString &string) {
    char *newString = new char[strlen(string.GetCharArray()) + SIZE_DIFFERENCE];
    delete[] privateString;

    privateString = newString;
    strcpy(privateString, string.GetCharArray());

    return *this;
}

TString &TString::operator = (const char *string) {
    char *newString = new char[strlen(string) + SIZE_DIFFERENCE];
    delete[] privateString;

    privateString = newString;
    strcpy(privateString, string);

    return *this;
}

bool TString::operator == (const TString &string) const {
    return !strcmp(privateString, string.GetCharArray());
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

char *TString::GetCharArray () {
    return this->privateString;
}
char *TString::GetCharArray () const{
    return this->privateString;
}
