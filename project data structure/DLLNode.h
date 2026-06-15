#ifndef DLLNODE_HPP
#define DLLNODE_HPP

template <typename T>
class DLLNode {
private:
    T data;
    DLLNode<T>* next;
    DLLNode<T>* prev;

public:
    DLLNode(T d);
    void setNext(DLLNode<T>* n);
    void setPrev(DLLNode<T>* p);
    DLLNode<T>* getNext();
    DLLNode<T>* getPrev();
    T getData();
};

#endif#pragma once
