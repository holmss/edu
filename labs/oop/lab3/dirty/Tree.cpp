#include "Tree.hpp"

Tree::Tree() : root(new TTree()) {}
Tree::~Tree() {}

std::ostream &operator<<(std::ostream &os, const Tree &node)
{
    os << *node.root;
    return os;
}

pFigure Tree::getItem(char *path)
{
    return root->getValue(path, root);
}

pTree Tree::get(char *path)
{
    return root->getItem(path, root);
}
void Tree::Remove(char *path)
{

    int i = 0, it = 0;
    char tm;
    while (path[i] != '\0')
    {
    if (path[i] == 'r' || path[i] == 'l')
    {
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

void Tree::add(Figure *triangle)
{
    root->add(triangle);
}

bool Tree::empty()
{
    return root->empty();
}