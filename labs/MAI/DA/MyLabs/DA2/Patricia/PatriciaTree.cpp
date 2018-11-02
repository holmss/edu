//
// Created by Maxim Spiridonov on 21.10.17.
//

#include "PatriciaTree.h"

unsigned int Length (const char *string) {
    unsigned int length = 0;

    while ((string + length != nullptr) && string[length] != '\0') {
        ++length;
    }
    return length;
}

int Prefix (const char *lfs, unsigned int lfsLen, const char *rhs, unsigned int rhsLen) {
    int prefix = 0;

    while (prefix != lfsLen && prefix != rhsLen && lfs[prefix] == rhs[prefix]) {
        ++prefix;
    }
    return prefix;
}

void CopyStr (char *dst, const char *src, unsigned int len) {
    for (int i = 0; i < len; ++i) {
        dst[i] = src[i];
    }
}

TPatriciaTree::TPatriciaTree () {
    next = nullptr;
    link = nullptr;
    key = nullptr;
    length = 0;
    data = 0;
}

const unsigned long long *TPatriciaTree::Search (const char *t, unsigned int len) {
    TPatriciaTree *node = this;
    int prefix;
    ++len;
    while (node != nullptr) {
        prefix = Prefix(node->key, node->length, t, len);

        if (prefix == 0) {
            node = node->next;
        } else if (prefix == len) {
            return &(node->data);
        } else if (prefix == node->length) {
            node = node->link;
        } else {
            node = nullptr;
        }

        t += prefix;
        len -= prefix;
    }
    return nullptr;
}

bool TPatriciaTree::Insert (const char *t, unsigned int len, unsigned long long num) {
    TPatriciaTree *node = this;
    TPatriciaTree *parent = nullptr;
    int prefix;
    bool sonsBrother = false;
    ++len;
    if (node->length == 0) {
        node->key = new char[len];
        CopyStr(node->key, t, len);
        node->length = len;
        node->data = num;
        return true;
    }

    while (true) {
        if (len == 0) {
            ++len;
        }
        if (node == nullptr) {
            node = new TPatriciaTree;
            node->key = new char[len];
            CopyStr(node->key, t, len);
            node->length = len;
            node->data = num;

            if (parent != nullptr) {
                if (sonsBrother) {
                    parent->next = node;
                } else {
                    node->next = parent->link;
                    parent->link = node;
                }
            }
            break;
        }

        prefix = Prefix(node->key, node->length, t, len);

        if (prefix == 0) {
            sonsBrother = true;
            parent = node;
            node = node->next;
        } else if (prefix < len) {
            if (prefix < node->length) {
                TPatriciaTree *newNode = new TPatriciaTree;
                newNode->key = new char[node->length - prefix];
                CopyStr(newNode->key, node->key + prefix, node->length - prefix);
                newNode->length = node->length - prefix;
                newNode->data = node->data;
                newNode->link = node->link;
                node->link = newNode;
                char *buf = new char[prefix];
                CopyStr(buf, node->key, prefix);
                delete node->key;
                node->key = buf;
                node->length = prefix;
            }
            sonsBrother = 0;
            parent = node;
            node = node->link;
            t += prefix;
            len -= prefix;
        } else {
            return false;
        }
    }
    return true;
}

