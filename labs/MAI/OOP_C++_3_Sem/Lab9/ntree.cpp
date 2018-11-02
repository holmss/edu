#include "ntree.h"
#include <exception>
using namespace std;

template <class T> TNTree<T>::TNTree()
{
	this->root = nullptr;
}
template <class T> TNTree<T>::TNTree(shared_ptr<TNTree<T>> &orig)
{
	this->root = orig->root;
}
template <class T> shared_ptr<TNode<T>> TNTree<T>::Search(shared_ptr<T> sh)
{
	lock_guard<recursive_mutex> lock(this->tree_mutex);
	if (root->GetShape() == sh) {
		return root;
	}
	else {
		return root->search_rec(sh);
	}
}
template <class T> shared_ptr<TNode<T>> TNTree<T>::Search_Path(char *path)
{
	lock_guard<recursive_mutex> lock(this->tree_mutex);
	shared_ptr<TNode<T>> NodePath = nullptr;
	shared_ptr<TNode<T>> prev = nullptr;
	while (*path != '\0') {
		if (*path == 'r') {
			NodePath = this->root;
			prev = nullptr;
			path++;
			continue;
		}
		if (*path == 's') {
			prev = NodePath;
			if (NodePath->Son()) {
				NodePath = NodePath->Son();
			}
			else return nullptr;
			path++;
			continue;
		}
		if (*path == 'b') {
			prev = NodePath;
			if (NodePath->Brother()) {
				NodePath = NodePath->Brother();
			}
			else return nullptr;
			path++;
			continue;
		}
	}
	return NodePath;
}
template <class T> void TNTree<T>::Insert(shared_ptr<T> sh, char *path, char *who)
{
	lock_guard<recursive_mutex> lock(this->tree_mutex);
	shared_ptr<TNode<T>> nd (new TNode<T>(&(this->tree_mutex), sh));
	if ((this->root == nullptr)) {
		this->root = nd;
	}
	else {
		shared_ptr<TNode<T>> Nodepath = Search_Path(path);
		if (*who == 's') {
			while (Nodepath->Son()) {
				Nodepath = Nodepath->Son();
			}
			Nodepath->SetSon(nd);
			nd->SetParent(Nodepath);
		}
		if (*who == 'b') {
			if (Nodepath == root) {
				cout << "ROOT CAN'T HAVE BROTHERS" << endl;
			}
			else {
				while (Nodepath->Brother()) {
					Nodepath = Nodepath->Brother();
				}
				Nodepath->SetBrother(nd);
				nd->SetParent(Nodepath->Parent());
			}
		}
	}
}
template <class T> void TNTree<T>::Delete(char *path)
{
	lock_guard<recursive_mutex> lock(this->tree_mutex);
	shared_ptr<TNode<T>> removednode = this->Search_Path(path);
	if (removednode == nullptr) {
		cout << "DIRECTORY IS NULLPTR" << endl;
		return;
	}
	shared_ptr<TNode<T>> current = this->root;
	shared_ptr<TNode<T>> parent = nullptr;
	while (current->Son()) {
		parent = current;
		current = current->Son();
	}
	if (current != removednode) {
		removednode->SetShape(current->GetShape());
	}
	current->SetParent(nullptr);
	parent->SetSon(current->Brother());
	current = nullptr;
}
template <class T> void TNTree<T>::Print(char *path)
{
	lock_guard<recursive_mutex> lock(this->tree_mutex);
	shared_ptr<TNode<T>> Path = this->Search_Path(path);
	if (Path == nullptr) {
		cout << "DIRECTORY IS NULLPTR" << endl;
		return;
	}
	shared_ptr<T> shape = Path->GetShape();
	cout << "Tree:";
	while (*path) {
		cout << "/" << *path;
		path++;
	}
	cout << "  ";
	shape->Print();
}
template <class T> shared_ptr<TNode<T>> TNTree<T>::Minimum() //minimum is the deepest son
{
	lock_guard<recursive_mutex> lock(this->tree_mutex);
	shared_ptr<TNode<T>> node = this->root;
	while (node->Son()) {
		node = node->Son();
	}
	return node;
}
template <class T> shared_ptr<TNode<T>> TNTree<T>::Maximum() //maximum is the root
{
	lock_guard<recursive_mutex> lock(tree_mutex);
	return this->root;
}
template <class T> TIterator<TNode<T>, T> TNTree<T>::begin() //begin == minimum
{
	return TIterator<TNode<T>, T>(this->Minimum());
}
template <class T> TIterator<TNode<T>, T> TNTree<T>::end() // end is the maximum is the root
{
	return TIterator<TNode<T>, T>(this->Maximum());
}
template <class T> size_t TNTree<T>::Size()
{
	lock_guard<recursive_mutex> lock(this->tree_mutex);
	if (this->root == nullptr) {
		return 0;
	}
	size_t result = 0;
	TIterator<TNode<T>, T> it_loc = this->begin();
	TIterator<TNode<T>, T> end_loc = this->end();
	for (it_loc, end_loc; it_loc != end_loc; it_loc++) {
		result++;
	}
	result++;
	return result;
}
template <class T> future<void> TNTree<T>::sort_bg()
{
	packaged_task<void(void)> task(bind(mem_fn(&TNTree<T>::parallel_sort), this));
	future<void> res(task.get_future());
	thread th(move(task));
	th.detach();
	return res;
}
template <class T> shared_ptr<T> TNTree<T>::operator [] (size_t i)
{
	lock_guard<recursive_mutex> lock(this->tree_mutex);
	if (i < this->Size() - 1) {
		throw
			invalid_argument("index greater then tree size");
	}
	size_t j = 0;
	for (shared_ptr<T> a : *this) {
		if (j == i) {
			return a;
		}
		j++;
	}
	return shared_ptr<T>(nullptr);
}
template <class T> void TNTree<T>::sort()
{
	if (this->Size() > 1) {
		shared_ptr<T> middle = (this->Search_Path("r\0"))->GetShape();
		this->Delete("r\0");
		shared_ptr<TNTree<T>> left(new TNTree<TShape>);
		shared_ptr<TNTree<T>> right(new TNTree<TShape>);
		while (this->Size() > 0) {
			if ((this->Search_Path("r\0"))->GetShape() < middle) {
				left->Insert((this->Search_Path("r\0"))->GetShape(), "r\0", "s\0");
				this->Delete("r\0");
			}
			else {
				right->Insert((this->Search_Path("r\0"))->GetShape(), "r\0", "s\0");
				this->Delete("r\0");
			}
			left->sort();
			right->sort();
			while (left->Size() > 0) {
				this->Insert((left->Search_Path("r\0"))->GetShape(), "r\0", "s\0");
				left->Delete("r\0");
			}
			this->Insert(middle, "r\0", "s\0");
			while (right->Size() > 0) {
				this->Insert((right->Search_Path("r\0"))->GetShape(), "r\0", "s\0");
				right->Delete("r\0");
			}
		}
	}
	else return;
}
template <class T> void TNTree<T>::parallel_sort()
{
	if (this->Size() > 1) {
		shared_ptr<T> middle = (this->Search_Path("r\0"))->GetShape();
		this->Delete("r\0");
		shared_ptr<TNTree<T>> left (new TNTree<TShape>);
		shared_ptr<TNTree<T>> right(new TNTree<TShape>);
		while (this->Size() != 0) {
			shared_ptr<T> item = (this->Search_Path("r\0"))->GetShape();
			this->Delete("r\0");
			if (item < middle) {
				left->Insert(item, "r\0", "r\0");
			}
			else {
				right->Insert(item, "r\0", "r\0");
			}
			future<void> left_res = left->sort_bg();
			future<void> right_res = right->sort_bg();
			left_res.get();
			size_t l = left->Size();
			size_t r = right->Size();
			while (l > 0) {
				this->Insert((left->Search_Path("r\0"))->GetShape(), "r\0", "s\0");
				l--;
			}
			this->Insert(middle, "r\0", "s\0");
			right_res.get();
			while (r > 0) {
				this->Insert((right->Search_Path("r\0"))->GetShape(), "r\0", "s\0");
				r--;
			}
		}
	}
	else return;
}
template <class T> TNTree<T>::~TNTree()
{
	while (this->root != nullptr) {
		this->Delete("r\0");
	}
	this->root = nullptr;
}

#include "Shape.h"
template class TNTree<TShape>;