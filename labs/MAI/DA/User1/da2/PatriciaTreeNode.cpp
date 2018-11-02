#include <cstring>
#include <cstdlib>
#include "PatriciaTreeNode.h"

TPatriciaTreeNode::TPatriciaTreeNode() {
    Initialize(nullptr, 0, -1, this, this); //MAY BE SET 'NULL' TO DATA
}

TPatriciaTreeNode::TPatriciaTreeNode(char* key, unsigned long long data, int bitIndex, TPatriciaTreeNode* left, TPatriciaTreeNode* right) {
    Initialize(key, data, bitIndex, left, right); //MAY BE SET '0' TO DARA
}

void TPatriciaTreeNode::Initialize(char* k, unsigned long long d, int bi, TPatriciaTreeNode* l, TPatriciaTreeNode* r) {
    if (k)
        this->key = (char*)strdup(k); //AM I ALLOWED TO USE 'strdup'?
    else
        this->key = k;

    this->data = d;
    this->bitIndex = bi;
    this->left = l;
    this->right = r;
}

unsigned long long TPatriciaTreeNode::GetData() {
    return this->data;
}

bool TPatriciaTreeNode::SetData(unsigned long long d) {
    memcpy(&data, &d, sizeof(unsigned long long)); //AM I ALLOWED TO USE 'memcpy'
    //this->data = d;
    return true; //CHECK
}

char* TPatriciaTreeNode::GetKey() {
    return this->key;
}

TPatriciaTreeNode* TPatriciaTreeNode::GetLeft() {
    return this->left;
}

TPatriciaTreeNode* TPatriciaTreeNode::GetRight() {
    return this->right;
}

TPatriciaTreeNode::~TPatriciaTreeNode() {
    if (this->key) {
        free(key);
        key = nullptr;
    }
}