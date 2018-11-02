#include <iostream>
#include <fstream>

namespace NStackContainer {

    template<class T> class TStackData {
    public:
        TStackData();

        T& GetData();
        TStackData<T>* GetNext();
        TStackData<T>* GetPrev();

        virtual ~TStackData();
        T data;
        TStackData<T>* next;
        TStackData<T>* prev;
    };

    template<class T> class TStack : public TStackData<T> {
    public:
        TStack();

        T* Top();
        void Pop();
        void Push(T&);
        bool Empty();

        virtual ~TStack();
    private:
        TStackData<T>* head;
    };

    class TPatriciaTree {
    public:
        TPatriciaTree();

        const unsigned long long* Search(const char*, unsigned int);
        bool Insert(const char*, unsigned int, unsigned long long);
        bool Remove(const char*, unsigned int);

        void Load(const char*);
        void Save(const char*);

        void Print(const TPatriciaTree* node = NULL, int lvl = -1);

        virtual ~TPatriciaTree();
    private:
        TPatriciaTree* next;
        TPatriciaTree* link;
        char* key;
        unsigned int length;
        unsigned long long data;
    };

    unsigned int LengthString(const char* string) {
	unsigned int length = 0;

	while( (string + length != NULL) && string[length] != '\0') {
	    ++length;
	}

	return length;
    }


    int Prefix(const char* string1, unsigned int len1 , const char* string2, unsigned int len2) {
        int prefix = 0;

        while(prefix != len1 && prefix != len2 && string1[prefix] == string2[prefix]) {
            ++prefix;
        }

        return prefix;
    }

    void CopyStr(char* dst, const char* src, unsigned int len) {
        for (int i = 0;i < len;++i) {
            dst[i] = src[i];
        }
    }

}

template<class T> NStackContainer::TStackData<T>::TStackData() {
    next = NULL;
    prev = NULL;
}

template<class T> NStackContainer::TStackData<T>* NStackContainer::TStackData<T>::GetNext() {
    return next;
}

template<class T> NStackContainer::TStackData<T>* NStackContainer::TStackData<T>::GetPrev() {
    return prev;
}

template<class T> T& NStackContainer::TStackData<T>::GetData() {
    return data;
}

template<class T> NStackContainer::TStackData<T>::~TStackData() {
}

template<class T> NStackContainer::TStack<T>::TStack() {
    head = NULL;
}

template<class T> T* NStackContainer::TStack<T>::Top() {
    if (head != NULL) {
        return &(head->data);
    }

    return NULL;
}

template<class T> void NStackContainer::TStack<T>::Pop() {
    if (head == NULL) {
        return;
    }

    if (head->prev != NULL) {
        NStackContainer::TStackData<T>* temp = head;

        head = head->prev;
        head->next = NULL;

        delete temp;
    }
    else {
        delete head;

        head = NULL;
    }
}

template<class T> void NStackContainer::TStack<T>::Push(T& t) {
    if (head != NULL) {
        NStackContainer::TStackData<T>* temp = new NStackContainer::TStackData<T>;
        temp->data = t;
        head->next = temp;
        temp->prev = head;

        head = temp;
    }
    else {
        head = new NStackContainer::TStackData<T>;
        head->data = t;
    }
}

template<class T> bool NStackContainer::TStack<T>::Empty() {
    if (head == NULL) {
        return 1;
    }

    return 0;
}

template<class T> NStackContainer::TStack<T>::~TStack() {
    while (head != NULL) {
        this->Pop();
    }
}


NStackContainer::TPatriciaTree::TPatriciaTree() {
    next = NULL;
    link = NULL;
    key = NULL;
    length = 0;
    data = 0;
}

const unsigned long long* NStackContainer::TPatriciaTree::Search(const char* t, unsigned int len) {
    TPatriciaTree* node = this;
    int prefix;
    ++len;

    while (node != NULL) {
        prefix = NStackContainer::Prefix(node->key, node->length, t, len);

        if (prefix == 0) {
            node = node->next;
        }
        else if (prefix == len) {
            return &(node->data);
        }
        else if (prefix == node->length) {
            node = node->link;
        }
        else {
            node = NULL;
        }


        t += prefix;
        len -= prefix;
    }

    return NULL;
}


