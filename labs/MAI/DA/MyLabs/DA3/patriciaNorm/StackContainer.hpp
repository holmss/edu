//
// Created by Maxim Spiridonov on 21.10.17.
//

template <class T>
TStackData <T>::TStackData () {
    next = nullptr;
    prev = nullptr;
}

template <class T>
TStackData <T> *TStackData <T>::GetNext () {
    return next;
}

template <class T>
TStackData <T> *TStackData <T>::GetPrev () {
    return prev;
}

template <class T>
T &TStackData <T>::GetData () {
    return data;
}

template <class T>
TStackData <T>::~TStackData () {
}

template <class T>
TStack <T>::TStack () {
    head = nullptr;
}

template <class T>
T *TStack <T>::Top () {
    if (head != nullptr) {
        return &(head->data);
    }

    return nullptr;
}

template <class T>
void TStack <T>::Pop () {
    if (head == nullptr) {
        return;
    }

    if (head->prev != nullptr) {
        TStackData <T> *temp = head;

        head = head->prev;
        head->next = nullptr;

        delete temp;
    } else {
        delete head;

        head = nullptr;
    }
}

template <class T>
void TStack <T>::Push (T &t) {
    if (head != nullptr) {
        TStackData <T> *temp = new TStackData <T>;
        temp->data = t;
        head->next = temp;
        temp->prev = head;

        head = temp;
    } else {
        head = new TStackData <T>;
        head->data = t;
    }
}

template <class T>
bool TStack <T>::Empty () {
    if (head == nullptr) {
        return 1;
    }

    return 0;
}

template <class T>
TStack <T>::~TStack () {
    while (head != nullptr) {
        this->Pop();
    }
}