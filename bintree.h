#include <iostream>
#include <fstream>
#include "nodedata.h"

#ifndef BINARYTREE_BINTREE_H
#define BINARYTREE_BINTREE_H

//---------------------- Assignment 2 -----------------------------------------
// Kieran Coito CSS343A
// 27/01/2019
// 03/02/2019
//-----------------------------------------------------------------------------
// BinTree class:
// This program creates a binary tree of string values
// - There are two ways to construct this tree intially, either by creating an
// empty tree or by copying an already existing tree
// - The operator = is supported
// - The height from the bottom of the tree to a specified node is supported
// but the overall height of the tree is not possible to get unless you know
// what the value of the root node is.
// - It can convert an array of nodes containing strings into a balanced binary
// tree
// - It can display an array in order in a single line, or as a sideways tree
// - == and != are supported comparisons
//-----------------------------------------------------------------------------
// Assumptions:
// - Users will only try to sort string values and they will want them sorted
// in ascending order based on there ASCIII values.
// - This tree class does not support feeding in strings directly and instead
// must be created using class NodeData nodes to input the desired values
//-----------------------------------------------------------------------------


class BinTree{

    friend ostream& operator<<( ostream &out, const BinTree &rhs );

public:

    BinTree();								// constructor
    BinTree(const BinTree &);				// copy constructor
    ~BinTree();                             // destructor, calls makeEmpty

    BinTree& operator=(const BinTree &);
    bool operator==(const BinTree &) const;
    bool operator!=(const BinTree &) const;

    bool retrieve( const NodeData& finding, NodeData* &found ) const; // retrieves an item from the tree
    int getHeight(const NodeData & toFind); // returns the height of a specified node

    void bstreeToArray(NodeData* []); // converts a tree to an inorder array
    void arrayToBSTree(NodeData* []); // converts an array to a balanced tree

    bool isEmpty() const;					// true if tree is empty, otherwise false
    void makeEmpty();						// make the tree empty so isEmpty returns true

    bool insert(NodeData* toInsert);
    void displaySideways() const;			// displays the tree sideways



private:

    struct Node {

        NodeData* data;						// pointer to data object
        Node* left;							// left subtree pointer
        Node* right;						// right subtree pointer
        Node() : data(), left(NULL), right(NULL) {}; //default node creation

    };


    Node* root;								// root of the tree

    // utility functions and helper functions for the public methods
    void inorderHelper(ostream& out, Node* base) const;
    void sideways(Node*, int) const;			// provided below, helper for displaySideways()
    bool insertHelper( Node* recursedRoot, NodeData* toInsert );
    bool retrieveHelper( Node* base, const NodeData& finding, NodeData* found) const;
    int getHeightHelper(Node* base, bool& flag, int& nodeSum, const NodeData& toFind);
    void makeEmptyHelper(Node* base);
    bool equalsHelper(Node* base, Node* comparedBase) const;
    void assignmentHelper(Node* newBase, Node* oldBase);
    void bstreetToArrayHelper(NodeData* [], Node* base, int& tracker);
    void arrayToBSTreeHelper(NodeData* arrayToCopy[], Node* base, int min, int max);

};

#endif //BINARYTREE_BINTREE_H