bool NStackContainer::TPatriciaTree::Insert(const char* t, unsigned int len, unsigned long long num) {
    NStackContainer::TPatriciaTree* node = this;
    NStackContainer::TPatriciaTree* parent = NULL;
    int prefix;
    bool sonsbrother;

    ++len;

    if (node->length == 0) {
        node->key = new char[len];

        NStackContainer::CopyStr(node->key, t, len);
        node->length = len;
        node->data = num;

        return 1;
    }

    while(1) {
        if (len == 0) {
            ++len;
        }
        if (node == NULL){
            node = new NStackContainer::TPatriciaTree;

            node->key = new char[len];

            NStackContainer::CopyStr(node->key, t, len);
            node->length = len;
            node->data = num;

            if(parent != NULL) {
                if (sonsbrother) {
                    parent->next = node;
                }
                else {
                    node->next = parent->link;
                    parent->link = node;
                }
            }

            break;
        }

        prefix = NStackContainer::Prefix(node->key, node->length, t, len);

        if (prefix == 0) {
            sonsbrother = 1;
            parent = node;
            node = node->next;
        }
        else if (prefix < len) {
            if (prefix < node->length) {
                NStackContainer::TPatriciaTree* newnode = new NStackContainer::TPatriciaTree;

                newnode->key = new char[node->length - prefix];
                NStackContainer::CopyStr(newnode->key, node->key + prefix, node->length - prefix);
                newnode->length = node->length - prefix;
                newnode->data = node->data;

                newnode->link = node->link;
                node->link = newnode;

                char* buf = new char[prefix];
                NStackContainer::CopyStr(buf, node->key, prefix);

                delete node->key;

                node->key = buf;
                node->length = prefix;
            }

            sonsbrother = 0;
            parent = node;
            node = node->link;

            t += prefix;
            len -= prefix;
        }
        else {
	    return 0;
        }
    }

    return 1;
}

bool NStackContainer::TPatriciaTree::Remove(const char* t, unsigned int len) {
    NStackContainer::TPatriciaTree* node = this;
    NStackContainer::TPatriciaTree* parent = NULL;
    NStackContainer::TPatriciaTree* brother = NULL;
    int prefix;
    ++len;

    while(1) {
        if (len == 0) {
            ++len;
        }
        if (node == NULL) {
	    return 0;
        }

        prefix = NStackContainer::Prefix(node->key, node->length, t, len);

        if (prefix == len) {
            NStackContainer::TPatriciaTree* temp = node->next;

            if (parent != NULL) {
                if( temp == NULL ) {
                    if (brother != NULL && parent->link == brother) {
                        //merge parent & brother
                        char* buf = new char[parent->length + brother->length];

                        NStackContainer::CopyStr(buf, parent->key, parent->length);
                        NStackContainer::CopyStr(buf + parent->length, brother->key, brother->length);

                        delete parent->key;

                        parent->key = buf;
                        parent->length += brother->length;
                        parent->data = brother->data;
                        parent->link = brother->link;

                        brother->next = NULL;
                        brother->link = NULL;
                        delete brother;
                    }
                    else {
                        brother->next = NULL;
                    }
                }
                else {
                    if (brother == NULL && temp->next == NULL && parent->link == node) {
                        //merge parent & temp
                        char* buf = new char[parent->length + temp->length];

                        NStackContainer::CopyStr(buf, parent->key, parent->length);
                        NStackContainer::CopyStr(buf + parent->length, temp->key, temp->length);

                        delete parent->key;

                        parent->key = buf;
                        parent->length += temp->length;
                        parent->link = temp->link;
                        parent->data = temp->data;

                        temp->next = NULL;
                        temp->link = NULL;
                        delete temp;
                    }
                    else if (brother == NULL && temp->next != NULL && parent->link == node) {
                        parent->link = temp;
                    }
                    else if (brother != NULL) {
                        brother->next = temp;
                    }
                }

                node->next = NULL;
                node->link = NULL;
                delete node;
                break;
            }
            else {
                if(brother == NULL) {
                    if(node->next == NULL) {
                        delete node->key;

                        node->length = 0;
                        node->key = NULL;
                        node->data = 0;
                    }
                    else {
                        delete node->key;
                        brother = node->next;

                        node->key = new char[brother->length];
                        NStackContainer::CopyStr(node->key, brother->key, brother->length);

                        node->length = brother->length;
                        node->data = brother->data;
                        node->next = brother->next;
                        node->link = brother->link;

                        brother->next = NULL;
                        brother->link = NULL;
                        delete brother;
                    }
                }
                else {
                    brother->next = temp;

                    node->next = NULL;
                    node->link = NULL;
                    delete node;
                }
            }

            break;
        }
        else if (prefix == 0) {
            brother = node;
            node = node->next;
        }
        else if (prefix == node->length) {
            parent = node;
            node = node->link;
            brother = NULL;

            t += prefix;
            len -= prefix;
        }
        else {
	    return 0;
            break;
        }
    }

    return 1;
}

