#ifndef TSTRING_H
#define TSTRING_H
#include "iostream"
#include "cstdio"

const int MAX_SIZE_STRING = 30000;
class TString {
private:
    char *data;
    size_t size;
public:
    TString ();
    TString (const char *);
    TString (const TString &);
    size_t & Size();
    char*& GetSting();
    char& operator[](unsigned long &);
    const char& operator[] (unsigned long) const;
    TString& operator=(const char *);
    TString& operator=(const TString &);
    ~TString();

};


#endif
