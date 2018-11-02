//
// Created by Maxim Spiridonov on 21.10.17.
//

#ifndef PATR_STACKCONTAINER_H
#define PATR_STACKCONTAINER_H

template <class T>
class TStackData {
public:
    TStackData ();

    T &GetData ();

    TStackData <T> *GetNext ();

    TStackData <T> *GetPrev ();

    virtual ~TStackData ();

    T data;
    TStackData <T> *next;
    TStackData <T> *prev;
};

template <class T>
class TStack : public TStackData <T> {
public:
    TStack ();

    T *Top ();

    void Pop ();

    void Push (T &);

    bool Empty ();

    virtual ~TStack ();

private:
    TStackData <T> *head;
};

#include "StackContainer.hpp"

#endif //PATR_STACKCONTAINER_H
