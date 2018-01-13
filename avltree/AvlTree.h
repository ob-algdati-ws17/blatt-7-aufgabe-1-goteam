#ifndef AVLTREE_LIBRARY_H
#define AVLTREE_LIBRARY_H

/**
 * @file AvlTree.h
 * @class AvlTree.cpp
 * @authors Korbinian Karl, Mario Walk
 * @copyright Korbinian Karl, Mario Walk
 * @date 13.01.2018
 * */

class AvlTree{
private:
    struct node{
        const int key;
        int balanceFactor;
        node *predecessor;
        node *leftSuccessor;
        node *rightSuccessor;

        node(const int, int, node *, node *, node *);
        node(const int, node *);
        ~node();

    };
    node *root = nullptr;

    void add (const int key, AvlTree::node *currentNode);
    node *search (const int key, node *currentNode);

    void startUpOut(node *currentNode);
    void upOut(node *currentNode);
    void startUpIn(node *currentNode);
    void recursiveUpIn(node *currentNode);

    void rotateRight(node *currentNode);
    void rotateLeft(node *currentNode);

    void doublerotateLeftRight(node *currentNode);
    void doublerotateRightLeft(node *currentNode);

    void removeNodeWithoutSuccessors(node *);
    void removeNodeWithTwoSuccessors(node *);
    void removeNodeWithOneSuccessor(node *);

public:
    ~AvlTree();

    /**
    * @param key
    */
    void add (const int key);

    /**
    * @param key
    * @return node
    */
    node *search (const int key);

    /**
    * @param key
    */
    void remove (const int key);
    friend node *findSymSucc(node *);
    friend int height(node *);
};

#endif