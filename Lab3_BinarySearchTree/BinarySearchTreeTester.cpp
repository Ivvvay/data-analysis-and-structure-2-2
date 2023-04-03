#include "BinarySearchTreeTester.h"

void BinarySearchTreeTester::test(const int size) {
    _maxSize = size;
    isBST();
}

void BinarySearchTreeTester::isBST() {
    int min = 0;
    int max = _maxSize;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(min, max);

    BinarySearchTree tree;
    for (int i = 0; i < _maxSize; ++i) {
        int key = dis(gen);
        tree.addNode(key);
    }

    assert(check_BST(tree.getRoot(), min, max));

    //Изменяем значение в одном из узлов, чтобы нарушить порядок
    tree.getRoot()->getRightChild()->setKey(-1);
    assert(!check_BST(tree.getRoot(), min, max));
}

bool BinarySearchTreeTester::check_BST(BinarySearchTree::Node* root, int minVal, int maxVal) {
    if (root == nullptr) {
        return true;
    }
    if (root->getKey() < minVal || root->getKey() > maxVal) {
        return false;
    }
    return check_BST(root->getLeftChild(), minVal, root->getKey() - 1) &&
           check_BST(root->getRightChild(), root->getKey(), maxVal);
}
