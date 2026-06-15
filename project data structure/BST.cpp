#include "BST.h"
#include <iostream>
#include "global.h"

using namespace std;

// Constructor: initialize root to NULL
BST::BST() {
    root = NULL;
}

// Return root of the BST
Node* BST::getRoot() const {
    return root;
}

// Set root of the BST
void BST::setRoot(Node* r) {
    root = r;
}

// Recursive helper function to insert a song into the BST
void BST::BSTinsert(Node*& root, Song* s) {
    if (!root) {
        // If current position is empty, create a new node
        root = new Node(s);
    }
    else {
        // Convert both names to lowercase for case-insensitive comparison
        string name1 = strtolower(s->getname());
        string name2 = strtolower(root->getSong()->getname());

        // Insert into left subtree if name is smaller
        if (name1 < name2) {
            BSTinsert(root->getLeft(), s);
        }
        // Otherwise insert into right subtree
        else {
            BSTinsert(root->getRight(), s);
        }
    }
}

// Public insert function
void BST::insert(Song* s) {
    BSTinsert(root, s);
}

// Recursive function to delete all nodes in BST
void BST::clearBST(Node*& root) {
    if (!root) return;

    // Delete left subtree
    clearBST(root->getLeft());

    // Delete right subtree
    clearBST(root->getRight());

    // Delete current node
    delete root;
    root = NULL;
}

// Clear entire BST
void BST::clear() {
    clearBST(root);
}

// In-order traversal to display songs
void BST::displayBST(Node* root) {
    if (!root) return;

    // Visit left subtree
    displayBST(root->getLeft());

    // Display current song
    root->getSong()->displaysong();

    // Visit right subtree
    displayBST(root->getRight());
}

// Display BST starting from root
void BST::display() {
    displayBST(root);
}

// Display BST with numbering (in-order traversal)
void BST::Display(Node* r, int& index) {
    if (r == NULL) return;

    // Traverse left subtree
    Display(r->getLeft(), index);

    // Display current node with index
    cout << ++index << ": "
        << r->getSong()->getname() << " by "
        << r->getSong()->getartist() << endl;

    // Traverse right subtree
    Display(r->getRight(), index);
}

// Get a song by its in-order index
Song* BST::getByIndex(Node* r, int target, int& current) {
    if (r == NULL) return NULL;

    // Search in left subtree
    Song* left = getByIndex(r->getLeft(), target, current);
    if (left) return left;

    // Check current node
    if (++current == target)
        return r->getSong();

    // Search in right subtree
    return getByIndex(r->getRight(), target, current);
}
