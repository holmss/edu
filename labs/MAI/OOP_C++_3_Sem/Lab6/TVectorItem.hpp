#ifndef TVECTORITEM_HPP
#define TVECTORITEM_HPP

#include "TVectorItem.h"

template <class T>
TVectorItem <T>::TVectorItem () {
    this->_item = nullptr;
    //std::cout << "TVectorItem: null created" << std::endl;
}

template <class T>
TVectorItem <T>::TVectorItem (T &item) {
    this->_item = &item;
    //std::cout << "TVectorItem: created" << std::endl;
}

template <class T>
TVectorItem <T>::TVectorItem (T *item) {
    this->_item = item;
    //std::cout << "TVectorItem: created" << std::endl;
}

template <class T>
TAllocationBlock TVectorItem <T>::_stackItemAllocator (sizeof(T),1600000);

template <class A>
std::ostream &operator << (std::ostream &os, const TVectorItem <A> &obj) {
    //os << "[" << *obj._item << "]" << std::endl;
    obj._item->Print();
    return os;
}

template <class T>
void *TVectorItem <T>::operator new (size_t size) {
    return _stackItemAllocator.allocate();
}

template <class T>
void *TVectorItem <T>::operator new [](size_t count) {
    return _stackItemAllocator.allocateSome(count);
}

template <class T>
void TVectorItem <T>::operator delete (void *p) {
    _stackItemAllocator.deallocate(p);
}

template <class T>
void TVectorItem <T>::operator delete[] (void *p, size_t count) {
    _stackItemAllocator.deallocateSome(p,count);
}

template <class T>
TVectorItem <T>::~TVectorItem () {
    //std::cout << "TVectorItem deleted" << std::endl;
}

#endif //PROG_TVECTORITEM_HPP