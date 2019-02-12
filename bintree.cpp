#include "bintree.h"
#include <iostream>
using namespace std;

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


//---------------------------- Constructor ------------------------------------
// Creates an empty BinTree, with all values set to NULL
//-----------------------------------------------------------------------------
BinTree::BinTree(){
    // create a new Node as the root
    root = new Node();
    // delete and set the data of the root to NULL as its default is
    // a string ""
    delete root->data;
    root->data = NULL;

}// end of constructor

//---------------------------- Constructor ------------------------------------
// Copies an existing BinTree
// Parameter: A BinTree that is being copied
//-----------------------------------------------------------------------------
BinTree::BinTree(const BinTree &toCopy){

    // create a new Node as the root
    root = new Node();
    delete root->data;
    // delete and set the data of the root to NULL as its default is
    // a string ""
    root->data = NULL;

    // call assignmentHelper with the root of this and the root of the BinTree being
    // copied
    assignmentHelper(root, toCopy.root);

}// end of copy constructor

//---------------------------- Destructor -------------------------------------
// Destructs the current tree
//-----------------------------------------------------------------------------
BinTree::~BinTree(){

    // makeEmptyHelper to clear all the values in the tree
    makeEmptyHelper(root);
    // set the root to NULL
    root = NULL;

}// end of Destructor

//---------------------------- operator= --------------------------------------
// Make a deep copy of a supplied tree to the current tree
// Parameter: A BinTree to be copied
// Return: The current tree that is a copy of the supplied tree
//-----------------------------------------------------------------------------
BinTree& BinTree::operator=(const BinTree &assignedTree){

    // only copy the tree if it is different than the
    // current tree
    if(&assignedTree != this){
        // empty the current tree
        makeEmpty();
        // call assignmentHelper with the root of the current tree
        // and the root of the tree being copied
        assignmentHelper(root, assignedTree.root);
    }
    // return the current tree
    return *this;


} // end of operator=

//---------------------------- assignmentHelper -------------------------------
// Recursive method for assiggning one tree to another
// Parameter: newBase - the root of the tree that is being copied too
//            oldBase - the root of the tree that is being copied
// Return: None
//-----------------------------------------------------------------------------
void BinTree::assignmentHelper(Node* newBase, Node* oldBase){

    //if both nodes are NULL nothing needs to be assigned so return
    if(oldBase == NULL || oldBase->data == NULL){
        return;
    }

    // create a new Node with the data to be copied and assign it
    // to the new tree
    NodeData* tempData = new NodeData(*oldBase->data);
    newBase->data = tempData;
    // set the children of the node to NULL
    newBase->left = NULL;
    newBase->right = NULL;

    // if the tree being copied has a left child that isn't NULL
    // create a new node for the left child in the new tree and
    // recursively call this function for the left child of
    // both trees
    if(oldBase->left != NULL){
        newBase->left = new Node();
        delete newBase->left->data;
        newBase->left->data = NULL;
        assignmentHelper(newBase->left, oldBase->left);
    }

    // if the tree being copied has a right child that isn't NULL
    // create a new node for the right child in the new tree and
    // recursively call this function for the right child of
    // both trees
    if(oldBase->right != NULL){
        newBase->right = new Node();
        delete newBase->right->data;
        newBase->right->data = NULL;
        assignmentHelper(newBase->right, oldBase->right);
    }

    return;
}//end of assignmentHelper

//---------------------------- operator== -------------------------------------
// Compares whether two trees are equal or not
// Parameter: comparedTree - The tree that is being compared to this tree
// Return: Bool - whether the two trees are equal or not
//-----------------------------------------------------------------------------
bool BinTree::operator==(const BinTree &comparedTree) const{

    // call equalsHelper comparing the root of this tree and the tree being
    // compared
    return equalsHelper(root, comparedTree.root);


} // end of operator==

