#include <cstdlib>
#include "PatriciaTree.h"
#include "PatriciaTreeNode.h"

#define ZEROTAB_SIZE 256

TPatriciaTree::TPatriciaTree() {
    this->head = new TPatriciaTreeNode();
    this->head->key = (char*)calloc(ZEROTAB_SIZE, 1);
}

TPatriciaTreeNode *TPatriciaTree::Insert (char *key, unsigned long long data) {
    TPatriciaTreeNode *node, *nodeComp, *x;

    node = this->head;
    nodeComp = (TPatriciaTreeNode*)(node->right);

    while (node->bitIndex < nodeComp->bitIndex) {
        node = nodeComp;
        nodeComp = (TPatriciaTreeNode*)(GetBit(key, nodeComp->bitIndex) ? nodeComp->right : nodeComp->left);
    }

    if (KeysCompare(key, nodeComp->key)) //CHECK IF KEY IS ALREADY IN THE TREE
        return nullptr; //ALREADY IN THE TREE

    int diffBit = FirstDiffBit(key, nodeComp->key);

    node = this->head;
    x = (TPatriciaTreeNode*)(node->right);
    while ((node->bitIndex < x->bitIndex) && (x->bitIndex < diffBit)) {
        node = x;
        x = (TPatriciaTreeNode*)(GetBit(key, x->bitIndex) ? x->right : x->left);
    }

    nodeComp = new TPatriciaTreeNode();
    nodeComp->Initialize(key, data, diffBit, (GetBit(key, diffBit) ? x : nodeComp), (GetBit(key, diffBit) ? nodeComp : x));

    if (GetBit(key, node->bitIndex))
        node->right = nodeComp;
    else
        node->left = nodeComp;

    return node;
}

unsigned long long TPatriciaTree::LookUp(char* k) {
    TPatriciaTreeNode* node = LookUpNode(k);

    if (!node)
        return 0; //MAY BE I SHOULD USE 'NULL' INSTEAD OF '0'

    return node->data;
}

TPatriciaTreeNode* TPatriciaTree::LookUpNode(char* k) {
    TPatriciaTreeNode* p;
    TPatriciaTreeNode* x;

    p = this->head;
    x = (TPatriciaTreeNode*)(this->head->right);

    while (p->bitIndex < x->bitIndex) {
        p = x;
        x = (TPatriciaTreeNode*)(GetBit(k, x->bitIndex) ? x->right : x->left);
    }

    if (!KeysCompare(k, x->key))
        return nullptr;

    return x;
}

