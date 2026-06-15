#ifndef DOUBLELINKEDLIST_HPP
#define DOUBLELINKEDLIST_HPP

#include "DLLNode.h"

template <typename T>
class DoubleLinkedList {
private:
    DLLNode<T>* Head;
    DLLNode<T>* tail;

public:
    DoubleLinkedList();
    void setHead(DLLNode<T>* h);
    void setTail(DLLNode<T>* t);
    DLLNode<T>* gethead();
    DLLNode<T>* gettail();
    void Add(T data);
    int size();
    T getByIndex(int index);
    void clear();
    void removeByIndex(int index);
};

#endif#pragma once
