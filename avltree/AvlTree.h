#ifndef AVLTREE_LIBRARY_H
#define AVLTREE_LIBRARY_H

/*! \mainpage Overview
 *
 * \section authors_sec Projekt authors
 * <a href="https://github.com/walkmario">Mario Walk</a> and <a href="https://github.com/korbster">Korbinian Karl</a>
 *
 * \section intro_sec Introduction
 * Our task was to write a AVL balanced tree in C++. The public methods are:
 * insert (for adding a node to the tree),
 * remove (for removing it) and
 * search (for searching)
 *
 */

/**
 * @file AvlTree.h
 * @class AvlTree.cpp
 * @authors Korbinian Karl, Mario Walk
 * @copyright Korbinian Karl, Mario Walk
 * @date 13.01.2018
 * */

/**
 * The AvlTree class represents custom avl balanced trees.
 */
class AvlTree {
private:
    struct node {
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

    void add(const int key, AvlTree::node *currentNode);

    node *search(const int key, node *currentNode);

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

    /**
     * Test
     */
public:
    /**
     * Default deconstructor for avl trees.
     */
    ~AvlTree();

    /**
    * Adding a node.
    *
    * This method add the node with the parameter key to the tree.
    * Also it automatically balances the tree again at place and also on the path to the root, if needed.
    *
    * @param key - the key to be added to a tree
    */
    void add(const int key);

    /**
    * Searching for a node.
    *
    * This method searches for the node with the key specified as a parameter. Returns the node if it was found otherwise a nullptr.
    *
    * @param key - the value to be searched for
    * @return node - the node if it exsists in the tree, otherwise nullptr
    */
    node *search(const int key);

    /**
    * Removing a node.
    *
    * This method removes the node with the key specified as a parameter.
    * Also it automatically balances the tree again at place and also on the path to the root, if needed.
    *
    * @param key - the key to be removed from a tree
    */
    void remove(const int key);

    /**
     * Finding the symmetric successor.
     *
     * This method finds the symmetric successor of the node given as a parameter.
     *
     * @param node the root of the tree
     * @return the symmetric successor
     */
    friend node *findSymSucc(node *node);
};
#endif
