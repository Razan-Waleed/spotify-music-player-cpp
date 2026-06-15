#include "Node.h"

Node::Node() {
    left = NULL;
    right = NULL;
    song = NULL;
}

Node::Node(Song* s) {
    left = NULL;
    right = NULL;
    song = s;
}

void Node::setLeft(Node* l) { left = l; }
void Node::setRight(Node* r) { right = r; }
void Node::setSong(Song* s) { song = s; }

Node*& Node::getLeft() { return left; }
Node*& Node::getRight() { return right; }
Song* Node::getSong() const { return song; }