void NStackContainer::TPatriciaTree::Save(const char* path) {
    const int size = 257;
    char* key = new char[size];
    int len = 0;
    NStackContainer::TStack<const NStackContainer::TPatriciaTree*>*  s = new NStackContainer::TStack<const NStackContainer::TPatriciaTree*>;
    const NStackContainer::TPatriciaTree* node = this;
    const NStackContainer::TPatriciaTree* last = NULL;
    FILE* file = NULL;

    file = fopen(path, "wb");

    if (file == NULL) {
	std::cout << "ERROR: couldn't create file!\n";
	return;
    }

    s->Push(node);

    while(s->Empty() == 0) {
        if (node->link != NULL && last != node->link && last != node->next) {
            NStackContainer::CopyStr(key + len, node->key, node->length);
            len += node->length;
            key[len] = '\0';

	    s->Push(node);
            node = node->link;
        }
        else {
	    if (last != node->link || node->link == NULL) {
	             NStackContainer::CopyStr(key + len, node->key, node->length);
            len += node->length;
            key[len] = '\0';
	    }

	    if (last == NULL || (last != node->next && last != node->link)) {
		fprintf(file, "%s %llu\n", key, node->data);
	    }

	    if (node->next != NULL && (last == NULL || last != node->next)) {
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

    fclose(file);
    delete s;
    delete []key;
}

void NStackContainer::TPatriciaTree::Load(const char* path) {
    unsigned long long data;
    std::ifstream file(path);
    char* key = new char[257];
    unsigned int len;

    while(file >> key >> data) {
	len = LengthString(key);

	this->Insert(key, len, data);
    }

    std::cout << "OK\n";

    delete[] key;
}

NStackContainer::TPatriciaTree::~TPatriciaTree() {
    delete key;
    delete next;
    delete link;

    next = NULL;
    link = NULL;
    key = NULL;
    length = 0;
    data = 0;
}

void Registr(char*, int);

int main() {
    NStackContainer::TPatriciaTree* p = new NStackContainer::TPatriciaTree;
    const int size = 1025;
    char temp[size];
    unsigned long long data;
    char choice;
    int len;

    if (!std::cin.get(choice)) {
        return 0;
    }

    std::cin.putback(choice);

    while(std::cin >> choice) {
        switch (choice) {
        case '+': {
            std::cin >> temp >> data;
            len = NStackContainer::LengthString(temp);
            Registr(temp, len);

            if (p->Insert(temp, len, data)) {
		std::cout << "OK\n";
	    }
	    else {
		std::cout << "Exist\n";
	    }
        }
            break;
        case '-': {
            std::cin >> temp;
            len = NStackContainer::LengthString(temp);
            Registr(temp, len);

            if (p->Remove(temp, len)) {
		std::cout << "OK\n";
	    }
	    else {
		std::cout << "NoSuchWord\n";
	    }
        }
            break;
        case '!': {
            std::cin.get(choice);
            std::cin.get(choice);

            if (choice == 'S') {
                std::cin >> temp >> temp;

                p->Save(temp);
            }
            else  {
                std::cin >> temp >> temp;
		delete p;

		p = new NStackContainer::TPatriciaTree;
		p->Load(temp);
            }

        }
            break;
        default: {
	    int len;
            std::cin.putback(choice);
            std::cin >> temp;

	    len = NStackContainer::LengthString(temp);
	    Registr(temp, len);
	    const unsigned long long* d = p->Search(temp, len);

	    if (d == NULL) {
		std::cout << "NoSuchWord\n";
	    }
	    else {
		std::cout << "OK: " << *d << '\n';
	    }
	}
        }

    }

    delete p;

    return 0;
}

void Registr(char* t, int len) {
    for(int i = 0;i < len;++i) {
        if (t[i] >= 'A' && t[i] <= 'Z') {
            t[i] = 'a' + t[i] - 'A';
        }
    }
}

