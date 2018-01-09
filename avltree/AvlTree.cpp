#include "AvlTree.h"

AvlTree::node::node(const int k,
                    int bF,
                    AvlTree::node *p,
                    AvlTree::node *lS,
                    AvlTree::node *rS) : key(k),
                                         balanceFactor(bF),
                                         predecessor(p),
                                         leftSuccessor(lS),
                                         rightSuccessor(rS){
}

AvlTree::node::node(const int k,
                    AvlTree::node * p) : key(k),
                                         balanceFactor(0),
                                         predecessor(p),
                                         leftSuccessor(nullptr),
                                         rightSuccessor(nullptr) {
}

AvlTree::node::~node() {
    delete leftSuccessor;
    delete rightSuccessor;
}

AvlTree::~AvlTree() {
    delete root;
}

void AvlTree::add(const int key) {
    if (root == nullptr){
        root = new node(key, nullptr);
    }

    if (key < root->key){
        if (root->leftSuccessor == nullptr){
            auto toInsert = new node(key, root);
            root->leftSuccessor = toInsert;
        } else{
            add(key, root->leftSuccessor);
        }
    }

    if (key > root->key){
        if (root->rightSuccessor == nullptr){
            auto toInsert = new node(key, root);
            root->rightSuccessor = toInsert;
        } else{
            add(key, root->rightSuccessor);
        }
    }
}

void AvlTree::add(const int key, AvlTree::node *successor) {
    if (key < successor->key){
        if (successor->leftSuccessor == nullptr){
            auto toInsert = new node(key, successor);
            successor->leftSuccessor = toInsert;
        } else{
            add(key, successor->leftSuccessor);
        }
    }

    if (key > successor->key){
        if (successor->rightSuccessor == nullptr){
            auto toInsert = new node(key, successor);
            successor->rightSuccessor = toInsert;
        } else{
            add(key, successor->rightSuccessor);
        }
    }
}

AvlTree::node *AvlTree::search(const int key) {
    if (root == nullptr){
        return nullptr;
    }
    if (key == root->key){
        return root;
    }
    if (key < root->key){
        return search(key, root->leftSuccessor);
    }
    if (key > root->key){
        return search(key, root->rightSuccessor);
    }
    return nullptr;
}

AvlTree::node *AvlTree::search(const int key, AvlTree::node *successor) {
    if (successor == nullptr){
        return nullptr;
    }
    if (key == successor->key){
        return successor;
    }
    if (key < successor->key){
        return search(key, successor->leftSuccessor);
    }
    if (key > successor->key){
        return search(key, successor->rightSuccessor);
    }
    return nullptr;
}

void AvlTree::remove(const int key) {

}