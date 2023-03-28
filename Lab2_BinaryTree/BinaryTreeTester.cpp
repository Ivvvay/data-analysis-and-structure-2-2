#include "BinaryTreeTester.h"

void BinaryTreeTester::test(const int size) {
    _maxSize = size;
    addAndCount();
    destructor();
    assign();
    remove();
    clear();
    height();
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
    for (int i = 0; i < 1000000; ++i) {
        addAndCount();
    }
    getchar();
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

void BinaryTreeTester::clear() {
    BinaryTree tree;
    for (int i = 0 ; i < _maxSize; ++i)
        tree.addNode(i);

    tree.clear();
    check_clear(tree);
}

void BinaryTreeTester::check_clear(const BinaryTree &tree) {
    assert(tree.getSize() == 0);
}

void BinaryTreeTester::height() {
    height_trivialCases();
    height_longOnlyLeftSubtree();
    height_longOnlyRightSubtree();
    height_longOnlyLeftAndRightSubtrees();
    height_longRandomZigzagSubtrees();
}

void BinaryTreeTester::check_height(const BinaryTree &tree, const int height) {
    assert(tree.getHeight() == height);
}

void BinaryTreeTester::height_trivialCases() {
    BinaryTree tree;
    check_height(tree, 0);
    tree.addNode(0);
    check_height(tree, 1);
}

void BinaryTreeTester::height_longOnlyLeftSubtree() {
    BinaryTree longTree;
    longTree.addNode(0);
    BinaryTree::Node *runner = longTree.getRoot();
    for (int i = 1; i < _maxSize; ++i) {
        runner->setLeftChild(new BinaryTree::Node(i));
        runner = runner->getLeftChild();
        check_height(longTree, i + 1);
    }
}

void BinaryTreeTester::height_longOnlyRightSubtree() {
    BinaryTree longTree;
    longTree.addNode(0);
    BinaryTree::Node *runner = longTree.getRoot();
    for (int i = 1; i < _maxSize; ++i) {
        runner->setRightChild(new BinaryTree::Node(i));
        runner = runner->getRightChild();
        check_height(longTree, i + 1);
    }
}

void BinaryTreeTester::height_longOnlyLeftAndRightSubtrees() {
    BinaryTree longTree;
    longTree.addNode(0);
    BinaryTree::Node *leftRunner = longTree.getRoot();
    BinaryTree::Node *rightRunner = longTree.getRoot();
    for (int i = 1; i < _maxSize/2; ++i) {
        leftRunner->setLeftChild(new BinaryTree::Node(i));
        leftRunner = leftRunner->getLeftChild();
        check_height(longTree, i + 1);

        rightRunner->setRightChild(new BinaryTree::Node(i));
        rightRunner = rightRunner->getRightChild();
        check_height(longTree, i + 1);
    }
}

void BinaryTreeTester::height_longRandomZigzagSubtrees() {
    std::random_device rd;
    std::mt19937 gen(rd());

    BinaryTree longTree;
    longTree.addNode(0);
    BinaryTree::Node *leftRunner = longTree.getRoot();
    BinaryTree::Node *rightRunner = longTree.getRoot();

    leftRunner->setLeftChild(new BinaryTree::Node(1));
    leftRunner = leftRunner->getLeftChild();
    rightRunner->setRightChild(new BinaryTree::Node(1));
    rightRunner = rightRunner->getRightChild();

    for (int i = 2; i < _maxSize/2; ++i) {
        if (gen() % 2 == 0) {
            leftRunner->setLeftChild(new BinaryTree::Node(i));
            leftRunner = leftRunner->getLeftChild();
        } else {
            leftRunner->setRightChild(new BinaryTree::Node(i));
            leftRunner = leftRunner->getRightChild();
        }
        check_height(longTree, i + 1);

        if (gen() % 2 == 0) {
            rightRunner->setLeftChild(new BinaryTree::Node(i));
            rightRunner = rightRunner->getLeftChild();
        } else {
            rightRunner->setRightChild(new BinaryTree::Node(i));
            rightRunner = rightRunner->getRightChild();
        }
        check_height(longTree, i + 1);
    }
}
