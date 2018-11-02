//
// Created by Maxim Spiridonov on 29.09.17.
//

#ifndef TSTRING_H
#define TSTRING_H

#include <cstring>

class TString {
public:
    TString (const char *string = "");

    TString (TString const &string);

    TString &operator = (const TString &string);

    TString &operator = (const char *string);

    bool operator == (const TString &string) const;

    char &operator [] (int) const;

    char &operator [] (int);

    const size_t Length () const;

    char *GetCharArray ();

    char *GetCharArray () const;

    ~TString ();

private:
    char *privateString;
    static int const SIZE_DIFFERENCE = 1;
    static int const DEFAULT_INT_VALUE = 0;
};

#endif //TSTRING_H
