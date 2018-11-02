//
// Created by Maxim Spiridonov on 21.10.17.
//

#include "PatriciaTree.h"

int Prefix (const TString &lfs, const TString &rfs) {
    int prefix = 0;

    while (prefix != lfs.Length() && prefix != rfs.Length() && lfs[prefix] == rfs[prefix]) {
        ++prefix;
    }
    return prefix;
}

TString &TPatriciaTree::CopyEndOfStr (const TString &str, int count) {
    TString *buf = new TString(str.Length() - count);
    for (int i = count; i <= str.Length(); ++i) {
        (*buf)[i - count] = str[i];
    }
    return *buf;
}

TString &TPatriciaTree::CopyStartOfStr (const TString &str, int count) {
    TString *buf = new TString(count);
    for (int i = 0; i < count; ++i) {
        (*buf)[i] = str[i];
    }
    return *buf;
}

TPatriciaTree::TPatriciaTree () {
    next = nullptr;
    link = nullptr;
    pair = TPair();
    //pair.Key = TString();
    //key = nullptr;
    //length = 0;
    //data = 0;
}

/*
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
*/
const unsigned long long *TPatriciaTree::Search (TPair &tmp) {
    TPatriciaTree *node = this;
    int prefix = 0;

    while (node != nullptr) {
        prefix = Prefix(tmp.Key, node->pair.Key);

        if (prefix == 0) {
            node = node->next;
        } else if (prefix == tmp.Key.Length()) {
            return &(node->pair.Value);
        } else if (prefix == node->pair.Key.Length()) {
            node = node->link;
        } else {
            node = nullptr;
        }

        tmp.Key = CopyEndOfStr(tmp.Key, prefix);
        //*(tmp.Key.GetInternal())+=prefix;
    }

    return nullptr;
}

