#include "Tree.hpp"

template <class T>
Tree<T>::Tree()
    : root(new TTree<T>())
{
}

template <class T>
Tree<T>::~Tree() {}

template <class T>
std::ostream& operator<<(std::ostream& os, const Tree<T>& node)
{
    os << *node.root;
    return os;
}

template <class T>
std::shared_ptr<T> Tree<T>::getItem(char* path)
{
    return root->getValue(path, root);
}

template <class T>
TIterator<TTree<T>, T> Tree<T>::begin()
{
    return TIterator<TTree<T>, T>(root);
}

template <class T>
TIterator<TTree<T>, T> Tree<T>::end()
{
    return TIterator<TTree<T>, T>();
}

// template <class T>
// template <class T>Tree Tree<T>::get(char *path)
// {
//     return root->getItem(path, root);
// }

template <class T>
void Tree<T>::Remove(char* path)
{

    int i = 0, it = 0;
    char tm;
    while (path[i] != '\0') {
        if (path[i] == 'r' || path[i] == 'l') {
            it = i;
        }
        i++;
    }
    tm = path[it];
    path[it] = '\0';
    pTree prev = root->getItem(path, root);
    path[it] = tm;
    if (!root->left && !root->right)
        root->value = nullptr;

    root->Remove(root->getItem(path, root), prev);
}

template <class T>
void Tree<T>::add(T* triangle)
{
    root->add(triangle);
}

template <class T>
bool Tree<T>::empty()
{
    return root->empty();
}

template class Tree<Figure>;
template std::ostream& operator<<(std::ostream& os, const Tree<Figure>& node);