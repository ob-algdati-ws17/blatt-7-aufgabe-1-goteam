#ifndef AVLTREE_LIBRARY_H
#define AVLTREE_LIBRARY_H

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

public:
    ~AvlTree();
    void add (const int key);
    AvlTree::node *search (const int key);
    AvlTree::node *search (const int key, AvlTree::node *successor);
    void remove (const int key);

};

#endif