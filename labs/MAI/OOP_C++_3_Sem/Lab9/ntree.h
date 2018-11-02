#ifndef NTREE_H
#define NTREE_H
#include "tree_node.h"
#include "iterator.h"
#include <memory>
#include <future>
#include <thread>
#include <mutex>
#include <functional>

template <class T> class TNTree {
private:
	recursive_mutex tree_mutex;
	shared_ptr<TNode <T>> root;
	future<void> sort_bg();
public:
	TNTree();
	TNTree(shared_ptr<TNTree<T>> &orig);
	shared_ptr<TNode <T>> Search(shared_ptr<T> sh);
	shared_ptr<TNode <T>> Search_Path(char *path);
	void Insert(shared_ptr<T> sh, char *path, char *who);
	void Delete(char *path);
	void Print(char *path);
	shared_ptr<TNode<T>> Minimum();
	shared_ptr<TNode<T>> Maximum();
	TIterator<TNode<T>, T> begin();
	TIterator<TNode<T>, T> end();

	size_t Size();

	shared_ptr<T> operator [] (size_t i);
	void sort();
	void parallel_sort();

	virtual ~TNTree();
};

#endif
