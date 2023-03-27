#include "BinaryTreeTester.h"

void BinaryTreeTester::test(const int size) {
    _maxSize = size;
    addAndCount();

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