bool TPatriciaTree::Remove (const char *t, unsigned int len) {
    TPatriciaTree *node = this;
    TPatriciaTree *parent = nullptr;
    TPatriciaTree *brother = nullptr;
    int prefix;
    ++len;
    while (true) {
        if (len == 0) {
            ++len;
        }
        if (node == nullptr) {
            return false;
        }
        prefix = Prefix(node->key, node->length, t, len);
        if (prefix == len) {
            TPatriciaTree *temp = node->next;

            if (parent != nullptr) {
                if (temp == nullptr) {
                    if (brother != nullptr && parent->link == brother) {
                        //merge parent & brother
                        char *buf = new char[parent->length + brother->length];

                        CopyStr(buf, parent->key, parent->length);
                        CopyStr(buf + parent->length, brother->key, brother->length);

                        delete parent->key;

                        parent->key = buf;
                        parent->length += brother->length;
                        parent->data = brother->data;
                        parent->link = brother->link;

                        brother->next = nullptr;
                        brother->link = nullptr;
                        delete brother;
                    } else {
                        brother->next = nullptr;
                    }
                } else {
                    if (brother == nullptr && temp->next == nullptr && parent->link == node) {
                        //merge parent & temp
                        char *buf = new char[parent->length + temp->length];
                        CopyStr(buf, parent->key, parent->length);
                        CopyStr(buf + parent->length, temp->key, temp->length);
                        delete parent->key;
                        parent->key = buf;
                        parent->length += temp->length;
                        parent->link = temp->link;
                        parent->data = temp->data;
                        temp->next = nullptr;
                        temp->link = nullptr;
                        delete temp;
                    } else if (brother == nullptr && temp->next != nullptr && parent->link == node) {
                        parent->link = temp;
                    } else if (brother != nullptr) {
                        brother->next = temp;
                    }
                }
                node->next = nullptr;
                node->link = nullptr;
                delete node;
                break;
            } else {
                if (brother == nullptr) {
                    if (node->next == nullptr) {
                        delete node->key;
                        node->length = 0;
                        node->key = nullptr;
                        node->data = 0;
                    } else {
                        delete node->key;
                        brother = node->next;
                        node->key = new char[brother->length];
                        CopyStr(node->key, brother->key, brother->length);
                        node->length = brother->length;
                        node->data = brother->data;
                        node->next = brother->next;
                        node->link = brother->link;
                        brother->next = nullptr;
                        brother->link = nullptr;
                        delete brother;
                    }
                } else {
                    brother->next = temp;
                    node->next = nullptr;
                    node->link = nullptr;
                    delete node;
                }
            }
            break;
        } else if (prefix == 0) {
            brother = node;
            node = node->next;
        } else if (prefix == node->length) {
            parent = node;
            node = node->link;
            brother = nullptr;

            t += prefix;
            len -= prefix;
        } else {
            return false;
        }
    }
    return true;
}

void TPatriciaTree::Save (const char *path) {
    const int size = 257;
    char *key = new char[size];
    int len = 0;
    TStack <const TPatriciaTree *> *s = new TStack <const TPatriciaTree *>;
    const TPatriciaTree *node = this;
    const TPatriciaTree *last = nullptr;
    std::ofstream file(path, std::ofstream::binary);

    if (!file) {
        std::cout << "ERROR: couldn't create file!\n";
        return;
    }

    s->Push(node);

    while (s->Empty() == 0) {
        if (node->link != nullptr && last != node->link && last != node->next) {
            CopyStr(key + len, node->key, node->length);
            len += node->length;
            key[len] = '\0';

            s->Push(node);
            node = node->link;
        } else {
            if (last != node->link || node->link == nullptr) {
                CopyStr(key + len, node->key, node->length);
                len += node->length;
                key[len] = '\0';
            }

            if (last == nullptr || (last != node->next && last != node->link)) {
                file << key << " " << node->data << std::endl;
            }

            if (node->next != nullptr && (last == nullptr || last != node->next)) {
                len -= node->length;
                s->Push(node);
                node = node->next;

                continue;
            }


            last = node;
            len -= node->length;
            key[len] = '\0';
            node = *(s->Top());
            s->Pop();
        }
    }

    std::cout << "OK\n";

    file.close();
    delete s;
    delete[] key;
}

void TPatriciaTree::Load (const char *path) {
    unsigned long long data;
    std::ifstream file(path, std::ifstream::binary);
    char *key = new char[257];
    unsigned int len = 0;

    while (file >> key >> data) {
        len = Length(key);

        this->Insert(key, len, data);
    }

    std::cout << "OK\n";

    delete[] key;
}

TPatriciaTree::~TPatriciaTree () {
    delete key;
    delete next;
    delete link;

    length = 0;
    data = 0;
}