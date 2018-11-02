#ifndef NTREE_2_H
#define NTREE_2_H
#include "tree_node_2.h"
#include "iterator.h"
#include "IRemoveCriteria.h"

template <class TT> class NTree_2 { //T - type of value,  TT - type of the container of 1 level
private:
	shared_ptr<TNode_2<TT>> root;
public:
	NTree_2();
	void deleterec(shared_ptr<TNode_2<TT>> node);
	void Insert_2(shared_ptr<TT> value, char *path, char *who);
	shared_ptr<TNode_2<TT>> Search_2(char *path);
	void Delete(char *path);
	shared_ptr<TNode_2<TT>> Minimum() const;
	shared_ptr<TNode_2<TT>> Maximum() const;
	TIterator<TNode_2<TT>, TT> begin() const;
	TIterator<TNode_2<TT>, TT> end() const;
	virtual ~NTree_2();
};

#endif