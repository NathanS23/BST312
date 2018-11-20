
/*  BST312.h
  CS 312 Fall 2018

  a simple implementation of a binary search tree


*/

#ifndef BST_312_H
#define BST_312_H

#include <cstdlib>  // Provides size_t
#include <iostream>
#include <vector>

using namespace std;

template<class ItemType>
class BST_312 {
public:

    BST_312();

    //Copy constructor
    BST_312(const BST_312 & src);

    ~BST_312();

/****************************
makeEmpty

Function: Removes all the items from the BST.
Preconditions: BST has been initialized
Postconditions: All the items have been removed
*****************************/
    void makeEmpty();

/****************************
isEmpty

Function: Checks to see if there are any items in the BST.
Preconditions: BST has been initialized
Postconditions: Returns true if there are no items in the BST, else false.
*****************************/
    bool isEmpty() const;

/****************************
isFull

Function: Determines if you have any more room to add items to the BST
Preconditions: BST has been initialized
Postconditions: Returns true if there is no more room to add items, else false
*****************************/
    bool isFull() const;

/****************************
insertItem

Function: Adds newItem to the BST.
Preconditions: BST has been initialized and is not full. Must also be a unique insert
Postconditions: newItem is in the proper position for a BST.
*****************************/
    void insertItem(const ItemType &);

/****************************
deleteItem

Function: Removes target from BST.
Preconditions: BST has been initialized.
Postconditions: If found, element has been removed from BST.
*****************************/
    void deleteItem(const ItemType& newItem);

/****************************
countNodes

Function: Counts the number of nodes in the BST
Preconditions: BST has been initialized.
Postconditions: returns the number of nodes in the BST
*****************************/
    int countNodes();

/****************************
preOrderTraversal

Function: Returns the preOder (Node, Left, Right) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
    vector<ItemType> preOrderTraversal();

/****************************
inOrderTraversal

Function: Returns the inOder (Left, Node, Right) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
    vector<ItemType> inOrderTraversal();

/****************************
postOrderTraversal

Function: returns the postOder (Left, Right, Node) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
    vector<ItemType> postOrderTraversal();

/********************
 isItemInTree

Function: Determines if a given Item is in tree.
Preconditions: BST has been initialized.
Postconditions: none
*****************************/

    bool isItemInTree(const ItemType& item);


private:
    struct TreeNode {
        ItemType data;
        TreeNode *left;
        TreeNode *right;
    };

    TreeNode * root;


    void insertItem(TreeNode*& t, const ItemType& newItem);
    void inOrderTraversal(TreeNode* t,vector<ItemType>& result) const;
    int countNodes(TreeNode* t) const;
    void deleteNode(TreeNode*& node);
    void makeEmpty(TreeNode*& t);
    void deleteItem(TreeNode*& t, const ItemType& newItem);
    void getPredecessor(TreeNode* t, ItemType& data);
    void preOrderTraversal(TreeNode* t,vector<ItemType>& result) const;
    void postOrderTraversal(TreeNode* t,vector<ItemType>& result) const;
    void copyTree(TreeNode*& copy, const TreeNode *originalTree);
    bool isItemInTree(TreeNode*& t, const ItemType& newItem);

};

/*******************************
//Function implementations
********************************/

template<class ItemType>
BST_312<ItemType>::BST_312 ()
{
    root = NULL;
}

template<class ItemType>
BST_312<ItemType>::BST_312(const BST_312 & src)
{
    copyTree(root, src.root);
}

template<class ItemType>
BST_312<ItemType>::~BST_312()
{
    makeEmpty();

}


template<class ItemType>
void BST_312<ItemType>::copyTree(TreeNode*& copy, const TreeNode* originalTree)
{
    if (originalTree == NULL)
        copy = NULL;
    else
    {
        copy = new TreeNode;
        copy->data = originalTree->data;

        copyTree(copy->left, originalTree->left);
        copyTree(copy->right, originalTree->right);
    }
}


template<class ItemType>
void BST_312 <ItemType>::deleteNode(TreeNode*& t)
{
    ItemType info;
    TreeNode *tempPtr;

    tempPtr = t;

    if (t->left == NULL)
    {
        t = t->right;
        delete tempPtr;
    }
    else if (t->right == NULL)
    {
        t = t->left;
        delete tempPtr;
    }
    else
    {
        getPredecessor(t->left, info);
        t->data = info;
        deleteItem(t->left, info);
    }
}



//find largest in left subtree
template<class ItemType>
void BST_312 <ItemType>::getPredecessor(TreeNode* t, ItemType& data)
{

    while (t->right != NULL)
        t = t->right;

    data = t->data;

}


template<class ItemType>
void BST_312 <ItemType>::deleteItem(TreeNode*& t, const ItemType& newItem)
{
    if (t == NULL)
        return;
    else if (newItem < t->data)
        deleteItem(t->left, newItem);
    else if (newItem > t->data)
        deleteItem(t->right, newItem);
    else
        deleteNode(t);
}


template<class ItemType>
void BST_312 <ItemType>::deleteItem(const ItemType& newItem)
{
    deleteItem(root, newItem);

}

template<class ItemType>
void BST_312 <ItemType>::makeEmpty(TreeNode*& t)
{
    //YOUR CODE GOES HERE
    if (t == NULL){
        return;
    }
    //check if t exists
    if(t->left != NULL){
        makeEmpty(t->left);
    }
    //check if left node, go to delete that if it exists
    if(t->right != NULL){
        makeEmpty(t->right);
    }
    //check if right node, go delete that if it exists
        delete t;
    //delete current node after looking if there other two

}

