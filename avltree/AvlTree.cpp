#include <algorithm>
#include "AvlTree.h"

AvlTree::node::node(const int k,
                    int bF,
                    AvlTree::node *p,
                    AvlTree::node *lS,
                    AvlTree::node *rS) : key(k),
                                         balanceFactor(bF),
                                         predecessor(p),
                                         leftSuccessor(lS),
                                         rightSuccessor(rS) {
}

AvlTree::node::node(const int k,
                    AvlTree::node *p) : key(k),
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
    if (root == nullptr) {
        root = new node(key, nullptr);
    } else {
        add(key, root);
    }
}

void AvlTree::add(const int key, AvlTree::node *currentNode) {
    if (key < currentNode->key) {
        if (currentNode->leftSuccessor == nullptr) {
            auto toInsert = new node(key, currentNode);
            currentNode->leftSuccessor = toInsert;
            startUpIn(currentNode);
        } else {
            add(key, currentNode->leftSuccessor);
        }
    }

    if (key > currentNode->key) {
        if (currentNode->rightSuccessor == nullptr) {
            auto toInsert = new node(key, currentNode);
            currentNode->rightSuccessor = toInsert;
            startUpIn(currentNode);
        } else {
            add(key, currentNode->rightSuccessor);
        }
    }
}

AvlTree::node *AvlTree::search(const int key) {
    return search(key, root);
}

AvlTree::node *AvlTree::search(const int key, AvlTree::node *currentNode) {
    if (currentNode == nullptr) {
        return nullptr;
    }
    if (key == currentNode->key) {
        return currentNode;
    }
    if (key < currentNode->key) {
        return search(key, currentNode->leftSuccessor);
    }
    if (key > currentNode->key) {
        return search(key, currentNode->rightSuccessor);
    }
    return nullptr;
}

void AvlTree::startUpIn(AvlTree::node *currentNode) {
    if (currentNode->balanceFactor == 0) {
        if (currentNode->leftSuccessor != nullptr) {
            currentNode->balanceFactor = -1;
        }
        if (currentNode->rightSuccessor != nullptr) {
            currentNode->balanceFactor = 1;
        }
        //stop recursion at root
        if(currentNode->predecessor != nullptr){
            recursiveUpIn(currentNode);
        }
    } else {
        currentNode->balanceFactor = 0;
    }
}

void AvlTree::recursiveUpIn(AvlTree::node *currentNode) {
    if (currentNode->predecessor != nullptr) {
        node *predecessor = currentNode->predecessor;

        //left side
        if (currentNode == predecessor->leftSuccessor) {
            // check if grew
            if(currentNode->balanceFactor != 0){
                switch(predecessor->balanceFactor){
                    case -1:
                        if(currentNode->balanceFactor == -1){
                            rotateRight(currentNode);
                        }
                        if(currentNode->balanceFactor == 1){
                            doublerotateLeftRight(currentNode);
                        }
                        break;
                    case  0:
                        predecessor->balanceFactor = -1;
                        recursiveUpIn(predecessor);
                        break;
                    case  1:
                        predecessor->balanceFactor = 0;
                        recursiveUpIn(predecessor);
                        break;
                    default:
                        break;
                }
            }
        }

        //right side
        if (currentNode == predecessor->rightSuccessor) {
            // check if grew
            if(currentNode->balanceFactor != 0){
                switch(predecessor->balanceFactor){
                    case -1:
                        predecessor->balanceFactor = 0;
                        recursiveUpIn(predecessor);
                        break;
                    case  0:
                        predecessor->balanceFactor = 1;
                        recursiveUpIn(predecessor);
                        break;
                    case  1:
                        if(currentNode->balanceFactor == 1){
                            rotateLeft(currentNode);
                        }
                        if(currentNode->balanceFactor == -1){
                            doublerotateRightLeft(currentNode);
                        }
                        break;
                    default:
                        break;
                }
            }
        }
    }
}


void AvlTree::remove(const int value) {
    if (root != nullptr) {
        auto nodeToDelete = search(value);
        if (nodeToDelete != nullptr) {
            // CASE 1: Both successors of the node to delete are leafs
            if (nodeToDelete->leftSuccessor == nullptr && nodeToDelete->rightSuccessor == nullptr) {
                removeNodeWithoutSuccessors(nodeToDelete);
            } else if (nodeToDelete->leftSuccessor != nullptr && nodeToDelete->rightSuccessor != nullptr) {
                removeNodeWithTwoSuccessors(nodeToDelete);
            } else {
                removeNodeWithOneSuccessors(nodeToDelete);
            }
        }
    }
}

