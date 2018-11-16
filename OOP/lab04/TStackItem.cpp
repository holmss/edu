#include "TStackItem.h"
#include <iostream>

tp
TStackItem<T>::TStackItem(const std::shared_ptr<T>& item)
{
    this->item = item;
    this->next = nullptr;
    std::cout << "Stack item: created" << std::endl;
}

tp
std::shared_ptr<TStackItem<T>> TStackItem<T>::SetNext(std::shared_ptr<TStackItem<T>>& next)
{
    std::shared_ptr<TStackItem<T>> old = this->next;
    this->next = next;
    return old;
}

tp
std::shared_ptr<T> TStackItem<T>::GetValue() const
{
    return this->item;
}

tp
std::shared_ptr<TStackItem<T>> TStackItem<T>::GetNext()
{
    return this->next;
}

tp
TStackItem<T>::~TStackItem()
{
    std::cout << "Stack item: deleted" << std::endl;
}

template <class A>
std::ostream& operator<<(std::ostream& os, const TStackItem<A>& obj)
{
    os << "[" << *obj.item << "]" << std::endl;
    return os;
}

tp
void* TStackItem<T>::operator new(size_t size)
{
    std::cout << "Allocated :" << size << "bytes" << std::endl;
    return malloc(size);
}

tp
void TStackItem<T>::operator delete(void* p)
{
    std::cout << "Deleted" << std::endl;
    free(p);
}

#include "Triangle.h"
template class TStackItem<Triangle>;
template std::ostream& operator<<(std::ostream& os, const TStackItem<Triangle>& obj);