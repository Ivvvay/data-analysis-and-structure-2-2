#include "BinaryTree.h"

BinaryTree::Node::Node(int key, Node *leftChild, Node *rightChild, int height) :
        _key(key), _leftChild(leftChild), _rightChild(rightChild), _height(height) {}

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

    //delete node;
}

BinaryTree::Node* BinaryTree::copyTree(Node* node) const {
    if (node == nullptr) return nullptr;
    Node* newNode = new Node(node->getKey());
    newNode->setLeftChild(copyTree(node->getLeftChild()));
    newNode->setRightChild(copyTree(node->getRightChild()));
    return newNode;
}

bool BinaryTree::isEmpty() const {
    return (_root == nullptr);
}

BinaryTree BinaryTree::copySubtree(int key) {
    return { rootOfCopySubtree(key) };
}

BinaryTree::Node* BinaryTree::rootOfCopySubtree(int key) {
    Node* node = findNodeByKey(key);
    if (!node)
        return nullptr;

    Node* newRoot = new Node(node->getKey());
    if (node->getLeftChild())
        newRoot->setLeftChild(copySubtree(node->getLeftChild()));
    if (node->getRightChild())
        newRoot->setRightChild(copySubtree(node->getRightChild()));

    return newRoot;
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

int BinaryTree::getMinKey() {
    std::vector<int> keys = getKeys();
    if (keys.empty()) throw std::logic_error("Tree is empty");
    auto min_element = std::min_element(keys.begin(), keys.end());
    return *min_element;
}

int BinaryTree::getMaxKey() {
    std::vector<int> keys = getKeys();
    if (keys.empty()) throw std::logic_error("Tree is empty");
    auto max_element = std::max_element(keys.begin(), keys.end());
    return *max_element;
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
        removeRoot();
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

bool BinaryTree::removeRoot() {
    if (_root == nullptr) {
        return false; // Дерево пустое
    }

    Node* oldRoot = getRoot();
    if (_root->getLeftChild() == nullptr && _root->getRightChild() == nullptr) {
        // Корень без потомков
        _root = nullptr;
    } else if (_root->getLeftChild() == nullptr) {
        // Корень справа имеет потомка
        _root = _root->getRightChild();
    } else if (_root->getRightChild() == nullptr) {
        // Корень слева имеет потомка
        _root = _root->getLeftChild();
    } else {
        // Корень имеет оба потомка
        Node* successor = getSuccessor(_root); // Находим преемника
        _root->setKey(successor->getKey()); // Ключ преемника копируется в корень
        removeNode(successor); // Удаляем преемника
    }
    return true;
}

BinaryTree::Node* BinaryTree::getSuccessor(Node* node) {
    if (node == nullptr) {
        return nullptr;
    }

    Node* current = node->getRightChild();
    while (current != nullptr && current->getLeftChild() != nullptr) {
        current = current->getLeftChild();
    }
    return current;
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

bool BinaryTree::isBalanced() const {
    return isBalanced(_root);
}

bool BinaryTree::isBalanced(const Node *node) const {
    if (node == nullptr)
        return true;

    int leftHeight = getHeight(node->getLeftChild());
    int rightHeight = getHeight(node->getRightChild());
    if (abs(leftHeight - rightHeight) > 1)
        return false;

    return isBalanced(node->getLeftChild()) && isBalanced(node->getRightChild());
}

int BinaryTree::getSum() {
    return getSum(_root);
}

int BinaryTree::getSum(const Node *node) {
    if (!node)
        return 0;

    return node->getKey() + getSum(node->getLeftChild()) + getSum(node->getRightChild());
}

int BinaryTree::getNodeLevel(int key) {
    return getNodeLevel(key, _root);
}

int BinaryTree::getNodeLevel(int key, const Node *node, int level) {
    if (!node)
        return -1;
    if (node->getKey() == key)
        return level;

    int leftLevel = getNodeLevel(key, node->getLeftChild(), level + 1);
    if (leftLevel != -1)
        return leftLevel;

    return getNodeLevel(key,node->getRightChild(), level + 1);
}

std::vector<int> BinaryTree::getKeys() const {
    std::vector<int> keys;
    inorderTraversal(_root, keys);
    return keys;
}

void BinaryTree::inorderTraversal(const Node *node, std::vector<int> &keys) const {
    if (!node) return;

    inorderTraversal(node->getLeftChild(), keys);
    keys.push_back(node->getKey());
    inorderTraversal(node->getRightChild(), keys);
}

void BinaryTree::printTree() const {
    printTree(_root, 0);
}

void BinaryTree::printTree(const Node *node, int indent) const {
    if (node == nullptr) return;

    if (node->getRightChild() != nullptr)
        printTree(node->getRightChild(), indent + 4);

    if (indent > 0)
        std::cout << std::setw(indent) << ' ';

    if (node->getRightChild() != nullptr)
        std::cout << " /\n" << std::setw(indent) << ' ';

    std::cout << node->getKey() << "\n ";

    if (node->getLeftChild() != nullptr) {
        std::cout << std::setw(indent) << ' ' << " \\\n";
        printTree(node->getLeftChild(), indent + 4);
    }
    /*if (node == nullptr) {
        return;
    }
    printTree(node->getRightChild(), indent + 1);
    for (int i = 0; i < indent; i++) {
        std::cout << "    ";
    }
    std::cout << node->getKey() << std::endl;
    printTree(node->getLeftChild(), indent + 1);*/
}

void BinaryTree::printLeaves() const {
    printLeaves(_root);
}

void BinaryTree::printLeaves(const Node *node) const {
    if (!node) return;

    if (node->getLeftChild() == nullptr && node->getRightChild() == nullptr)
        std::cout << node->getKey() << " ";
    else {
        printLeaves(node->getLeftChild());
        printLeaves(node->getRightChild());
    }
}

BinaryTree &BinaryTree::operator=(const BinaryTree &other) {
    if (this != &other) {
        clear();
        if (other.getRoot() != nullptr) {
            _root = new Node(other.getRoot()->getKey());
            copyNodes(_root, other._root);
        }
    }
    return *this;
}


void BinaryTree::copyNodes(Node* newNode, const Node* otherNode) const
{
    if (otherNode->getLeftChild() != nullptr) {
        newNode->setLeftChild(new Node(otherNode->getLeftChild()->getKey()));
        copyNodes(newNode->getLeftChild(), otherNode->getLeftChild());
    }

    if (otherNode->getRightChild() != nullptr) {
        newNode->setRightChild(new Node(otherNode->getRightChild()->getKey()));
        copyNodes(newNode->getRightChild(), otherNode->getRightChild());
    }
}