#ifndef LAB3_BINARYSEARCHTREE_BINARYSEARCHTREE_H
#define LAB3_BINARYSEARCHTREE_BINARYSEARCHTREE_H
#include "BinaryTree.h"

class BinarySearchTree : public BinaryTree {
    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree& other);
    explicit BinarySearchTree(Node* newRoot);
    ~BinarySearchTree() override;

    BinarySearchTree copySubtreeSearch(int key);
    Node* copySubtree(const Node* node) const override;
};


#endif //LAB3_BINARYSEARCHTREE_BINARYSEARCHTREE_H
