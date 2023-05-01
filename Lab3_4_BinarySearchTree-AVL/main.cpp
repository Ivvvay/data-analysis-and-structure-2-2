#include "AVLtester.h"

int main() {
    BinaryTreeTester tree;
    for (int size = 10; size < 200; size += 10) {
        tree.test(size);
    }

    BinarySearchTreeTester BST;
    for (int size = 10; size < 200; size += 10) {
        BST.test(size);
    }

    AVLtester AVL;
    for (int size = 10; size < 200; size += 10) {
        AVL.test(size);
    }

    return 0;
}
