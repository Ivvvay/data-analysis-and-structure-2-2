#include "BinarySearchTreeTester.h"

void BinarySearchTreeTester::test(const int size) {
    _maxSize = size;
    addAndCount();
    destructor();
    assign();
    remove();
    clear();
    height();
}

BinaryTree *BinarySearchTreeTester::allocateTree() {
    return new BinarySearchTree;
}

void BinarySearchTreeTester::isBST(const BinaryTree &tree) {
    std::vector<int> nodeKeys = tree.getKeys();
    for (int i = 1; i < nodeKeys.size(); i++)
        assert(nodeKeys[i-1] <= nodeKeys[i]);
}

void BinarySearchTreeTester::check_addAndCount(const BinaryTree &tree, const int size) {
    BinaryTreeTester::check_addAndCount(tree, size);
    isBST(tree);
}

void BinarySearchTreeTester::check_assign(const BinaryTree *tree1, const BinaryTree *tree2) {
    BinaryTreeTester::check_assign(tree1, tree2);
    isBST(*tree1);
    isBST(*tree2);
}

void BinarySearchTreeTester::check_remove(const BinaryTree &tree, const int size) {
    BinaryTreeTester::check_remove(tree, size);
    isBST(tree);
}

void BinarySearchTreeTester::check_clear(const BinaryTree &tree) {
    BinaryTreeTester::check_clear(tree);
    isBST(tree);
}