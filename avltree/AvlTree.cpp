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
            recursiveUpIn(currentNode);
        }
    } else {
        currentNode->balanceFactor = 0;
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
        if(currentNode == predecessor->rightSuccessor){
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

            // both successors are leafs
            if (nodeToDelete->leftSuccessor == nullptr && nodeToDelete->rightSuccessor == nullptr) {
                // get predecessor of the node to delete
                auto p = nodeToDelete->predecessor;
                // if the note to delete is the left successor of p, set p's left successor = nullptr
                if (nodeToDelete == p->leftSuccessor) {
                    p->leftSuccessor = nullptr;
                    auto q = p->rightSuccessor;
                    // the height of p was reduces by 1
                    if (q->balanceFactor == 0) {
                        //todo: upout
                    } else if (q->balanceFactor == 2) {
                        //todo:  rotation or double rotation to balance tree with root p
                        //todo: if new root of split tree has balance 0 -> upout
                    }
                } else {
                    p->rightSuccessor = nullptr;
                    auto q = p->leftSuccessor;
                    // the height of p was reduces by 1
                    if (q->balanceFactor == 0) {
                        //todo: upout
                    } else if (q->balanceFactor == 2) {
                        //todo:  rotation or double rotation to balance tree with root p
                        //todo: if new root of split tree has balance 0 -> upout
                    }
                }
                // both successors are nodes
            } else if (nodeToDelete->leftSuccessor != nullptr && nodeToDelete->rightSuccessor != nullptr) {
                auto p = nodeToDelete;
                auto symSucKey = findSymSucc(nodeToDelete);
                //todo: replace key of p with symSucKey
                //todo: delete sumSuc like in the cases before

                // one successor leaf and the other node
            } else {
                auto p = nodeToDelete;
                if (p->leftSuccessor != nullptr) {
                    auto q = p->leftSuccessor;
                    //todo: replace key of p with key of q. replace q with a leaf
                    //todo: upout
                } else {
                    auto q = p->rightSuccessor;
                    //todo: replace key of p with key of q. replace q with a leaf
                    //todo: upout
                }

            }

        }
    }
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



