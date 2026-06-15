#include "DoubleLinkedList.h"
#include "Song.h"
#include "Playlist.h"
template <typename T>
DoubleLinkedList<T>::DoubleLinkedList() {
    Head = tail = nullptr;
}

template <typename T>
void DoubleLinkedList<T>::setHead(DLLNode<T>* h) { Head = h; }

template <typename T>
void DoubleLinkedList<T>::setTail(DLLNode<T>* t) { tail = t; }

template <typename T>
DLLNode<T>* DoubleLinkedList<T>::gethead() { return Head; }

template <typename T>
DLLNode<T>* DoubleLinkedList<T>::gettail() { return tail; }

template <typename T>
void DoubleLinkedList<T>::Add(T data) {
    if (!Head) {
        Head = new DLLNode<T>(data);
        Head->setNext(Head);
        Head->setPrev(Head);
        tail = Head;
    }
    else {
        DLLNode<T>* node = new DLLNode<T>(data);
        node->setPrev(tail);
        node->setNext(Head);
        tail->setNext(node);
        Head->setPrev(node);
        tail = node;
    }
}

template <typename T>
int DoubleLinkedList<T>::size() {
    if (!Head) return 0;
    int c = 0;
    DLLNode<T>* temp = Head;
    do {
        c++;
        temp = temp->getNext();
    } while (temp != Head);
    return c;
}

template <typename T>
T DoubleLinkedList<T>::getByIndex(int index) {
    if (!Head) return nullptr;
    DLLNode<T>* temp = Head;
    int i = 0;
    do {
        if (i == index) return temp->getData();
        temp = temp->getNext();
        i++;
    } while (temp != Head);
    return nullptr;
}

template <typename T>
void DoubleLinkedList<T>::clear() {
    if (!Head) return;
    DLLNode<T>* curr = Head->getNext();
    while (curr != Head) {
        DLLNode<T>* tmp = curr;
        curr = curr->getNext();
        delete tmp;
    }
    delete Head;
    Head = tail = nullptr;
}

template <typename T>
void DoubleLinkedList<T>::removeByIndex(int index) {
    int s = size();
    if (!Head || index < 0 || index >= s) return;
    DLLNode<T>* temp = Head;
    for (int i = 0; i < index; i++) temp = temp->getNext();
    if (s == 1) {
        delete temp;
        Head = tail = nullptr;
    }
    else {
        temp->getPrev()->setNext(temp->getNext());
        temp->getNext()->setPrev(temp->getPrev());
        if (temp == Head) Head = temp->getNext();
        if (temp == tail) tail = temp->getPrev();
        delete temp;
    }
}

template class DoubleLinkedList<Song*>;
template class DoubleLinkedList<Playlist*>;