#include "AVLtester.h"

void AVLtester::test(const int size) {
    _maxSize = size;
    addAndCount();
    destructor();
    assign();
    remove();
    clear();
    height();
}

BinaryTree *AVLtester::allocateTree() {
    return new AVLtree;
}

void AVLtester::check_addAndCount(const BinaryTree &tree, const int size) {
    BinarySearchTreeTester::check_addAndCount(tree, size);
    isBST(tree);
    assert(tree.isBalanced());
}

void AVLtester::check_assign(const BinaryTree *tree1, const BinaryTree *tree2) {
    BinarySearchTreeTester::check_assign(tree1, tree2);
    isBST(*tree1);
    isBST(*tree2);
    assert(tree1->isBalanced());
    assert(tree2->isBalanced());
}

void AVLtester::check_remove(const BinaryTree &tree, const int size) {
    BinarySearchTreeTester::check_remove(tree, size);
    isBST(tree);
    assert(tree.isBalanced());
}

void AVLtester::check_clear(const BinaryTree &tree) {
    BinarySearchTreeTester::check_clear(tree);
    isBST(tree);
    assert(tree.isBalanced());
}

/*void AVLtester::isAVL() {
    int min = 0;
    int max = _maxSize;
    std::random_device rd;
    std::mt19937 gen(rd());

    std::vector<int> nodeKeys;

    for (int i = 0 ; i < _maxSize; ++i) {
        nodeKeys.push_back(i);
    }

    AVLtree tree;
    for (int i = 0; i < _maxSize; ++i) {
        std::uniform_int_distribution<int> dis(0, nodeKeys.size() - 1);
        int keyIndex = dis(gen);
        int key = nodeKeys[keyIndex];
        nodeKeys.erase(nodeKeys.begin() + keyIndex);
        tree.addNode(key);
        isBST(tree);
        assert(tree.isBalanced());
    }
}*/







