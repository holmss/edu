#include "BRTree.h"
#include <iostream>
//
//bool GreaterThan(char *first, char *second) {
//    bool result = false;
//    int temp = strcmp(first, second);
//    if (temp > 0) {
//        result = true;
//    }
//    return result;
//}


TRBNode::TRBNode() {

    //key = new char[1];
    //key[1] = '\0';
    // key[0] = '-';
    key = nullptr;
    value = 0;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    colour = RED;

}

TRBNode::TRBNode(const char *k, const uint64_t val) { // не нравится
    //delete[] key;
    //int ;
    key = new char[strlen(k) + 1];
    strcpy(this->key, k);
    value = val;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    colour = RED;
}

TRBTree::TRBTree() {
    this->nil = new TRBNode();
    nil->colour = BLACK;
    //char *tmp = new char[4];
    //strcpy(tmp, "nil");
    //nil->key = tmp;
    nil->left = nil;
    nil->right = nil;
    nil->parent = nil;
    //nil->key = "";
    root = nil;
}

bool TRBTree::RBInsert(const char *key, unsigned long long value) {
    TRBNode *newNode = new TRBNode(key, value);
    newNode->left = nil;
    newNode->right = nil;
    newNode->parent = nil;


    TRBNode *y = nil;
    TRBNode *x = this->root;
    while (x != nil) {
        // if tree isnt empty, go low
        y = x;
        if (strcmp(x->key, newNode->key) > 0) {
            //(z->key < x->key) {
            x = x->left;
        } else if (strcmp(x->key, newNode->key) == 0) {
            newNode->left = nullptr;
            newNode->right = nullptr;
            newNode->parent = nullptr;
            delete[] newNode->key;
            delete newNode;

            return false;
        } else {
            x = x->right;
        }
    }

    newNode->parent = y;
    if (y == nil) {
        // parent is empty->node is root
        this->root = newNode;
        //	root->colour = BLACK;
        //root->left = nil;
        //root->right = nil;

    } else if (strcmp(y->key, newNode->key) > 0) {
        //(z->key < y->key) {
        y->left = newNode;
    } else {
        y->right = newNode;
    }
    newNode->left = nil;
    newNode->right = nil;
    newNode->colour = RED;//
    RBInsertFixup(newNode);
    //newNode= nullptr;
    return true;
}


void TRBTree::RBInsertFixup(TRBNode *z) {
    TRBNode *y;
    //y = nil;//for uncle
    while (z->parent->colour == RED && z->parent != nil) {
        // parent is red
        if (z->parent == z->parent->parent->left) {
            //parent is left son
            y = z->parent->parent->right;
            if (y->colour == RED) {
                // uncle is red CASE 1
                z->parent->colour = BLACK;
                y->colour = BLACK;
                z->parent->parent->colour = RED;
                z = z->parent->parent;// go up
            } else {
                if (z == z->parent->right) {
                    // element is right son
                    z = z->parent;
                    LeftRotate(z);
                }
                z->parent->colour = BLACK;
                z->parent->parent->colour = RED;
                RightRotate(z->parent->parent);
            }
        } else {
            // exact the same with another uncle
            if (z->parent == z->parent->parent->right) {
                //parent is right son
                y = z->parent->parent->left;
                if (y->colour == RED) {
                    // uncle is red CASE 1
                    z->parent->colour = BLACK;
                    y->colour = BLACK;
                    z->parent->parent->colour = RED;
                    z = z->parent->parent;// go up
                } else {
                    if (z == z->parent->left) {
                        // element is left son
                        z = z->parent;
                        RightRotate(z);
                    }
                    z->parent->colour = BLACK;
                    z->parent->parent->colour = RED;
                    LeftRotate(z->parent->parent);
                }
            }

        }
    }
    root->colour = BLACK;
    //delete y;
}

void TRBTree::LeftRotate(TRBNode *x) {
    TRBNode *y = x->right; // y state
    x->right = y->left; // trees change
    if (y->left != nil) {
        // conect with parent
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nil) {
        // 1 case x was root
        root = y;
    } else if (x == x->parent->left) {
        // 2 case x was left son
        x->parent->left = y;
    } else {
        // 3 case x was right son
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
    //delete y;
}

void TRBTree::RightRotate(TRBNode *x) {
    TRBNode *y = x->left;
    x->left = y->right;
    if (y->right != nil) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nil) {
        root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }

    y->right = x;
    x->parent = y;
    //delete y;
}

