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

void BinaryTreeTester::assign() {
    BinaryTree tree;
    check_addAndCount(tree, 0);
    for (int i = 0 ; i < _maxSize; ++i) {
        tree.addNode(i);
        check_addAndCount(tree, i + 1);
    }

    BinaryTree cTree(tree);
    check_assign(tree, cTree);

    BinaryTree Otree = tree;
    check_assign(tree, Otree);

    tree = Otree;
    check_assign(tree, Otree);
}

void BinaryTreeTester::check_assign(BinaryTree &tree1, BinaryTree &tree2) {
    std::vector<int> keys1 = tree1.getKeys();
    std::vector<int> keys2 = tree2.getKeys();
    assert(keys1 == keys2);
}

void BinaryTreeTester::remove() {
    std::random_device rd;
    std::mt19937 gen(rd());

    int invalidKey = -1;
    std::vector<int> nodeKeys;

    BinaryTree tree;
    tree.removeNode(invalidKey);

    for (int i = 0 ; i < _maxSize; ++i) {
        nodeKeys.push_back(i);
        tree.addNode(i);
    }
    /*std::cout << "tree.getSize()=" << tree.getSize() << ", nodeKeys.size()=" << nodeKeys.size() << std::endl;
    tree.printTree();*/

    while (!nodeKeys.empty()) {
        std::uniform_int_distribution<int> distribution(0, nodeKeys.size() - 1);
        int removedNodeIndex = distribution(gen);
        int removeNodeKey = nodeKeys[removedNodeIndex];
        //std::cout << "--------" << removeNodeKey << "--------" << std::endl;

        tree.removeNode(removeNodeKey);
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

    tree.removeNode(invalidKey);
    check_remove(tree, nodeKeys.size());
}

void BinaryTreeTester::check_remove(const BinaryTree &tree, const int size) {
    assert(tree.getSize() == size);
}