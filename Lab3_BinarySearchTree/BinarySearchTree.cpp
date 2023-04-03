#include "BinarySearchTree.h"

BinarySearchTree::BinarySearchTree() : BinaryTree() {}

BinarySearchTree::BinarySearchTree(const BinarySearchTree &other) : BinaryTree(other) {}

BinarySearchTree::BinarySearchTree(Node* newRoot) : BinaryTree(newRoot) {}

BinarySearchTree::~BinarySearchTree() = default;

BinarySearchTree BinarySearchTree::copySubtreeSearch(int key) {
    Node* node = findNodeByKey(key);
    if (!node)
        return BinarySearchTree();

    Node* newRoot = new Node(node->getKey());
    if (node->getLeftChild())
        newRoot->setLeftChild(copySubtree(node->getLeftChild()));
    if (node->getRightChild())
        newRoot->setRightChild(copySubtree(node->getRightChild()));

    return BinarySearchTree(newRoot);
}

BinaryTree::Node *BinarySearchTree::copySubtree(const BinaryTree::Node *node) const {
    return BinaryTree::copySubtree(node);
}

int BinarySearchTree::getMinKey() {
    if (_root == nullptr) {
        throw std::runtime_error("Tree is empty");
    }
    Node* current = _root;
    while (current->getLeftChild() != nullptr) {
        current = current->getLeftChild();
    }
    return current->getKey();
}

int BinarySearchTree::getMaxKey() {
    if (_root == nullptr) {
        throw std::runtime_error("Tree is empty");
    }
    Node* current = _root;
    while (current->getRightChild() != nullptr) {
        current = current->getRightChild();
    }
    return current->getKey();
}