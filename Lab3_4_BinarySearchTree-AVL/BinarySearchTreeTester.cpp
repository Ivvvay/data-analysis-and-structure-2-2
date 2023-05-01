#include "BinarySearchTreeTester.h"

void BinarySearchTreeTester::test(const int size) {
    _maxSize = size;
    isBST();
    copySubtreeSearch();
    getMinMaxKey();
    remove();
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

void BinarySearchTreeTester::copySubtreeSearch() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, _maxSize-1);

    BinarySearchTree tree;
    for (int i = 0; i < _maxSize; i++)
        tree.addNode(i);

    int copySubtreeSearchKey = dis(gen);
    BinarySearchTree subTree = tree.copySubtreeSearch(copySubtreeSearchKey);
    check_copySubtreeSearch(subTree, tree, copySubtreeSearchKey);
}

void BinarySearchTreeTester::check_copySubtreeSearch(BinarySearchTree &subTree, BinarySearchTree &tree, const int key) {
    assert(subTree.getHeight() + key == tree.getHeight());
}

void BinarySearchTreeTester::getMinMaxKey() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, _maxSize);

    BinarySearchTree tree;
    for (int i = 0; i <= _maxSize; i++) {
        int key = dis(gen);
        tree.addNode(key);
    }

    int min = tree.getMinKey();
    int max = tree.getMaxKey();

    check_getMinMaxKey(tree, min, max);
}

void BinarySearchTreeTester::check_getMinMaxKey(BinarySearchTree &tree, int min, int max) {
    std::vector<int> keys = tree.getKeys();
    auto min_element = std::min_element(keys.begin(), keys.end());
    auto max_element = std::max_element(keys.begin(), keys.end());

    assert(min == *min_element && max == *max_element);
}

void BinarySearchTreeTester::remove() {
    std::random_device rd;
    std::mt19937 gen(rd());

    int invalidKey = -1;
    std::vector<int> nodeKeys;

    BinarySearchTree tree;
    tree.removeNodeSearch(invalidKey);

    for (int i = 0 ; i < _maxSize; ++i) {
        nodeKeys.push_back(i);
        tree.addNode(i);
    }
    //std::cout << "tree.getSize()=" << tree.getSize() << ", nodeKeys.size()=" << nodeKeys.size() << std::endl;
    //tree.printTree();

    while (!nodeKeys.empty()) {
        std::uniform_int_distribution<int> distribution(0, nodeKeys.size() - 1);
        int removedNodeIndex = distribution(gen);
        int removeNodeKey = nodeKeys[removedNodeIndex];
        //std::cout << "--------" << removeNodeKey << "--------" << std::endl;

        tree.removeNodeSearch(removeNodeKey);
        if (removedNodeIndex == 0 && tree.getSize() == 0)
            nodeKeys.clear();
        else
            nodeKeys.erase(nodeKeys.begin() + removedNodeIndex);
        //std::cout << "tree.getSize()=" << tree.getSize() << ", nodeKeys.size()=" << nodeKeys.size() << std::endl;
        check_remove(tree, nodeKeys.size());

        //tree.printTree();
    }
    /*std::cout << "----------------" << std::endl;
    tree.printTree();*/

    tree.removeNodeSearch(invalidKey);
    check_remove(tree, nodeKeys.size());
}

void BinarySearchTreeTester::check_remove(const BinaryTree &tree, const int size) {
    assert(tree.getSize() == size);
}