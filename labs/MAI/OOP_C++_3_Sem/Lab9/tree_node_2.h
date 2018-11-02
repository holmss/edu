#ifndef NODE_2_H
#define NODE_2_H
#include "Shape.h"
#include <iostream>
#include <cstdlib>
#include <memory>

using namespace std;

template <class T> class TNode_2 : enable_shared_from_this<TNode_2<T>> {
private:
	shared_ptr<TNode_2<T>> parent;
	shared_ptr<TNode_2<T>> brother;
	shared_ptr<TNode_2<T>> son;
	shared_ptr<T> value;
public:
	TNode_2();
	TNode_2(shared_ptr<T> value);
	void SetSon(shared_ptr<TNode_2<T>> son);
	void SetBrother(shared_ptr<TNode_2<T>> brother);
	void SetParent(shared_ptr<TNode_2<T>> parent);
	shared_ptr<TNode_2<T>> Parent();
	shared_ptr<TNode_2<T>> Son();
	shared_ptr<TNode_2<T>> Brother();
	shared_ptr<T> GetShape();
	virtual ~TNode_2();
};

#endif