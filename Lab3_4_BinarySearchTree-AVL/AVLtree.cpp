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

BinaryTree::Node *AVLtree::addNode(int key) {
    _root = addNode(_root, key);
}

BinaryTree::Node *AVLtree::addNode(Node *root, int key) {
    if (!root) {
        return new Node(key);
    }
    if (key < root->getKey()) {
        root->setLeftChild(addNode(root->getLeftChild(), key));
    } else {
        root->setRightChild(addNode(root->getRightChild(), key));
    }
    root = balanceNode(root);
    return root;
}

bool AVLtree::removeNode(int key) {
    if (!_root)
        return false;

    bool result = false;
    _root = removeNode(_root, key, result);
    return result;
}

BinaryTree::Node *AVLtree::removeNode(Node *root, int key, bool &result) {
    if (!root) {
        return nullptr;
    }
    if (key < root->getKey()) {
        root->setLeftChild(removeNode(root->getLeftChild(), key, result));
    }
    else if (key > root->getKey()) {
        root->setRightChild(removeNode(root->getRightChild(), key, result));
    } else {
        Node* left = root->getLeftChild();
        Node* right = root->getRightChild();
        if (right == nullptr) {
            delete root;
            return left;
        }
        Node* minNode = findMin(right);
        minNode->setRightChild(removeMin(right));
        minNode->setLeftChild(left);
        delete root;
        root = balanceNode(minNode);
        result = true;
    }
    root = balanceNode(root);
    return root;
}

BinaryTree::Node *AVLtree::balanceNode(Node *node) {
    if (node == nullptr) {
        return nullptr;
    }
    int balanceFactor = getBalanceFactor(node);
    if (balanceFactor == 2) {
        if (getBalanceFactor(node->getLeftChild()) < 0) {
            node->setLeftChild(leftRotate(node->getLeftChild()));
        }
        node = rightRotate(node);
    }
    else if (balanceFactor == -2) {
        if (getBalanceFactor(node->getRightChild()) > 0) {
            node->setRightChild(rightRotate(node->getRightChild()));
        }
        node = leftRotate(node);
    }
    return node;
}

int AVLtree::getBalanceFactor(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    int leftHeight = getHeight(node->getLeftChild());
    int rightHeight = getHeight(node->getRightChild());
    return leftHeight - rightHeight;
}

BinaryTree::Node *AVLtree::rightRotate(Node *node) {
    Node* newRoot = node->getLeftChild();
    node->setLeftChild(newRoot->getRightChild());
    newRoot->setRightChild(node);

    node->_height = 1 + std::max(getHeight(node->getLeftChild()), getHeight(node->getRightChild()));
    newRoot->_height = 1 + std::max(getHeight(newRoot->getLeftChild()), getHeight(newRoot->getRightChild()));

    return newRoot;
}

BinaryTree::Node *AVLtree::leftRotate(Node *node) {
    Node* newRoot = node->getRightChild();
    node->setRightChild(newRoot->getLeftChild());
    newRoot->setLeftChild(node);

    node->_height = 1 + std::max(getHeight(node->getLeftChild()), getHeight(node->getRightChild()));
    newRoot->_height = 1 + std::max(getHeight(newRoot->getLeftChild()), getHeight(newRoot->getRightChild()));

    return newRoot;
}

BinaryTree::Node *AVLtree::findMin(Node *node) {
    while (node->getLeftChild() != nullptr) {
        node = node->getLeftChild();
    }
    return node;
}

BinaryTree::Node *AVLtree::removeMin(Node *node) {
    if (node->getLeftChild() == nullptr) {
        return node->getRightChild();
    }
    node->setLeftChild(removeMin(node->getLeftChild()));
    node = balanceNode(node);
    return node;
}