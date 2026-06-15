#ifndef NODE_HPP
#define NODE_HPP

#include "Song.h"

class Node {
private:
    Node* left;
    Node* right;
    Song* song;

public:
    Node();
    Node(Song* s);

    void setLeft(Node* l);
    void setRight(Node* r);
    void setSong(Song* s);

    Node*& getLeft();
    Node*& getRight();
    Song* getSong() const;
};

#endif#pragma once
