#include "TStack.h"

tp
TStack<T>::TStack()
    : head(nullptr)
{
}

tp
std::ostream& operator<<(std::ostream& os, const TStack<T>& stack)
{

    std::shared_ptr<TStackItem<T>> item = stack.head;

    while (item != nullptr) {
        os << *item;
        item = item->GetNext();
    }

    return os;
}

tp
void TStack<T>::push(std::shared_ptr<T>&& item)
{
    std::shared_ptr<TStackItem<T>> other(new TStackItem<T>(item));
    other->SetNext(head);
    head = other;
}

tp
bool TStack<T>::empty()
{
    return head == nullptr;
}

tp
std::shared_ptr<T> TStack<T>::pop()
{
    std::shared_ptr<T> result;
    if (head != nullptr) {
        result = head->GetValue();
        head = head->GetNext();
    }

    return result;
}

tp
TIterator<TStackItem<T>, T> TStack<T>::begin()
{
    return TIterator<TStackItem<T>, T>(head);
}

tp
TIterator<TStackItem<T>, T> TStack<T>::end()
{
    return TIterator<TStackItem<T>, T>(nullptr);
}

tp
TStack<T>::~TStack()
{
}

#include "Triangle.h"
template class TStack<Triangle>;
template std::ostream& operator<<(std::ostream& os, const TStack<Triangle>& stack);