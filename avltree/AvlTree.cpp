#include "AvlTree.h"

AvlTree::node::node(const int k,
                    int bF,
                    AvlTree::node *p,
                    AvlTree::node *lS,
                    AvlTree::node *rS) : key(k),
                                         balanceFactor(bF),
                                         predecessor(p),
                                         leftSuccessor(lS),
                                         rightSuccesor(rS){
}

AvlTree::node::~node() {
    delete leftSuccessor;
    delete rightSuccesor;
}

AvlTree::~AvlTree() {
    delete root;
}