//---------------------------- operator!= -------------------------------------
// Compares whether two trees are not equal or not
// Parameter: comparedTree - The tree that is being compared to this tree
// Return: Bool - whether the two trees are equal or not
//-----------------------------------------------------------------------------
bool BinTree::operator!=(const BinTree &comparedTree) const{

    // call equalsHelper comparing the root of this tree and the tree being
    // compared
    // returns the opposite of equalsHelper
    return ! ( equalsHelper(root, comparedTree.root) );


}//end of operator!=

//---------------------------- equalsHelper -----------------------------------
// Recursive function that to help with tree comparison
// Parameter: base - root of the this tree
//            comparedBase - root of the tree being compared to this tree
// Return: Bool - whether the two trees are equal or not
//-----------------------------------------------------------------------------
bool BinTree::equalsHelper(Node* base, Node* comparedBase) const{

    // if both nodes are NULL return true
    if( base == NULL && comparedBase == NULL ){
        return true;
    }
    // if one node exists and the other is NULL return false
    if((base != NULL && comparedBase == NULL) || (base == NULL && comparedBase != NULL)){
        return false;
    }
    // if the data in both nodes is not the same return false
    if(*base->data != *comparedBase->data){
        return false;
    }
    // if both items are equal recursively call this function
    if(*base->data == *comparedBase->data){
        // store the value of the left and right recursive calls in temp
        // use || such that true only will return if both sides are true
        bool temp = equalsHelper(base->left, comparedBase->left) || equalsHelper(base->right, comparedBase->right);
        // return true only if temp is true
        return true || temp;
    }

}// end of equalsHelper

//---------------------------- retrieve ---------------------------------------
// Finds if a value exists in the tree and if it does points a pointer to the
// node that has that value
// Parameter: finding - a node with the string that is being looked for
//            foundData - a pointer to a node, that will point to the node if
//                        if it is found.
// Return: bool - whether the node was found or not
//-----------------------------------------------------------------------------
bool BinTree::retrieve( const NodeData &finding, NodeData* &foundData ) const{
    // all retrieveHelper with the root of this tree
    // the object that is being looked for, and a pointer for if that item is
    // found
    return retrieveHelper(root, finding, foundData);
}//end of retrieve

//---------------------------- retrieveHelper ---------------------------------
// Recursive method that helps with finding if a value exists in the tree and
// if it does points a pointer to the node that has that value
// Parameter: base - the base of the the tree that is being looked through
//            finding - a node with the string that is being looked for
//            foundData - a pointer to a node, that will point to the node if
//                        if it is found.
// Return: bool - whether the node was found or not
//-----------------------------------------------------------------------------
bool BinTree::retrieveHelper( Node* base, const NodeData& finding, NodeData* found) const{
    // flag used to mark if item is found
    bool flag;
    // if current node is NULL there is no item to be found so return false
    if(base == NULL){
        return false;
    }
    // if the current nodes data is what is being looked for
    // point the found pointer at it and return true
    if(*base->data == finding){
        found = base->data;
        return true;
    }

    // only recurse to the right if the left recursive call did not find
    // the node that is being looked for
    flag = retrieveHelper(base->left, finding, found);
    if(flag == false){
        flag = retrieveHelper(base->right, finding, found);
    }
    // return flag which will be true/false if the node was found in the left or right children
    // of the current node
    return flag;


}//end of retrieveHelper

//---------------------------- getHeight --------------------------------------
// Finds the height of a node in the tree from the lowest leaf to that node
// Parameter: searchingTree - The node that the height will be found from
// Return: int - the height of the node, or if the node doesn't exist in the
//               tree, 0 will be returned.
//-----------------------------------------------------------------------------
int BinTree::getHeight(const NodeData &searchingTree){

    // create values placeholder variables for recursive call
    // they will correspond to if the node is found
    // and the height of that node
    bool foundFlag = false;
    int finalNum = 0;

    // call getHeightHelper with the root of this tree, the node that is being
    // looked for, and the placeholder variables
    getHeightHelper(root, foundFlag, finalNum, searchingTree);
    // if foundFlag is true
    // return the the height of it represented by finalNum
    // otherwise return 0
    if(foundFlag == true){
        return finalNum;

    }else{ return 0; }

}//end of getHeight

