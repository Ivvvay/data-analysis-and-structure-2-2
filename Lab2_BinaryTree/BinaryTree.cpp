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