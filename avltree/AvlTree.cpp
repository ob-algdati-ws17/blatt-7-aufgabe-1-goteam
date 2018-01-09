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
    } else {
        add(key, root);
    }
}

void AvlTree::add(const int key, AvlTree::node *currentNode) {
    if (key < currentNode->key){
        if (currentNode->leftSuccessor == nullptr){
            auto toInsert = new node(key, currentNode);
            currentNode->leftSuccessor = toInsert;
        } else{
            add(key, currentNode->leftSuccessor);
        }
    }

    if (key > currentNode->key){
        if (currentNode->rightSuccessor == nullptr){
            auto toInsert = new node(key, currentNode);
            currentNode->rightSuccessor = toInsert;
        } else{
            add(key, currentNode->rightSuccessor);
        }
    }
}

AvlTree::node *AvlTree::search(const int key) {
    return search(key, root);
}

AvlTree::node *AvlTree::search(const int key, AvlTree::node *currentNode) {
    if (currentNode == nullptr){
        return nullptr;
    }
    if (key == currentNode->key){
        return currentNode;
    }
    if (key < currentNode->key){
        return search(key, currentNode->leftSuccessor);
    }
    if (key > currentNode->key){
        return search(key, currentNode->rightSuccessor);
    }
    return nullptr;
}

void AvlTree::remove(const int key) {

}