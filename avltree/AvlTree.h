#ifndef AVLTREE_LIBRARY_H
#define AVLTREE_LIBRARY_H

class AvlTree{
private:
    struct node{
        const int key;
        int balanceFactor;
        node *predecessor;
        node *leftSuccessor;
        node *rightSuccesor;

        node(const int, int, node *, node *, node *);
        ~node();


    };
    node *root = nullptr;

public:
    ~AvlTree();

};

#endif