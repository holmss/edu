#include "tree_node_2.h"

using namespace std;

template <class T> TNode_2<T>::TNode_2()
{
	this->parent = nullptr;
	this->brother = nullptr;
	this->son = nullptr;
	this->value = nullptr;
}
template <class T> TNode_2<T>::TNode_2(shared_ptr<T> value)
{
	this->parent = nullptr;
	this->brother = nullptr;
	this->son = nullptr;
	this->value = value;
}
template <class T> void TNode_2<T>::SetSon(shared_ptr<TNode_2<T>> son)
{
	this->son = son;
}
template <class T>void TNode_2<T>::SetBrother(shared_ptr<TNode_2<T>> brother)
{
	this->brother = brother;
}
template <class T>void TNode_2<T>::SetParent(shared_ptr<TNode_2<T>> parent)
{
	this->parent = parent;
}
template <class T> shared_ptr<TNode_2<T>> TNode_2<T>::Parent()
{
	return this->parent;
}
template <class T> shared_ptr<TNode_2<T>> TNode_2<T>::Son()
{
	return this->son;
}
template <class T> shared_ptr<TNode_2<T>> TNode_2<T>::Brother()
{
	return this->brother;
}
template <class T> shared_ptr<T> TNode_2<T>::GetShape()
{
	return this->value;
}
template <class T>  TNode_2<T>::~TNode_2()
{
	this->parent = nullptr;
	this->brother = nullptr;
	this->son = nullptr;
	this->value = nullptr;
}

#include "ntree.h"
template class TNode_2<TNTree<TShape>>;
#include <functional>
template class TNode_2<function<void(void)>>;