bool TPatriciaTree::Insert (TPair &tmp) {
    TPatriciaTree *node = this;
    TPatriciaTree *parent = nullptr;
    int prefix;
    bool sonsBrother = false;

    if (node->pair.Key.Length() == 0) {
        node->pair = tmp;
        return true;
    }

    while (true) {
        if (node == nullptr) {
            node = new TPatriciaTree();

            node->pair = tmp;

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

        prefix = Prefix(node->pair.Key, tmp.Key);

        if (prefix == 0) {
            sonsBrother = true;
            parent = node;
            node = node->next;
        } else if (prefix < tmp.Key.Length()) {
            if (prefix < node->pair.Key.Length()) {
                TPatriciaTree *newNode = new TPatriciaTree();
                //std::cout << CopyEndOfStr(node->pair.Key, prefix) << std::endl;
                newNode->pair.Key = CopyEndOfStr(node->pair.Key, prefix);
                //newNode->pair.Key.GetInternal() = new char[node->pair.Key.Length()-prefix];
                //CopyStr(newNode->pair.Key.GetInternal(), (node->pair.Key.GetInternal())+prefix, node->pair.Key.Length()-prefix);

                newNode->pair.Value = node->pair.Value;

                newNode->link = node->link;
                node->link = newNode;

                node->pair.Key = CopyStartOfStr(node->pair.Key, prefix);
                //CopyStr(node->pair.Key.GetInternal(),node->pair.Key.GetInternal(),prefix);
                //std::cout << CopyStartOfStr(node->pair.Key, prefix-1) << std::endl;
            }

            sonsBrother = false;
            parent = node;
            node = node->link;

            tmp.Key = CopyEndOfStr(tmp.Key, prefix);
        } else {
            return false;
        }
    }
    return true;
}
/*
bool TPatriciaTree::Insert (TPair& tmp) {
    TPatriciaTree *node = this;
    TPatriciaTree *parent = nullptr;
    int prefix;
    bool sonsbrother = false;

    //++len;

    if (node->pair.Key.Length() == 0) {
        //node->key = new char[len];

        //CopyStr(node->key, t, len);
        //node->length = len;
        //node->data = num;
        node->pair = tmp;

        return true;
    }

    while (true) {

        if (node == nullptr) {
            node = new TPatriciaTree;

            node->pair = tmp;

            if (parent != nullptr) {
                if (sonsbrother) {
                    parent->next = node;
                } else {
                    node->next = parent->link;
                    parent->link = node;
                }
            }

            break;
        }

        prefix = Prefix(node->pair.Key, tmp.Key);

        if (prefix == 0) {
            sonsbrother = true;
            parent = node;
            node = node->next;
        } else if (prefix < tmp.Key.Length()) {
            if (prefix < node->pair.Key.Length()) {
                TPatriciaTree *newnode = new TPatriciaTree;

                //newnode->key = new char[node->length - prefix];

                //CopyStr(newnode->key, node->key + prefix, node->length - prefix);
                newnode->pair.Key = CopyEndOfStr(node->pair.Key, prefix);

                //newnode->length = node->length - prefix;

                //newnode->data = node->data;
                newnode->pair.Value = tmp.Value;

                newnode->link = node->link;
                node->link = newnode;

                //char *buf = new char[prefix];
                //CopyStr(buf, node->key, prefix);

                //delete node->key;

                node->pair.Key = CopyStartOfStr(node->pair.Key,prefix);
                //node->length = prefix;
            }

            sonsbrother = 0;
            parent = node;
            node = node->link;

            //t += prefix;
            tmp.Key = CopyEndOfStr(tmp.Key,prefix);
            //len -= prefix;
        } else {
            return false;
        }
    }
    return true;
}*/
/*
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
            return 0;
        }
    }

    return 1;
}
*/
bool TPatriciaTree::Remove (TPair &inp) {
    TPatriciaTree *node = this;
    TPatriciaTree *parent = nullptr;
    TPatriciaTree *brother = nullptr;
    int prefix;

    while (true) {
        if (node == nullptr) {
            return false;
        }

        prefix = Prefix(node->pair.Key, inp.Key);

        if (prefix == inp.Key.Length()) {
            TPatriciaTree *tmpNode = node->next;

            if (parent != nullptr) {
                if (tmpNode == nullptr) {
                    if (brother != nullptr && parent->link == brother) {
                        //merge parent & brother
                        parent->pair.Key = parent->pair.Key + brother->pair.Key;
                        parent->pair.Value = brother->pair.Value;
                        parent->link = brother->link;

                        brother->next = nullptr;
                        brother->link = nullptr;
                        delete brother;
                    } else {
                        brother->next = nullptr;
                    }
                } else {
                    if (brother == nullptr && tmpNode->next == nullptr && parent->link == node) {
                        //merge parent & tmpNode (node->next)

                        parent->pair.Key = parent->pair.Key + tmpNode->pair.Key;
                        parent->link = tmpNode->link;
                        parent->pair.Value = tmpNode->pair.Value;

                        tmpNode->next = nullptr;
                        tmpNode->link = nullptr;
                        delete tmpNode;
                    } else if (brother == nullptr && tmpNode->next != nullptr && parent->link == node) {
                        parent->link = tmpNode;
                    } else if (brother != nullptr) {
                        brother->next = tmpNode;
                    }
                }

                node->next = nullptr;
                node->link = nullptr;
                delete node;
                break;
            } else {
                if (brother == nullptr) {
                    if (node->next == nullptr) {
                        node->pair.Key = "";
                        node->pair.Value = 0;
                    } else {

                        brother = node->next;

                        node->pair.Key = brother->pair.Key;
                        node->pair.Value = brother->pair.Value;

                        node->next = brother->next;
                        node->link = brother->link;

                        brother->next = nullptr;
                        brother->link = nullptr;
                        delete brother;
                    }
                } else {
                    brother->next = tmpNode;
                    node->next = nullptr;
                    node->link = nullptr;
                    delete node;
                }
            }

            break;
        } else if (prefix == 0) {
            brother = node;
            node = node->next;
        } else if (prefix == node->pair.Key.Length()) {
            parent = node;
            node = node->link;
            brother = nullptr;

            inp.Key = CopyEndOfStr(inp.Key, prefix);
        } else {
            return false;
        }
    }
    return true;
}

void CutStr (TString &arr, int startIndex, const TString &str) {
    int len = str.Length();
    if (len > arr.Length()) {
        std::cerr << "Хуйня" << std::endl;
        EXIT_FAILURE;
    } else
        for (int i = startIndex; i < len; ++i) {
            arr[i] = str[i - len];
        }
}

void CopyStr(char* dst, const TString &str) {
    for (int i = 0; i < str.Length(); ++i) {
        dst[i] = str[i];
    }
}

void TPatriciaTree::Save (TString &path) {
    const int size = 257;
    char *key = new char[size];
    int len = 0;
    TStack <const TPatriciaTree *> *s = new TStack <const TPatriciaTree *>;
    const TPatriciaTree *node = this;
    const TPatriciaTree *last = nullptr;
    std::ofstream file (path);
    if (!file) {
        std::cout << "ERROR: couldn't create file!\n";
        return;
    }
    s->Push(node);
    while (s->Empty() == 0) {
        if (node->link != nullptr && last != node->link && last != node->next) {
            CopyStr(key + len, node->pair.Key);
            len += node->pair.Key.Length();
            key[len] = '\0';
            s->Push(node);
            node = node->link;
        } else {
            if (last != node->link || node->link == nullptr) {
                CopyStr(key + len, node->pair.Key);
                len += node->pair.Key.Length();
                key[len] = '\0';
            }
            if (last == nullptr || (last != node->next && last != node->link)) {
                //fprintf(file, "%s %llu\n", key, node->pair.Value);
                file << key << " " << node->pair.Value << std::endl;
            }
            if (node->next != nullptr && (last == nullptr || last != node->next)) {
                len -= node->pair.Key.Length();
                s->Push(node);
                node = node->next;
                continue;
            }
            last = node;
            len -= node->pair.Key.Length();
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

void TPatriciaTree::Load (TString &path) {
    TPair tmp;
    std::ifstream file(path);
    //char *key = new char[257];
    //unsigned int len;

    while (file >> tmp.Key >> tmp.Value) {
        //len = pair.Key.Length();
        this->Insert(tmp);
    }

    std::cout << "OK\n";
}

TPatriciaTree::~TPatriciaTree () {
    //delete key;
    delete next;
    delete link;
    //pair.Key = nullptr;
    next = nullptr;
    link = nullptr;
    //key = nullptr;
    //length = 0;
    //data = 0;
}