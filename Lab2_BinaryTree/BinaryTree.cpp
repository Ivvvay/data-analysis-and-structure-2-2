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

BinaryTree::BinaryTree(Node* newRoot) : _root(copyTree(newRoot)) {}

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

void BinaryTree::deleteSubtree(int key) {
    Node* nodeToRemove = findNodeByKey(key);
    if (nodeToRemove) {
        deleteSubtree(nodeToRemove);
        removeNode(nodeToRemove);
    }
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

BinaryTree BinaryTree::copySubtree(int key) {
    Node* node = findNodeByKey(key);
    if (!node)
        return BinaryTree();

    Node* newRoot = new Node(node->getKey());
    if (node->getLeftChild())
        newRoot->setLeftChild(copySubtree(node->getLeftChild()));
    if (node->getRightChild())
        newRoot->setRightChild(copySubtree(node->getRightChild()));

    return BinaryTree(newRoot);
}

BinaryTree::Node* BinaryTree::copySubtree(const Node *node) const {
    Node* newNode = new Node(node->getKey());
    if (node->getLeftChild())
        newNode->setLeftChild(copySubtree(node->getLeftChild()));
    if (node->getRightChild())
        newNode->setRightChild(copySubtree(node->getRightChild()));

    return newNode;
}

int BinaryTree::getHeight() const {
    return getHeight(_root);
}

int BinaryTree::getHeight(const Node *node) const {
    if (!node) {
        return 0;
    }
    int leftHeight = getHeight(node->getLeftChild());
    int rightHeight = getHeight(node->getRightChild());
    return 1 + std::max(leftHeight, rightHeight);
}

int BinaryTree::getSize() const {
    return getSize(_root);
}

int BinaryTree::getSize(const Node *node) const {
    if (!node)
        return 0;
    return 1 + getSize(node->getLeftChild()) + getSize(node->getRightChild());
}

BinaryTree::Node *BinaryTree::addNode(Node* root, int key) {
    std::random_device rd;
    std::mt19937 gen(rd());
    if (!root) {
        root = new Node(key);
    } else if (gen() % 2) {
        root->setLeftChild(addNode(root->getLeftChild(), key));
    } else {
        root->setRightChild(addNode(root->getRightChild(), key));
    }
    return root;
}

BinaryTree::Node *BinaryTree::addNode(int key) {
    if (_root)
        return addNode(_root, key);
    else
        return _root = new Node(key);

}

bool BinaryTree::removeNode(int key) {
    Node* nodeToRemove = findNodeByKey(key);
    if (!nodeToRemove) {
        return false;
    }
    removeNode(nodeToRemove);
    return true;

}

void BinaryTree::removeNode(Node* node) {
    // случай, когда удаляемый узел - корень дерева
    if (node == _root) {
        delete _root;
        _root = nullptr;
        return;
    }

    Node* nodeParent = findParent(node, _root);
    if (nodeParent == nullptr) {
        // узел не найден
        return;
    }

    Node* replacementNode = nullptr;
    if (node->getLeftChild() == nullptr && node->getRightChild() == nullptr) {
        // случай 1: удаляемый узел - лист
        replacementNode = nullptr;
    } else if (node->getLeftChild() == nullptr) {
        // случай 2.1: удаляемый узел имеет только правого потомка
        replacementNode = node->getRightChild();
    } else if (node->getRightChild() == nullptr) {
        // случай 2.2: удаляемый узел имеет только левого потомка
        replacementNode = node->getLeftChild();
    } else {
        // случай 3: удаляемый узел имеет обоих потомков
        // найти наименьший узел в правом поддереве
        Node* minNode = node->getRightChild();
        while (minNode->getLeftChild() != nullptr) {
            minNode = minNode->getLeftChild();
        }
        replacementNode = minNode;
        // разрыв связи удаляемого узла с его предком
        Node* minNodeParent = findParent(minNode, _root);
        if (minNodeParent != node) {
            minNodeParent->setLeftChild(replacementNode->getRightChild());
            replacementNode->setRightChild(node->getRightChild());
        }
        replacementNode->setLeftChild(node->getLeftChild());
    }

    // удаление узла
    if (nodeParent->getLeftChild() == node) {
        nodeParent->setLeftChild(replacementNode);
    } else {
        nodeParent->setRightChild(replacementNode);
    }
    delete node;
}

BinaryTree::Node* BinaryTree::findNodeByKey(int key) {
    Node* nodeToRemove = findNodeByKey(key, _root);
    if (nodeToRemove == nullptr)
        return nullptr;
    return nodeToRemove;
}

BinaryTree::Node* BinaryTree::findNodeByKey(int key, Node* currentNode) {
    if (currentNode == nullptr)
        return nullptr;
    if (currentNode->getKey() == key)
        return currentNode;
    Node* leftResult = findNodeByKey(key, currentNode->getLeftChild());
    if (leftResult != nullptr)
        return leftResult;
    Node* rightResult = findNodeByKey(key, currentNode->getRightChild());
    if (rightResult != nullptr)
        return rightResult;
    return nullptr;
}

BinaryTree::Node* BinaryTree::findParent(Node* node, Node* current) {
    if (_root == node)
        return nullptr;

    if (current == nullptr)
        return nullptr;

    if (current->getLeftChild() == node || current->getRightChild() == node)
        return current;

    Node* parent = findParent(node, current->getLeftChild());
    if (parent != nullptr)
        return parent;

    parent = findParent(node, current->getRightChild());
    return parent;
}

bool BinaryTree::isBalanced() {
    return isBalanced(_root);
}

bool BinaryTree::isBalanced(const Node *node) {
    if (node == nullptr)
        return true;

    int leftHeight = getHeight(node->getLeftChild());
    int rightHeight = getHeight(node->getRightChild());
    if (abs(leftHeight - rightHeight) > 1)
        return false;

    int leftSize = getSize(node->getLeftChild());
    int rightSize = getSize(node->getRightChild());
    if (abs(leftSize - rightSize) > 1)
        return false;

    return isBalanced(node->getLeftChild()) && isBalanced(node->getRightChild());
}
