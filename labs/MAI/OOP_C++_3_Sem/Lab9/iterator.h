#ifndef ITERATOR_H
#define ITERATOR_H

#include <memory>
#include <iostream>

using namespace std;

template <class Tnode, class T> class TIterator {
public:
	TIterator(shared_ptr<Tnode> n) //node - is current elem
	{
		node = n;
	}
	shared_ptr<T> operator * () //returns the value of the shape - square
	{
		if (node != nullptr) {
			return node->GetShape();
		}
		else return nullptr;
	}
	shared_ptr<T> operator -> () //returns shape from current node
	{
		if (node != nullptr) {
			return node->GetShape();
		}
		else return nullptr;
	}
	void operator ++ () // this operator - walking of the tree. Minimum  - is the deepest son. We are going to the brother and then his minimum. But if brother null, then go to parent
	{
		if (node->Brother()) {
			node = node->Brother();
			if (node->Son()) {
				node = node->Son();
				while (node->Son()) {
					node = node->Son();
				}
			}
		} else if (node->Parent()) {
			node = node->Parent();
		}
	}
	TIterator operator ++(int)
	{
		TIterator iter(*this);
		++(*this);
		return iter;
	}
	bool operator == (TIterator const i) //comparing
	{
		return this->node == i.node;
	}
	bool operator != (TIterator const i)//comparing
	{
		return !(*this == i);
	}
private:
	shared_ptr<Tnode> node;
};

#endif