void AvlTree::removeNodeWithoutSuccessors(AvlTree::node *nodeToDelete) {
    if (nodeToDelete != root) {
        auto p = nodeToDelete->predecessor;
        if (nodeToDelete == p->leftSuccessor) {
            auto q =p->rightSuccessor;
            delete nodeToDelete;
            auto qHeight = height(q);
            switch (qHeight) {
                case 0:
                    p->balanceFactor = 0;
                    upOut(p);
                    break;
                case 1:
                    p->balanceFactor = 1;
                    break;

                case 2:

                    break;

                default:
                    break;
            }

        } else {
            auto q =p->leftSuccessor;
            delete nodeToDelete;
            auto qHeight = height(q);
            switch (qHeight) {
                case 0:
                    p->balanceFactor = 0;
                    upOut(p);
                    break;
                case 1:
                    p->balanceFactor = -1;
                    break;

                case 2:

                    break;

                default:
                    break;
            }
        }
    } else {
        delete root;
    }
}

void AvlTree::removeNodeWithTwoSuccessors(AvlTree::node *nodeToDelete) {

}

void AvlTree::removeNodeWithOneSuccessors(AvlTree::node *nodeToDelete) {
    node* predecessor = nodeToDelete->predecessor;
    node* successor = nullptr;
    if(nodeToDelete->leftSuccessor != nullptr){
        successor = nodeToDelete->leftSuccessor;

    }else if(nodeToDelete->rightSuccessor != nullptr){
        successor = nodeToDelete->rightSuccessor;
    }

    if(successor != nullptr){
        successor->predecessor = predecessor;

        if(predecessor->leftSuccessor == nodeToDelete){
            predecessor->leftSuccessor = successor;
        } else if(predecessor->rightSuccessor == nodeToDelete){
            predecessor->rightSuccessor = successor;
        }
    }
}

void AvlTree::upOut(AvlTree::node *currentNode) {
    auto p = currentNode;
    auto father = p->predecessor;
    if (p->balanceFactor == 0) {
        if (father->leftSuccessor == p) {
            if (father->balanceFactor == -1) {
                father->balanceFactor = 0;
                upOut(father);
            } else if (father->balanceFactor == 0) {
                father->balanceFactor = 1;
                return;
            } else if(father->balanceFactor == +1) {
                auto q = father->rightSuccessor;
                if (q->balanceFactor == 0) {

                } else if (q->balanceFactor == +1) {

                } else if (q->balanceFactor == -1) {

                }
            }
        } else if (father->rightSuccessor == p) {

        }
    }
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

void AvlTree::rotateRight(AvlTree::node *currentNode) {
    node* predecessor = currentNode->predecessor;

    if(predecessor == root){
        root = currentNode;
        currentNode->predecessor = nullptr;
    } else {
        node* prePredecessor = predecessor->predecessor;

        if(predecessor == prePredecessor->leftSuccessor){
            prePredecessor->leftSuccessor = currentNode;
            currentNode->predecessor = prePredecessor;
        }
        if(predecessor == prePredecessor->rightSuccessor){
            prePredecessor->rightSuccessor = currentNode;
            currentNode->predecessor = prePredecessor;
        }
    }
    currentNode->balanceFactor = 0;

    currentNode->rightSuccessor = predecessor;
    predecessor->predecessor = currentNode;

    predecessor->leftSuccessor = nullptr;
    predecessor->balanceFactor = 0;
}

void AvlTree::rotateLeft(AvlTree::node *currentNode) {
    node* predecessor = currentNode->predecessor;

    if(predecessor == root){
        root = currentNode;
        currentNode->predecessor = nullptr;
    } else {
        node* prePredecessor = predecessor->predecessor;

        if(predecessor == prePredecessor->rightSuccessor){
            prePredecessor->rightSuccessor = currentNode;
            currentNode->predecessor = prePredecessor;
        }
        if(predecessor == prePredecessor->leftSuccessor){
            prePredecessor->leftSuccessor = currentNode;
            currentNode->predecessor = prePredecessor;
        }
    }
    currentNode->balanceFactor = 0;

    currentNode->leftSuccessor = predecessor;
    predecessor->predecessor = currentNode;

    predecessor->rightSuccessor = nullptr;
    predecessor->balanceFactor = 0;
}

void AvlTree::doublerotateLeftRight(AvlTree::node *currentNode) {
    rotateLeft(currentNode->rightSuccessor);
    rotateRight(currentNode->predecessor);
}

void AvlTree::doublerotateRightLeft(AvlTree::node *currentNode) {
    rotateRight(currentNode->leftSuccessor);
    rotateLeft(currentNode->predecessor);
}

int height(AvlTree::node *node) {
    if (node != nullptr) {
        return 1 + std::max(height(node->leftSuccessor),height(node->rightSuccessor));
    }
    return -1;
}











