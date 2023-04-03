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

    int getMinKey() override;
    int getMaxKey() override;

    Node* addNode(int key) override;
    Node* addNode(Node* root, int key) override;

    bool removeNodeSearch(int key);
    Node* getSuccessor(Node* node);

    Node* findNodeByKey(int key) override;
    int getNodeLevel(int key) override;

    BinarySearchTree& operator=(const BinarySearchTree& other);
};


#endif //LAB3_BINARYSEARCHTREE_BINARYSEARCHTREE_H
