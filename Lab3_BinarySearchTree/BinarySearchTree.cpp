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

BinaryTree::Node *BinarySearchTree::addNode(BinaryTree::Node *root, int key) {
    if (!root) {
        root = new Node(key);
    } else if (key < root->getKey()) {
        root->setLeftChild(addNode(root->getLeftChild(), key));
    } else {
        root->setRightChild(addNode(root->getRightChild(), key));
    }
    return root;
}

BinaryTree::Node *BinarySearchTree::addNode(int key) {
    if (_root)
        return addNode(_root, key);
    else
        return _root = new Node(key);
}

bool BinarySearchTree::removeNodeSearch(int key) {
    Node* parent = nullptr;
    Node* current = _root;
    bool isLeftChild = false;

    while (current != nullptr && current->getKey() != key) {
        parent = current;
        if (key < current->getKey()) {
            current = current->getLeftChild();
            isLeftChild = true;
        }
        else {
            current = current->getRightChild();
            isLeftChild = false;
        }
    }
    if (current == nullptr) {
        return false;
    }

    if (current->getLeftChild() == nullptr && current->getRightChild() == nullptr) {
        if (current == _root)
            _root = nullptr;
        else if (isLeftChild)
            parent->setLeftChild(nullptr);
        else
            parent->setRightChild(nullptr);
        delete current;
    } else if (current->getRightChild() == nullptr) {
        if (current == _root)
            _root = current->getLeftChild();
        else if (isLeftChild)
            parent->setRightChild(current->getLeftChild());
        else
            parent->setRightChild(current->getLeftChild());
        delete current;
    } else if (current->getLeftChild() == nullptr) {
        if (current == _root)
            _root = current->getRightChild();
        else if (isLeftChild)
            parent->setLeftChild(current->getRightChild());
        else
            parent->setRightChild(current->getRightChild());
        delete current;
    } else {
        Node* successor = getSuccessor(current);

        if (current == _root)
            _root = successor;
        else if (isLeftChild)
            parent->setLeftChild(successor);
        else
            parent->setRightChild(successor);

        successor->setLeftChild(current->getLeftChild());
        delete current;
    }

    return true;
}

BinarySearchTree::Node* BinarySearchTree::getSuccessor(Node* node) {
    Node* parent = node;
    Node* successor = node;
    Node* current = node->getRightChild();

    while (current != nullptr) {
        parent = successor;
        successor = current;
        current = current->getLeftChild();
    }

    if (successor != node->getRightChild()) {
        parent->setLeftChild(successor->getRightChild());
        successor->setRightChild(node->getRightChild());
    }

    return successor;
}