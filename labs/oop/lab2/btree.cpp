#include "btree.hpp"

TTree::TTree() : value(), left(nullptr), right(nullptr), prev(nullptr) {}

TTree::TTree(const TTree &orig)
{
    value = orig.value;
    left = orig.left;
    right = orig.right;
    prev = orig.prev;
}

int TTree::height() const
{
    if (!prev)
        return 0;
    return 1 + prev->height();
}

bool TTree::empty()
{
    return value == Pentagon();
}

std::ostream &operator<<(std::ostream &os, const TTree &Tree)
{
    Pentagon help = Pentagon();
    int height = Tree.height();

    if (Tree.right)
        os << *Tree.right;

    if (Tree.value != help)
    {
        for (int i = 0; i < height; i++)
            os << "\t\t";

        os << Tree.value;

        os << std::endl;

    }

    if (Tree.left)
        os << *Tree.left;

    return os;
}

void TTree::add(Pentagon pentagon)
{
    if (empty())
    {
        value = pentagon;
        return;
    }
    if (pentagon.Square() == 0)
    {
        return;
    }
    if (pentagon.Square() >= value.Square()) // сбалансированное дерево
    {
        if (!right)
        {
            right = new TTree();
            right->value = pentagon;
            right->prev = this;
        }
        else
            right->add(pentagon);
    }
    else
    {
        if (!left)
        {
            left = new TTree();
            left->value = pentagon;
            left->prev = this;
        }
        else
            left->add(pentagon);
    }
}

TTree *TTree::get(char *path)
{
    if (*path == 'l')
    {
        if (left)
            return left->get(path + 1);
    }
    else if (*path == 'r')
    {
        if (right)
            return right->get(path + 1);
    }
    else if (*path != '\0')
    {
        return get(path + 1);
    }
    return this;
}

Pentagon TTree::getItem()
{
    return value;
}

Pentagon TTree::getItem(char *path)
{
    return get(path)->value;
}

void TTree::Remove(TTree *node)
{
    if (!node->prev)
    {
        if (node->right)
        {
            std::swap(node->value, node->right->value);
            node = node->right;
        }
        else if (node->left)
        {
            std::swap(node->value, node->left->value);
            node = node->left;
        }
        else
        {
            node->value = Pentagon();
            return;
        }
    }
    if (node->right && !node->left)
    {
        if (node->prev->right == node)
        {
            node->prev->right = node->right;
            node->right->prev = node->prev;
        }
        else if (node->prev->left == node)
        {
            node->prev->left = node->right;
            node->right->prev = node->prev;
        }
    }
    else if (node->left && !node->right)
    {
        if (node->prev->right == node)
        {
            node->prev->right = node->left;
            node->left->prev = node->prev;
        }
        else if (node->prev->left == node)
        {
            node->prev->left = node->left;
            node->left->prev = node->prev;
        }
    }
    else if (!node->right && !node->left)
    {
        if (node->prev->right == node)
            node->prev->right = nullptr;
        else if (node->prev->left == node)
            node->prev->left = nullptr;
    }
    else
    {
        TTree *help = node->right;

        while (help->left)
        {
            help = help->left;
        }
        std::swap(node->value, help->value);
        Remove(help);
        return;
    }
    node->left = node->right = node->prev = nullptr;
    delete node;
}


TTree::~TTree()
{
    if (right)
        delete right;

    if (left)
        delete left;
}
