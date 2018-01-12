#ifndef AVLTREE_LIBRARY_H
#define AVLTREE_LIBRARY_H

class AvlTree{
private:
    struct node{
        int key;
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

    void upOut(node *currentNode);
    void startUpIn(node *currentNode);
    void recursiveUpIn(node *currentNode);

    void rotateRight(node *currentNode);
    void rotateLeft(node *currentNode);

    void doublerotateLeftRight(node *currentNode);
    void doublerotateRightLeft(node *currentNode);

public:
    ~AvlTree();
    void add (const int key);
    node *search (const int key);
    void remove (const int key);
    void removeNodeWithoutSuccessors(node *);
    void removeNodeWithTwoSuccessors(node *);
    void removeNodeWithOneSuccessors(node *);
    friend node *findSymSucc(node *);
    friend int height(node *);
};

#endif