//
// Created by Maxim Spiridonov on 29.09.17.
//

#ifndef TSTRING_H
#define TSTRING_H

#include <cstring>
#include <iostream>

class TString {
public:
    explicit TString (const char *string = "");

    TString (TString const &string);

    explicit TString (const int bufferSize);

    TString &operator = (const TString &string);

    operator const char *() const;

    operator const char *();

    TString &operator = (const char *string);

    TString &operator + (const TString &str);

    TString &operator += (const TString &str);

    bool operator == (const TString &string) const;

    void ToLower ();

    char &operator [] (int) const;

    char &operator [] (int);

    friend std::istream &operator >> (std::istream &is, TString &str);

    friend std::ostream &operator << (std::ostream &os, const TString &str);

    const size_t Length () const;

    virtual ~TString ();

private:
    char *privateString;
    int const SIZE_DIFFERENCE = 1;
};

#endif //TSTRING_H
