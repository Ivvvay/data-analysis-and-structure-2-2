#include "AVLtree.h"

AVLtree::AVLtree() : BinarySearchTree() {}

AVLtree::AVLtree(const AVLtree &other) : BinarySearchTree(other) {}

AVLtree::AVLtree(Node *newRoot) : BinarySearchTree(newRoot) {}

AVLtree AVLtree::copySubtree(int key) {
    Node* node = findNodeByKey(key);
    if (!node)
        return AVLtree();

    Node* newRoot = new Node(node->getKey());
    if (node->getLeftChild())
        newRoot->setLeftChild(copySubtree(node->getLeftChild()));
    if (node->getRightChild())
        newRoot->setRightChild(copySubtree(node->getRightChild()));

    return AVLtree(newRoot);
}

BinaryTree::Node *AVLtree::copySubtree(const Node *node) const {
    return BinarySearchTree::copySubtree(node);
}