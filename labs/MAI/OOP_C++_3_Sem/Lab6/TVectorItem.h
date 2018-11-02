#ifndef TVECTORITEM_H
#define TVECTORITEM_H

#include <memory>
#include "iostream"
#include "TAllocationBlock.h"

template <class T>
class TVectorItem {
public:

    //TVectorItem();

    TVectorItem ();

    TVectorItem (T &item);

    TVectorItem (T *item);

    template <class A>
    friend std::ostream &operator << (std::ostream &os, const TVectorItem <A> &obj);

    void *operator new (size_t size);

    void *operator new[] (size_t count);

    void operator delete (void *p);

    void operator delete[] (void *p, size_t count);

    virtual ~TVectorItem ();

private:

    static TAllocationBlock _stackItemAllocator;

    T* _item;
};

#include "TVectorItem.hpp"

#endif //PROG_TVECTORITEM_H
