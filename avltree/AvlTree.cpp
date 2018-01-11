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
            startUpIn(currentNode);
        } else{
            add(key, currentNode->leftSuccessor);
        }
    }

    if (key > currentNode->key){
        if (currentNode->rightSuccessor == nullptr){
            auto toInsert = new node(key, currentNode);
            currentNode->rightSuccessor = toInsert;
            startUpIn(currentNode);
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

void AvlTree::startUpIn(AvlTree::node *currentNode) {
    if(currentNode->balanceFactor == 0){
        if(currentNode->leftSuccessor != nullptr){
            currentNode->balanceFactor = -1;
        }
        if(currentNode->rightSuccessor != nullptr){
            currentNode->balanceFactor = 1;
        }
        //stop recursion at root
        if(currentNode->predecessor != nullptr){
            recursiveUpIn(currentNode->predecessor);
        }
    }
}

void AvlTree::recursiveUpIn(AvlTree::node *currentNode) {
    if( currentNode->predecessor != nullptr){
        node *predecessor = currentNode->predecessor;

        //left side
        if(currentNode == predecessor->leftSuccessor){
            // check if grew
            if(currentNode->balanceFactor != 0){
                switch(predecessor->balanceFactor){
                    case -1: //TODO: Rotation
                        break;
                    case  0: predecessor->balanceFactor = -1;
                        recursiveUpIn(predecessor);
                        break;
                    case  1: predecessor->balanceFactor = 0;
                        recursiveUpIn(predecessor);
                        break;
                    default:
                        break;
                }
            }
        }

        //right side
        if(currentNode == predecessor->rightSuccessor){
            // check if grew
            if(currentNode->balanceFactor != 0){
                switch(predecessor->balanceFactor){
                    case -1: predecessor->balanceFactor = 0;
                        recursiveUpIn(predecessor);
                        break;
                    case  0: predecessor->balanceFactor = 1;
                        recursiveUpIn(predecessor);
                        break;
                    case  1: //TODO: Rotation
                        break;
                    default:
                        break;
                }
            }
        }
    }
}

void AvlTree::remove(const int value) {

}

void AvlTree::upOut(AvlTree::node *currentNode) {

}

AvlTree::node *findSymSucc(AvlTree::node *node) {
    if (node->rightSuccessor != nullptr) {
        auto symSucc = node->rightSuccessor;
        while (symSucc->leftSuccessor != nullptr) {
            symSucc = symSucc->leftSuccessor;
        }
        return symSucc;
    }
    return nullptr;
}

