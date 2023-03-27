#include "BinaryTreeTester.h"

void BinaryTreeTester::test(const int size) {
    _maxSize = size;
    addAndCount();
    destructor();
}

void BinaryTreeTester::addAndCount() {
    BinaryTree tree;
    check_addAndCount(tree, 0);

    for (int i = 0 ; i < _maxSize; i++) {
        tree.addNode(i);
        check_addAndCount(tree, i + 1);
    }
}

void BinaryTreeTester::check_addAndCount(const BinaryTree &tree, const int size) {
    assert(tree.getSize() == size);
}

void BinaryTreeTester::destructor() {
    BinaryTree tree;
    check_destructor(tree, 0);
    for (int i = 0 ; i < _maxSize; ++i) {
        tree.addNode(i);
        check_destructor(tree, i + 1);
    }
    tree.~BinaryTree();
    check_destructor(tree, 0);
}

void BinaryTreeTester::check_destructor(const BinaryTree &tree, const int size) {
    assert(tree.getSize() == size);
}