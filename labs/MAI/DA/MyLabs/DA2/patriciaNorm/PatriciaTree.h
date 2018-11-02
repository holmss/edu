//
// Created by Maxim Spiridonov on 21.10.17.
//

#ifndef PATR_PATRICIATREE_H
#define PATR_PATRICIATREE_H

#include "StackContainer.h"
#include <fstream>
#include "iostream"

class TPatriciaTree {
public:
    TPatriciaTree ();

    const unsigned long long *Search (const char *, unsigned int);

    bool Insert (const char *, unsigned int, unsigned long long);

    bool Remove (const char *, unsigned int);

    void Load (const char *);

    void Save (const char *);

    //void Print (const TPatriciaTree *node = nullptr, int lvl = -1);

    virtual ~TPatriciaTree ();

private:
    TPatriciaTree *next;
    TPatriciaTree *link;
    char *key;
    unsigned int length;
    unsigned long long data;
};

#endif //PATR_PATRICIATREE_H
