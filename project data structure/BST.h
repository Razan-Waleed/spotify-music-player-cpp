#ifndef BST_HPP
#define BST_HPP

#include "Node.h"
#include "Song.h"

class BST {
private:
    Node* root;

    void BSTinsert(Node*& root, Song* s);
    void clearBST(Node*& root);
    void displayBST(Node* root);

public:
    BST();
    Node* getRoot() const;
    void setRoot(Node* r);
    void insert(Song* s);
    void clear();
    void display();

    void Display(Node* r, int& index);
    Song* getByIndex(Node* r, int target, int& current);
};

#endif#pragma once
