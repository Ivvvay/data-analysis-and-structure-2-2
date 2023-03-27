#include "BinaryTree.h"

BinaryTree::Node::Node(int key, Node *leftChild, Node *rightChild) :
        _key(key), _leftChild(leftChild), _rightChild(rightChild) {}

int BinaryTree::Node::getKey() const {
    return _key;
}

void BinaryTree::Node::setKey(int key) {
    _key = key;
}

int BinaryTree::Node::getNumChildren() const {
    int count = 0;
    if (_leftChild)
        count++;
    if (_rightChild)
        count++;
    return count;
}

BinaryTree::Node *BinaryTree::Node::getLeftChild() const {
    return _leftChild;
}

BinaryTree::Node *BinaryTree::Node::getRightChild() const {
    return _rightChild;
}

void BinaryTree::Node::setLeftChild(Node *leftChild) {
    _leftChild = leftChild;
}

void BinaryTree::Node::setRightChild(Node *rightChild) {
    _rightChild = rightChild;
}

BinaryTree::BinaryTree() : _root(nullptr) {}

BinaryTree::BinaryTree(const BinaryTree &other) : _root(copyTree(other._root)) {}

BinaryTree::~BinaryTree() {
    clear();
}

const BinaryTree::Node *BinaryTree::getRoot() const {
    return _root;
}

BinaryTree::Node *BinaryTree::getRoot() {
    return _root;
}

void BinaryTree::clear() {
    deleteSubtree(_root);
    _root = nullptr;
}

void BinaryTree::deleteSubtree(Node *node) {
    if (node == nullptr)
        return;

    deleteSubtree(node->getLeftChild());
    deleteSubtree(node->getRightChild());
    node->setLeftChild(nullptr);
    node->setRightChild(nullptr);
}

BinaryTree::Node* BinaryTree::copyTree(Node* node) const {
    if (node == nullptr) return nullptr;
    Node* newNode = new Node(node->getKey());
    newNode->setLeftChild(copyTree(node->getLeftChild()));
    newNode->setRightChild(copyTree(node->getRightChild()));
    return newNode;
}

bool BinaryTree::isEmpty() const {
    return !_root;
}

BinaryTree::Node* BinaryTree::copySubtree(const Node *node) const {
    Node* newNode = new Node(node->getKey());
    if (node->getLeftChild())
        newNode->setLeftChild(copySubtree(node->getLeftChild()));
    if (node->getRightChild())
        newNode->setRightChild(copySubtree(node->getRightChild()));

    return newNode;
}