//---------------------------- getHeightHelper --------------------------------
// Recursive function to help finding the height of a node in the tree from the
// lowest leaf to that node
// Parameter: base - the root of the tree that height is being found for
//            flag - a flag that will flip if the node is found
//            nodeSum - the height of the node, if it is found
//            toFind - The node that the height will be found from
// Return: int - the height of the node, or if the node doesn't exist in the
//               tree, 0 will be returned.
//-----------------------------------------------------------------------------
int BinTree::getHeightHelper(Node* base, bool& flag, int& nodeSum, const NodeData& toFind){
    // variables for storing the distance from the leafs to the current node
    int left, right;

    // once NULL is hit return one to begin counting up from that node
    if(base == NULL){
        return 1;
    }

    // recursively call getHeightHelper for the left and right sides of the
    // current node and assign what they return to the left and right variables
    left = getHeightHelper(base->left, flag, nodeSum, toFind);
    right = getHeightHelper(base->right, flag, nodeSum, toFind);

    // once the node is found, mark the flag true
    // and assign the greater of left and right to nodeSum
    // thus saving the distance from the bottom of the tree to that node
    if(*base->data == toFind){

        flag = true;

        if(left < right){
            nodeSum = right;

        }else{
            nodeSum = left;
        }
    }

    // if flag is not true return the greater of left/right + 1 to count for
    // the current node
    if(flag != true){

        if(left < right){
            return right + 1;

        }else{
            return left + 1;
        }

    }else{
        // once flag is found return 0 to being the process of exiting the recursive
        // calls
        return 0;
    }



}//end of getHeightHelper

//---------------------------- bstreeToArray ----------------------------------
// Converts a binary tree into an array that will represent the tree inorder
// Parameter: copyArray - the array that the tree will be copied into
// Return : NONE
//-----------------------------------------------------------------------------
void BinTree::bstreeToArray(NodeData* copyArray[]){
    // create orderTracker which will keep track of which Node
    // corresponds to which index in the array
    int orderTracker = 0;
    // call recursive function, with the array that is being
    // copied to, the root of the current tree, and orderTrakcer
    bstreetToArrayHelper(copyArray, root, orderTracker);

}//end of bstreeToArray


//---------------------------- bstreeToArrayHelper ----------------------------
// Recursive function that helps convert a binary tree into an array that will
// represent the tree inorder
// Parameter: copyArray - the array that the tree will be copied into
//            tracker - an int that helps keep track of which node relates to
//                      which index in the array
// Return : NONE
//-----------------------------------------------------------------------------
void BinTree::bstreetToArrayHelper(NodeData* copyArray[], Node* base, int& tracker){
    // once NULL is hit return as nothing needs to be copied
    if(base == NULL){
        return;
    }

    // recursively call this function to the left of the current node
    bstreetToArrayHelper(copyArray, base->left, tracker);

    // copy the data in the current node the its appropriate
    // place in the array
    copyArray[tracker] = base->data;
    // set the current node to NULL
    base->data = NULL;
    // increment tracker so that the next node is assigned to the
    // next spot in the array
    tracker++;

    // recursively call to the right side of the current node
    bstreetToArrayHelper(copyArray, base->right, tracker);

    // once both sides of the current node have been recursed to
    // return to the previous level
    return;



}//end of bstreeToArrayHelper

//---------------------------- arrayToBSTree ----------------------------------
// Converts an array of NodeData's into a balanced binary tree
// Parameter: arrayToCopy - the array of NodeData's to be converted into a BST
// Return: NONE
//-----------------------------------------------------------------------------
void BinTree::arrayToBSTree(NodeData* arrayToCopy[]){

    // find the length of the array that is being copied
    int max = 0;
    while(arrayToCopy[max] != NULL){
        max++;
    }

    // empty the tree that is being copied to
    makeEmpty();

    // call recursive function with the array that is being copied from,
    // the current tree, and the first and last indices in the array
    arrayToBSTreeHelper(arrayToCopy, root, 0, max-1);

}//end of arrayToBSTree

