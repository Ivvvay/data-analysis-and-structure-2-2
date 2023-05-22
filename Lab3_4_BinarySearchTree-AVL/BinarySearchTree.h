#ifndef LAB3_BINARYSEARCHTREE_BINARYSEARCHTREE_H
#define LAB3_BINARYSEARCHTREE_BINARYSEARCHTREE_H
#include "BinaryTree.h"

class BinarySearchTree : public BinaryTree {
public:
    using BinaryTree::Node;

    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree& other);
    explicit BinarySearchTree(Node* newRoot);
    ~BinarySearchTree() override = default;

    BinarySearchTree copySubtree(int key);
    Node* copySubtree(const Node* node) const override;

    int getMinKey() override;
    int getMaxKey() override;

    Node* addNode(int key) override;
    Node* addNode(Node* root, int key) override;

    bool removeNode(int key) override;
    Node* getSuccessor(Node* node) override;

    Node* findNodeByKey(int key) override;
    int getNodeLevel(int key) override;

    BinarySearchTree& operator=(const BinarySearchTree& other) = default;
};


#endif //LAB3_BINARYSEARCHTREE_BINARYSEARCHTREE_H
