#ifndef PROG_TMASS_H
#define PROG_TMASS_H

#include "triangle.h"
#include "iostream"

class TMass {
public:
    TMass ();

    TMass (size_t n);

    void AddToFirstFree (const Triangle &tr);

    bool Delete (const Triangle &tr);

    bool Replace (const Triangle &oldT, const Triangle &newT);

    Triangle &GetTriangle (int n) const;

    size_t GetInternalMassSize ();

    size_t GetItemsCount ();

    friend std::ostream &operator << (std::ostream &os, const TMass &mass);

    ~TMass ();

private:
    Triangle *_trianglePrivateMass;
    size_t _size;
    size_t _countOfElements;
    size_t const SIZE_DIFF = 1;
    size_t const DEFAULT_COUNT = 0;

    void Resize (size_t newSize);
};

#endif  // PROG_TMASS_H