//---------------------------- arrayToBSTreeHelper ----------------------------
// Recursive method that helps convert an array of NodeData's into a balanced
// binary tree
// Parameter: arrayToCopy - the array of NodeData's to be converted into a BST
//            base - the root of the tree that the data is copied into
//            min - the first index in the array that is being copied
//            max - the last index in the array that is being copied
// Return: NONE
//-----------------------------------------------------------------------------
void BinTree::arrayToBSTreeHelper(NodeData* arrayToCopy[], Node* base, int min, int max){
    // find the middle value of the of the length of the array segment
    int index = (max + min) / 2;

    // if min is greater than max than there is nothing to be copied
    if(min > max){
        return;
    }

    // copy the middle value of the array to the current node
    // set the copied index to NULL
    base->data = arrayToCopy[index];

    arrayToCopy[index] = NULL;

    // create a new Node for the left and right children
    base->left = new Node();
    base->right = new Node();

    // recurisvely call this function for the lower section of the array
    // which is the value min, to the index-1
    arrayToBSTreeHelper(arrayToCopy, base->left, min, index-1);
    // if nothing was assigned to the left child then delete it
    // and set it as NULL
    if((base->left)->data == NULL){
        delete base->left;
        base->left = NULL;
    }

    // recurisvely call this function for the lower section of the array
    // which is the value min, to the index-1
    arrayToBSTreeHelper(arrayToCopy, base->right, index+1, max);
    // if nothing was assigned to the right child then delete it
    // and set it as NULL
    if((base->right)->data == NULL){
        delete base->right;
        base->right = NULL;
    }
    // once both children have been visited return
    return;


}// end of arrayToBSTreeHelper

//---------------------------- isEmpty ----------------------------------------
// Returns whether a given tree is empty
// Parameter: NONE
// Return: Bool - True/False if the tree is empty
//-----------------------------------------------------------------------------
bool BinTree::isEmpty() const{
    // return if the root is NULL
    // the tree is only empty if the root is NULL
    return root == NULL;
}//end of isEmpty

//---------------------------- makeEmpty --------------------------------------
// Empties this tree of all its data
// Parameter: NONE
// Return: NONE
//-----------------------------------------------------------------------------
void BinTree::makeEmpty(){
    // call make empty helper with the root of the current tree
    makeEmptyHelper(root);
    // set the root to an empty node
    root = new Node();
    delete root->data;
    root->data = NULL;

}//end of makeEmpty

//---------------------------- makeEmptyHelper --------------------------------
// Recursive helper that empties this tree of all its data
// Parameter: base - the root of the tree that is being emptied
// Return: NONE
//-----------------------------------------------------------------------------
void BinTree::makeEmptyHelper(Node* base){
    // if the current node is NULL nothing needs to be made empty
    if(base == NULL){
        return;
    }

    // if the left child isn't empty and assigned as NULL
    // recurse to it and make it empty
    if(base->left != NULL){
        makeEmptyHelper(base->left);
    }
    // if the right child isn't empty and assigned as NULL
    // recurse to it and make it empty
    if(base->right != NULL){
        makeEmptyHelper(base->right);
    }

    //set the left and right children to NULL
    base->left = NULL;
    base->right = NULL;

    //delete the current nodes data and set it to NULL
    delete base->data;
    base->data = NULL;

    //delete teh current node and set it to NULL
    delete base;
    base = NULL;

    return;


}// end of makeEmptyHelper

//---------------------------- insert -----------------------------------------
// Inserts an item into this BinTree
// Parameter: toInsert - A NodeData that is to be inserted into the BinTree
// Return: bool - whether the toInsert was inserted or not
//-----------------------------------------------------------------------------
bool BinTree::insert(NodeData* toInsert){

    // call insert helper with the root of the current tree and the item to be
    // inserted
    return insertHelper(root, toInsert);


} // end of insert

