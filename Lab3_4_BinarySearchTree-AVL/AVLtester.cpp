#include "AVLtester.h"

void AVLtester::test(const int size) {
    _maxSize = size;
    isAVL();
    BinarySearchTreeTester::remove();
}

void AVLtester::isAVL() {
    int min = 0;
    int max = _maxSize;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(min, max);

    AVLtree tree;
    for (int i = 0; i < _maxSize; ++i) {
        int key = dis(gen);
        tree.addNode(key);
    }
    check_BST(tree);
    check_AVL(tree);
}

void AVLtester::check_AVL(AVLtree &tree) {
    assert(tree.isBalanced());
}







