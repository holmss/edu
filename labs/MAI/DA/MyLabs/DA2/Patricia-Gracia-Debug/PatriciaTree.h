//
// Created by Maxim Spiridonov on 21.10.17.
//

#ifndef PATR_PATRICIATREE_H
#define PATR_PATRICIATREE_H

#include "Model.h"
#include "StackContainer.h"
#include <fstream>
#include "iostream"

class TPatriciaTree {
public:
    TPatriciaTree ();

    //const unsigned long long *Search (const char *, unsigned int);

    const unsigned long long *Search (TPair &tmp);

    //bool Insert (const char *, unsigned int, unsigned long long);

    bool Insert (TPair &tmp);

    //bool Remove (const char *, unsigned int);

    bool Remove (TPair &inp);

    void Load (TString& str);

    void Save (TString& str);

    virtual ~TPatriciaTree ();

private:
    TString &CopyEndOfStr (const TString &str, int count);
    TString &CopyStartOfStr (const TString &str, int count);
    TPatriciaTree *next;
    TPatriciaTree *link;
    //char *key;
    //unsigned int length;
    //unsigned long long data;
    TPair pair;
};

#endif //PATR_PATRICIATREE_H