TRBNode *TRBTree::Search(char *key) {

    TRBNode *x = root;//this
    while (x != nil) {
        // if tree isnt empty, go low
        if (strcmp(x->key, key) != 0) {
            if (strcmp(x->key, key) > 0) {
                //z->key < x->key) {
                x = x->left;
            } else {
                x = x->right;
            }
        } else {
            break;
        }
    }

    return x;
}


TRBNode *TRBTree::Minimum(TRBNode *x) const {
    while (x->left != nil) {
        x = x->left;
    }
    return x;
}


void TRBTree::RBTransplant(TRBNode *u, TRBNode *v) {
    //replace u with v
    if (u->parent == nil) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }

    v->parent = u->parent;
}

void TRBTree::RBDelete(TRBNode *z) {
    TRBNode *y = z;
    TRBNode *x;
    char yOrigColour = y->colour;// dont change bh or change
    if (z->left == nil) {
        // no left tree/ case 1
        x = z->right;
        RBTransplant(z, z->right);
    } else if (z->right == nil) {
        // no right tree/ case 2
        x = z->left;
        RBTransplant(z, z->left);
    } else {
        // right tree + left tree
        y = Minimum(z->right);
        yOrigColour = y->colour; // cause delete y
        x = y->right;
        if (y->parent == z) {
            //case 3
            x->parent = y;
        } else {
            //case 4
            RBTransplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        RBTransplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->colour = z->colour;
    }

    if (yOrigColour == BLACK) {
        RBDeleteFixup(x);
    }
}

void TRBTree::RBDeleteFixup(TRBNode *x) {
    while(x != this->root && x->colour == BLACK) {
        if(x == x->parent->left) {
            TRBNode* bro = x->parent->right;
            if(bro->colour == RED) {
                bro->colour = BLACK;
                x->parent->colour = RED;
                LeftRotate((x->parent));
                bro = x->parent->right;
            }
            if(bro->left->colour == BLACK && bro->right->colour == BLACK) {
                bro->colour = RED;
                x = x->parent;
            } else {
                if(bro->right->colour == BLACK) {
                    bro->left->colour = BLACK;
                    bro->colour = RED;
                    RightRotate(bro);
                    bro = x->parent->right;
                }
                bro->colour = x->parent->colour;
                x->parent->colour = BLACK;
                bro->right->colour = BLACK;
                LeftRotate((x->parent));
                x = this->root;
            }
        } else {
            TRBNode* bro = x->parent->left;
            if(bro->colour == RED) {
                bro->colour = BLACK;
                x->parent->colour = RED;
                RightRotate((x->parent));
                bro = x->parent->left;
            }
            if(bro->right->colour == BLACK && bro->left->colour == BLACK) {
                bro->colour = RED;
                x = x->parent;
            } else {
                if(bro->left->colour == BLACK) {
                    bro->right->colour = BLACK;
                    bro->colour = RED;
                    LeftRotate(bro);
                    bro = x->parent->left;
                }
                bro->colour = x->parent->colour;
                x->parent->colour = BLACK;
                bro->left->colour = BLACK;
                RightRotate((x->parent));
                x = this->root;
            }
        }
    }
    x->colour = BLACK;
}

void TRBTree::Serialize(TRBNode *node, std::ofstream &fp) {
    if (node == nil) {
        fp << MARKER << " ";
        return;
    }
    fp << node->colour << " " << node->key << " " << node->value << " ";
    Serialize(node->left, fp);
    Serialize(node->right, fp);
}

void TRBTree::DeSerialize(TRBNode *parNode, TRBNode *&node, std::ifstream &file, char *temp)//*& change value of ptr
{
    char colour;
    uint64_t val = 0;

    file >> colour;

    if ((colour == MARKER || (colour != BLACK && colour != RED)) || colour == EOF) {
        return;
    }

    file >> temp >> val;


    node = new TRBNode(temp, val);/////////////////////////////////////////////////////////////////////////
    node->left = nil;
    node->right = nil;
    node->parent = parNode;
    node->colour = colour;

    DeSerialize(node, node->left, file, temp);
    DeSerialize(node, node->right, file, temp);
}

TRBNode::~TRBNode() {
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    key = nullptr;
}

void TRBTree::DistructTree(TRBNode *node) {
    if (node->right != nullptr && node->right != nil) {
        DistructTree(node->right);
    }
    if (node->left != nullptr && node->left != nil) {
        DistructTree(node->left);
    }
    delete [] (node->key);
    delete node;
}

TRBTree::~TRBTree() {
    if (this->root != this->nil) {
        DistructTree(this->root);
    }
    delete nil;
}
