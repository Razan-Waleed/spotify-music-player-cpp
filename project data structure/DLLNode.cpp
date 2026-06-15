#include "DLLNode.h"
#include "Song.h"
#include "Playlist.h"

template <typename T>
DLLNode<T>::DLLNode(T d) {
    data = d;
    next = prev = nullptr;
}

template <typename T>
void DLLNode<T>::setNext(DLLNode<T>* n) { next = n; }

template <typename T>
void DLLNode<T>::setPrev(DLLNode<T>* p) { prev = p; }

template <typename T>
DLLNode<T>* DLLNode<T>::getNext() { return next; }

template <typename T>
DLLNode<T>* DLLNode<T>::getPrev() { return prev; }

template <typename T>
T DLLNode<T>::getData() { return data; }


template class DLLNode<Song*>;
template class DLLNode<Playlist*>;