template<class ItemType>
void BST_312 <ItemType>::makeEmpty()
{
    makeEmpty(root);
    root = NULL;
}

template<class ItemType>
bool BST_312 <ItemType>::isEmpty() const
{
    return root == NULL;
}



template<class ItemType>
bool BST_312 <ItemType>::isFull() const
{
    try
    {
        TreeNode *temp = new TreeNode;
        delete temp;
        return false;
    }
    catch (std::bad_alloc)
    {
        return true;
    }

}


template<class ItemType>
void BST_312 <ItemType>::insertItem(TreeNode*& t, const ItemType& newItem) {

    //YOUR CODE GOES HERE
    if (t == NULL){
        TreeNode* newNode = new TreeNode;
        newNode->data = newItem;
        newNode->right = NULL;
        newNode->left = NULL;
        root = newNode;
        //if empty, make it root

    }
    else if((!isFull()) && (!isItemInTree(newItem))){
        //check full and if the item is already in tree

        if (newItem < t->data) {
            if(t->left != NULL){
                insertItem(t->left, newItem);
            }
                //if less, go down left path and check again if PTR not Null
            else{
                TreeNode* newNode = new TreeNode;
                newNode->data = newItem;
                newNode->right = NULL;
                newNode->left = NULL;
                t->left = newNode;
            }
        }
        else if (newItem > t->data){
            if(t->right != NULL){
                insertItem(t->right, newItem);
            }
                //if greater, go down right path and check again if PTR not Null
            else{
                TreeNode* newNode = new TreeNode;
                newNode->data = newItem;
                newNode->right = NULL;
                newNode->left = NULL;
                t->right = newNode;
            }
        }

    }

}

template<class ItemType>
void BST_312 <ItemType>::insertItem(const ItemType& newItem)
{
    //YOUR CODE GOES HERE
    insertItem(root, newItem);
}



template<class ItemType>
int BST_312 <ItemType>::countNodes(TreeNode* t) const
{
    //YOUR CODE GOES HERE
    if (t == NULL){
        return 0;
    }
    //no root, delete
    else{

        return (1 + countNodes(t->left) + countNodes(t -> right));

    }
    //1 + the nodes in left subtree and right subtree



}


template<class ItemType>
int BST_312 <ItemType>::countNodes()
{
    //YOUR CODE GOES HERE
    int cnt = countNodes(root);
    return cnt;
}

template<class ItemType>
void BST_312 <ItemType>::preOrderTraversal(TreeNode* t,vector<ItemType>& result) const
{
    //YOUR CODE GOES HERE
    if (t != NULL) {
        result.push_back(t->data);
        //step one, push value
        if (t->left != NULL) {
            preOrderTraversal(t->left, result);
        }
        //step two, if can go left, go left and return to step one
        if (t->right != NULL) {
            preOrderTraversal(t->right, result);
        }
        //step three, if can go right, go right and return to step one
    }
}


template<class ItemType>
vector<ItemType> BST_312 <ItemType>::preOrderTraversal()
{
    //YOUR CODE GOES HERE
    vector<ItemType> result;
    preOrderTraversal(root, result);
    return result;

}

template<class ItemType>
void BST_312 <ItemType>::inOrderTraversal(TreeNode* t,vector<ItemType>& result) const
{
    //YOUR CODE GOES HERE
    if (t != NULL) {
        if (t->left != NULL) {
            inOrderTraversal(t->left, result);
        }
        //step one, if can go left, go left and return to step one
        result.push_back(t->data);
        //step two, push value
        if (t->right != NULL) {
            inOrderTraversal(t->right, result);
        }
        //step three, if can go right, go right and return to step one
    }
}

template<class ItemType>
vector<ItemType> BST_312 <ItemType>::inOrderTraversal()
{
    //YOUR CODE GOES HERE
    vector<ItemType> result;
    inOrderTraversal(root, result);
    return result;
}

template<class ItemType>
void BST_312 <ItemType>::postOrderTraversal(TreeNode* t,vector<ItemType>& result) const
{

    //YOUR CODE GOES HERE
    if (t != NULL) {
        if (t->left != NULL) {
            postOrderTraversal(t->left, result);
        }
        //step one, if can go left, go left and return to step one
        if (t->right != NULL) {
            postOrderTraversal(t->right, result);
        }
        //step two, if can go right, go right and return to step one
        result.push_back(t->data);
        //step three, push value
    }
}

template<class ItemType>
vector<ItemType> BST_312 <ItemType>::postOrderTraversal()
{
    //YOUR CODE GOES HERE
    vector<ItemType> result;
    postOrderTraversal(root, result);
    return result;
}

template<class ItemType>
bool BST_312 <ItemType>::isItemInTree(const ItemType& item)
{
  //YOUR CODE GOES HERE
  return isItemInTree(root, item);
}

template<class ItemType>
bool BST_312 <ItemType>::isItemInTree(TreeNode*& t, const ItemType& item){

    if(t != NULL) {
        //check if t exists
        if (t->data == item) {
            return true;
        }
        if (t->data > item) {
            //if new item is less than, go left
            if (t->left != NULL) {
                isItemInTree(t->left, item);
            } else {
                //doesn't exist
                return false;
            }
        }
        if (t->data < item) {
            //if new item is greater than, go right
            if (t->right != NULL) {
                isItemInTree(t->right, item);
            } else {
                //doesn't exist
                return false;
            }
        }
    }
    else{
        return false;
    }

}
#endif