bool TPatriciaTree::Delete(char* k) {
    TPatriciaTreeNode *p, *t, *x, *pp, *lp;
    int bp, bl, br;
    char* key = nullptr;

    //START AT ROOT
    p = head;
    t = (TPatriciaTreeNode*)(p->right);

    //GO DOWN THE TREE AND LOOK FOR KEY
    while (p->bitIndex < t->bitIndex) {
        pp = p;
        p = t;
        t = (TPatriciaTreeNode*)(GetBit(k, t->bitIndex) ? t->right : t->left);
    }

    //EXIT IF KEY ISN'T IN THE TREE
    if (!KeysCompare(k, t->key))
        return false; //THE KEY ISN'T IN THE TREE

    //COPY p's KEY TO t
    if (t != p)
        KeyCopy(p, t);

    //CHECK IF p IS A LEAF
    bp = p->bitIndex;
    bl = ((TPatriciaTreeNode*)(p->left))->bitIndex;
    br = ((TPatriciaTreeNode*)(p->right))->bitIndex;

    if ((bl > bp) || (br > bp)) {
        if (p != t) {
            //LOOK FOR A NEW (INTERMEDIATE) KEY //??
            key = strdup(p->key);

            lp = p;
            x = (TPatriciaTreeNode*)(GetBit(key, p->bitIndex) ? p->right : p->left);

            while (lp->bitIndex < x->bitIndex) {
                lp = x;
                x = (TPatriciaTreeNode*)(GetBit(key, x->bitIndex) ? x->right : x->left);
            }

            //FALSE IF THE INTERMEDIATE KEY WAS NOT FOUND
            if (!KeysCompare(key, x->key)) {
                free(key);
                return false; //THE KEY COULD NOT BE FOUND
            }

            //REWIRE THE LEAF(lp) TO POINT TO t
            if (GetBit(key, lp->bitIndex))
                lp->right = t;
            else
                lp->left = t;
        }

        //REWIRE THE PARENT TO POINT TO THE REAL CHILD OF p
        if (pp != p) {
            TPatriciaTreeNode* ch = (TPatriciaTreeNode*)(GetBit(k, p->bitIndex) ? p->left : p->right);

            if (GetBit(k, pp->bitIndex))
                pp->right = ch;
            else
                pp->left = ch;
        }
        
        //WE NO LONGER NEED 'key'
        free(key);
        key = nullptr;
    }
    else {
        //SITUATION WHEN BOTH EDGES(LEFT, RIGHT) ARE POINTING UPWARDS OR TO THE NODE(SELF-EDGES)
        
        //REWIRE THE PARENT
        if (pp != p) {
            TPatriciaTreeNode* blx = (TPatriciaTreeNode*)(p->left);
            TPatriciaTreeNode* brx = (TPatriciaTreeNode*)(p->right);

            if (GetBit(k, pp->bitIndex))
                pp->right = (((blx == brx) && (blx == p)) ? pp : ((blx == p) ? brx : blx));
            else
                pp->left  = (((blx == brx) && (blx == p)) ? pp : ((blx == p) ? brx : blx));
        }
    }

    delete p;
    
    return true; //SUCCESSFULLY DELETED
}

void TPatriciaTree::RecursiveRemove(TPatriciaTreeNode* root) {
    TPatriciaTreeNode* l = (TPatriciaTreeNode*)root->left;
    TPatriciaTreeNode* r = (TPatriciaTreeNode*)root->right;

    //REMOVE LEFT BRANCH
    if ((l->bitIndex >= root ->bitIndex) && (l != root) && (l != head))
        RecursiveRemove(l);

    //REMOVE RIGHT BRANCH
    if ((r->bitIndex >= root ->bitIndex) && (r != root) && (r != head))
    RecursiveRemove(r);

    //REMOVE THE ROOT
    delete root;
}

int TPatriciaTree::GetBit(char* bitStream, int n) {
    if (n < 0)
        return 2; //PSEUDO-BIT WITH A VALUE OF 2
    
    int k = (n & 0x7); //HOW IT WORKS?
    return ((*(bitStream + (n >> 3))) >> k) & 0x1;
}

bool TPatriciaTree::KeysCompare(char* k1, char* k2) {
    if (!k1 || !k2)
        return false;
    
    return (strcmp((char*)k1, (char*)k2)) == 0; 
}

int TPatriciaTree::FirstDiffBit(char* k1, char* k2) {
    if (!k1 || !k2)
        return 0; //FIRST BIT IS DIFFERENT
    
    int n = 0;
    int d = 0;

    while (((k1[n]) == k2[n]) && (k1[n] != 0) && (k2[n] != 0))
        n++;
    while (GetBit(&k1[n], d) == GetBit(&k2[n], d))
        d++;
    return ((n << 3) + d);
}

void TPatriciaTree::KeyCopy(TPatriciaTreeNode* src, TPatriciaTreeNode* dest) {
    if (src == dest)
        return;
    
    //COPY THE KEY FROM src TO dest
    if (strlen(dest->key) < strlen(src->key))
        dest->key = (char*)realloc(dest->key, 1 + strlen(src->key));
    strcpy(dest->key, src->key);

    //COPY THE DATA FROM src TO dest
    dest->data = src->data;

    //SHOULD I COPY THE BIT INDEX?
	//dest->bit_index = src->bit_index;
}

TPatriciaTree::~TPatriciaTree() {
    RecursiveRemove(this->head);
}
