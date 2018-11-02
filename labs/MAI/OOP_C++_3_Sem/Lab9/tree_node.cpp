#include "tree_node.h"

using namespace std;

template <class T> TNode<T>::TNode(recursive_mutex *mutex)
{
	this->brother = nullptr;
	this->son = nullptr;
	this->parent = nullptr;
	this->tree_mutex = mutex;
}
template <class T> TAllocBlock TNode<T>::TNode_allocator(sizeof(TNode<T>), 100);

template <class T> void TNode<T>::SetShape(shared_ptr<T> shape)
{
	unique_lock<recursive_mutex> lock(*this->tree_mutex);
	this->shape = shape;
}
template <class T> TNode<T>::TNode(recursive_mutex *mutex, shared_ptr<T> sh)
{
	brother = nullptr;
	son = nullptr;
	parent = nullptr;
	shape = sh;
	this->tree_mutex = mutex;
}
template <class T> void TNode<T>::SetBrother(shared_ptr<TNode <T>> node)
{
	unique_lock<recursive_mutex> lock(*this->tree_mutex);
	if (this->brother == nullptr) {
		this->brother = node;
	}
	else {
		this->SetBrother(node);
	}
}
template <class T> void TNode<T>::SetSon(shared_ptr<TNode <T>> node)
{
	unique_lock<recursive_mutex> lock(*this->tree_mutex);
	if (this->son == nullptr) {
		this->son = node;
	}
	else {
		this->SetBrother(node);
	}
}
template <class T> void TNode<T>::SetParent(shared_ptr<TNode <T>> node)
{
	unique_lock<recursive_mutex> lock(*this->tree_mutex);
	this->parent = node;
}
template <class T> shared_ptr<TNode<T>> TNode<T>::Son()
{
	lock_guard<recursive_mutex> lock(*this->tree_mutex);
	return son ? this->son : nullptr;
}
template <class T> shared_ptr<TNode<T>> TNode<T>::Brother()
{
	lock_guard<recursive_mutex> lock(*this->tree_mutex);
	return brother ? this->brother : nullptr;
}
template <class T> shared_ptr<TNode<T>> TNode<T>::Parent()
{
	lock_guard<recursive_mutex> lock(*this->tree_mutex);
	return parent ? this->parent : nullptr;
}
template <class T> shared_ptr<T> TNode<T>::GetShape()
{
	unique_lock<recursive_mutex> lock(*this->tree_mutex);
	return shape ? this->shape : nullptr;
}
template <class T> double TNode<T>::GetValue()
{
	unique_lock<recursive_mutex> lock(*this->tree_mutex);
	return this->shape->Square();
}

template <class T> bool TNode<T>::operator == (shared_ptr<TNode<T>> &right)
{
	unique_lock<recursive_mutex> lock(*this->tree_mutex);
	if (this->shape == right->shape) {
		return true;
	}
	else return false;
}
template <class T> TNode<T> &TNode<T>::operator = (shared_ptr<TNode<T>> &right)
{
	unique_lock<recursive_mutex> lock(*this->tree_mutex);
	if (shared_from_this() == right) {
		return *this;
	}
	else {
		son = right->son;
		brother = right->brother;
		shape = right->shape;
		return *this;
	}
}
template <class T> int TNode<T>::Son_qty()
{
	unique_lock<recursive_mutex> lock(*this->tree_mutex);
	int count = 1;
	shared_ptr<TNode<T>> node = this->son;
	while (node->brother != nullptr) {
		count++;
		node = node->brother;
	}
	return count;
}
template <class T> shared_ptr<TNode<T>> TNode<T>::search_rec(shared_ptr<T> sh)
{
	unique_lock<recursive_mutex> lock(*this->tree_mutex);
	if (!(this->shape == sh)) {
		if (this->son != nullptr) {
			shared_ptr<TNode<T>> tmp = this->Son();
			return tmp->search_rec(sh);
		}
		if (this->brother != nullptr) {
			shared_ptr<TNode<T>> tmp = this->Brother();
			return tmp->search_rec(sh);
		}
	}
	return shared_from_this();
}
template <class T> TNode<T>::~TNode()
{
	son = nullptr;
	brother = nullptr;
	parent = nullptr;
}
template <class T> void *TNode<T>::operator new (size_t size) 
{
	return TNode_allocator.allocate();
}
template <class T> void TNode<T>::operator delete (void *p)
{
	return TNode_allocator.deallocate(p);
}

#include "Shape.h"
template class TNode<TShape>;
