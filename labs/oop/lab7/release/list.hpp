#ifndef TLIST_H
#define	TLIST_H
#include <memory>
#include "linkedlist.hpp"
#include "TIterator.hpp"
#include "IRemoveCriteria.hpp"

template <class T,class TT> class TList {

public:
    TList();
    
    void InsertSubitem(TT* value);
    void RemoveSubitem(IRemoveCriteria<TT> * criteria);
    void PushBack(T* value);
    bool Remove(T* value);
    size_t Size();
    
    Iter<TListItem<T>, T> begin() const;
    Iter<TListItem<T>, T> end() const;
    template <class A,class AA> friend std::ostream& operator<<(std::ostream& os,const TList<A,AA>& list);
    
    virtual ~TList();
private:
    std::shared_ptr<TListItem<T>> head;
};

#endif