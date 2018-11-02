#include "ntree_2.h"

template <class TT> NTree_2<TT>::NTree_2()
{
	this->root = nullptr;
}
template <class TT> shared_ptr<TNode_2<TT>> NTree_2<TT>::Search_2(char *path)
{
	shared_ptr<TNode_2<TT>> NodePath = nullptr;
	shared_ptr<TNode_2<TT>> prev = nullptr;
	while (*path != '\0') {
		if (*path == 'r') {
			NodePath = this->root;
			prev = nullptr;
			path++;
			continue;
		}
		if (*path == 's') {
			prev = NodePath;
			NodePath = NodePath->Son();
			path++;
			continue;
		}
		if (*path == 'b') {
			prev = NodePath;
			NodePath = NodePath->Brother();
			path++;
			continue;
		}
	}
	return NodePath;
}
template <class TT> void NTree_2<TT>::deleterec(shared_ptr<TNode_2<TT>> node)
{
	if (node->Brother() != nullptr) {
		deleterec(node->Brother());
	}
	if (node->Son() != nullptr) {
		deleterec(node->Son());
	}
	node = nullptr;
}
template <class TT> void NTree_2<TT>::Insert_2(shared_ptr<TT> value, char *path, char *who)
{
	shared_ptr<TNode_2<TT>> nd(new TNode_2<TT>(value));
	if ((this->root == nullptr)) {
		this->root = nd;
	}
	else {
		shared_ptr<TNode_2<TT>> Nodepath = Search_2(path);
		if (*who == 's') {
			Nodepath->SetSon(nd);
			nd->SetParent(Nodepath);
		}
		if (*who == 'b') {
			if (Nodepath == root) {
				cout << "ROOT CAN'T HAVE BROTHERS" << endl;
			}
			else {
				Nodepath->SetBrother(nd);
				nd->SetParent(Nodepath->Parent());
			}
		}
	}
}

template <class TT> void NTree_2<TT>::Delete(char *path)
{
	shared_ptr<TNode_2<TT>> deleting = this->Search_2(path);
	deleterec(deleting);
}
template <class TT> shared_ptr<TNode_2<TT>> NTree_2<TT>::Minimum() const
{
	shared_ptr<TNode_2<TT>> node = this->root;
	while (node->Son()) {
		node = node->Son();
	}
	return node;
}
template <class TT> shared_ptr<TNode_2<TT>> NTree_2<TT>::Maximum() const
{
	return this->root;
}
template <class TT> TIterator<TNode_2<TT>, TT> NTree_2<TT>::begin() const
{
	return TIterator<TNode_2<TT>, TT>(this->Minimum());
}
template <class TT> TIterator<TNode_2<TT>, TT> NTree_2<TT>::end() const
{
	return TIterator<TNode_2<TT>, TT>(this->Maximum());
}
template <class TT> NTree_2<TT>::~NTree_2()
{
	if (this->root) {
		deleterec(this->root);
	}
	this->root = nullptr;
}


#include "ntree.h"
template class NTree_2<TNTree<TShape>>;
#include <functional>
template class TNode_2<function<void(void)>>;
template class NTree_2<function<void(void)>>;