//---------------------------- insertHelper -----------------------------------
// Recursive helper that helps insert an item into this BinTree
// Parameter: recursedRoot - the root of the tree that is being inserted into
//            toInsert - A NodeData that is to be inserted into the BinTree
// Return: bool - whether the toInsert was inserted or not
//-----------------------------------------------------------------------------
bool BinTree::insertHelper( Node* recursedRoot ,NodeData* toInsert ){

    // if the current node in the tree is NULL
    // insert the item that is needs to inserted
    // and set its children to NULL
    // return true as it is inserted
    if(recursedRoot == NULL || recursedRoot->data == NULL){
        recursedRoot->data = toInsert;
        recursedRoot->left = NULL;
        recursedRoot->right = NULL;
        return true;

    }

    // if the current item to be inserted is the same as the current item
    // in the current node (and not equal to NULL), then it does not
    // need to be inserted, return false it is not inserted
    if(recursedRoot->data != NULL && *recursedRoot->data == *toInsert){
        return false;

    }

    // if the item to be inserted is smaller than the current item,
    // and the current node does not have a left child, then insert
    // the current item as its child, then return true as the item
    // was inserted
    // otherwise make a recursive call to the left child
    if(*recursedRoot->data > *toInsert){
        if(recursedRoot->left == NULL){

            Node* ptrLeft = new Node();
            ptrLeft->data = toInsert;
            ptrLeft->left = NULL;
            ptrLeft->right = NULL;

            recursedRoot->left = ptrLeft;
            return true;

        }else{
            return insertHelper(recursedRoot->left, toInsert);
        }

    }

    // if the item to be inserted is larger than the current item,
    // and the current node does not have a right child, then insert
    // the current item as its child return true as the item was
    // inserted
    // otherwise make a recursive call to the right child
    if(*recursedRoot->data < *toInsert){
        if(recursedRoot->right == NULL){
            Node* ptrRight = new Node();

            ptrRight->data = toInsert;
            ptrRight->left = NULL;
            ptrRight->right = NULL;

            recursedRoot->right = ptrRight;
            return true;


        }else{
            return insertHelper(recursedRoot->right, toInsert);
        }

    }
}// end of insertHelper

//------------------------- displaySideways -----------------------------------
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
//-----------------------------------------------------------------------------
void BinTree::displaySideways() const {
    sideways(root, 0);
} //end of displaySideways

//---------------------------- operator<< -------------------------------------
// Prints this BinTree inorder to the user console
// Parameter: out - ostream that will print to user console
//            rhs - BinTree that is being printed
// Return: ostream - that prints to user
//-----------------------------------------------------------------------------
ostream& operator<<( ostream &out, const BinTree &rhs ){

    // call inorderHelper with the ostream and the tree that is being printed
    // to the user
    rhs.inorderHelper(out, rhs.root);
    // end the current line that is being printed
    out << endl;

    // return the ostream
    return out;

} //end of operator<<

//---------------------------- inorderHelper ----------------------------------
// Recursive function that helps print a BinTree inorder to the user console
// Parameter: out - ostream that will print to user console
//            node - root of the BinTree that is being printed
// Return: NONE
//-----------------------------------------------------------------------------
void BinTree::inorderHelper( ostream& out, Node* base ) const{
    // if the current node is NULL, nothing can be printed so return
    if(base == NULL){
        return;
    }

    // make a recursive call to the left
    inorderHelper(out, base->left);

    //print the data in the current node
    out << *base->data << " ";

    // make a recurisve call to the right
    inorderHelper(out, base->right);

    // once both children have been iterated through return to the previous node
    return;

} // end of inorderHelper

//---------------------------- Sideways ---------------------------------------
// Helper method for displaySideways
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
//-----------------------------------------------------------------------------
void BinTree::sideways(Node* current, int level) const {
    if (current != NULL) {
        level++;
        sideways(current->right, level);

        // indent for readability, 4 spaces per depth level
        for (int i = level; i >= 0; i--) {
            cout << "    ";
        }

        cout << *current->data << endl;        // display information of object
        sideways(current->left, level);
    }
} // end of Sideways

