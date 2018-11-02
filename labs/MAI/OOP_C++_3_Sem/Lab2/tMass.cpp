#include "tMass.h"

TMass::TMass (size_t n) {
    this->_trianglePrivateMass = new Triangle[n];
    this->_size = n;
    this->_countOfElements = DEFAULT_COUNT;
#ifndef NDEBUG
    std::cout << "TMass created with size = " << n << std::endl;
#endif
}

std::ostream &operator << (std::ostream &os, const TMass &mass) {
    for (size_t i = 0; i < mass._countOfElements; ++i) {
        os << " " << mass.GetTriangle(i) << " " << std::endl;
    }
    return os;
}

void TMass::AddToFirstFree (const Triangle &tr) {
    size_t firstFree = 0;
    if (_size == 0) {
        Resize(SIZE_DIFF);
    } else {
        Triangle t = Triangle();
        for (size_t i = 0; i < _size; ++i) {
            firstFree = i;
            if (this->_trianglePrivateMass[i] == t) {
                break;
            }
        }
        if (firstFree == _size - SIZE_DIFF) {
            Resize(_size + SIZE_DIFF);
            firstFree = _size - SIZE_DIFF;
        }
    }
    this->_trianglePrivateMass[firstFree] = tr;
    this->_countOfElements++;
}

bool TMass::Delete (const Triangle &tr) {
    bool res = false;

    for (int i = 0; i < _countOfElements; ++i) {
        if (this->_trianglePrivateMass[i] == tr) {
            this->_trianglePrivateMass[i] = Triangle();
            res = true;
            break;
        }
    }
    if (res) {
        this->_countOfElements--;
    }
    return res;
}

void TMass::Resize (size_t newSize) {
#ifndef NDEBUG
    std::cout << "TMass resized " << this->_size << "->" << newSize << std::endl;
#endif

    Triangle *new_arr = new Triangle[newSize];

    if (this->_size < newSize) {
        this->_size = newSize;
    }

    for (size_t i = 0; i < this->_size; ++i)
        new_arr[i] = _trianglePrivateMass[i];

    delete[] _trianglePrivateMass;

    this->_trianglePrivateMass = new_arr;
}

Triangle &TMass::GetTriangle (int n) const {
    Triangle res;
    if (n < _size) {
        res = this->_trianglePrivateMass[n];
    }
    return res;
}

TMass::TMass () {
    this->_trianglePrivateMass = new Triangle[DEFAULT_COUNT];
    this->_size = DEFAULT_COUNT;
    this->_countOfElements = DEFAULT_COUNT;
#ifndef NDEBUG
    std::cout << "TMass created with null " << std::endl;
#endif
}

TMass::~TMass () {
    delete[] _trianglePrivateMass;
    this->_size = DEFAULT_COUNT;
    this->_countOfElements = DEFAULT_COUNT;

#ifndef NDEBUG
    std::cout << "TMass deleted " << std::endl;
#endif
}

size_t TMass::GetInternalMassSize () {
    return this->_size;
}

size_t TMass::GetItemsCount () {
    return this->_countOfElements;
}

bool TMass::Replace (const Triangle &oldT, const Triangle &newT) {
#ifndef NDEBUG
    std::cout << "Try replace (" << oldT << ")->(" << newT << ")" << std::endl;
#endif
    bool res = Delete(oldT);
    if (res) {
        AddToFirstFree(newT);
    }
#ifndef NDEBUG
    if (res) {
        std::cout << "Sucess replace (" << oldT << ")->(" << newT << ")"
                  << std::endl;
    } else {
        std::cout << "Fail replace (" << oldT << ")->(" << newT << ")" << std::endl;
    }
#endif
    return res;
}
