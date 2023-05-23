#include "BinaryTreeTester.h"

void BinaryTreeTester::test(const int size) {
    _maxSize = size;
    addAndCount();
    destructor();
    assign();
    remove();
    clear();
    height();
    copySubtreeAndDelete();
}

BinaryTree *BinaryTreeTester::allocateTree() {
    return new BinaryTree;
}

void BinaryTreeTester::deallocateTree(BinaryTree *tree) {
    delete tree;
}

void BinaryTreeTester::addAndCount() {
    BinaryTree *tree = allocateTree();
    check_addAndCount(*tree, 0);

    for (int i = 0 ; i < _maxSize; i++) {
        tree->addNode(i);
        check_addAndCount(*tree, i + 1);
    }
    deallocateTree(tree);
}

void BinaryTreeTester::check_addAndCount(const BinaryTree &tree, const int size) {
    assert(tree.getSize() == size);
}

void BinaryTreeTester::destructor() {
    const int runsCount = 10;

    for (int i = 0; i < runsCount; i++) {
        BinaryTree *tree = allocateTree();
        for (int j = 0 ; j < _maxSize; ++j) {
            tree->addNode(j);
        }
        deallocateTree(tree);
    }
}

void BinaryTreeTester::assign() {

    BinaryTree* tree1 = allocateTree();

    for (int i = 0 ; i < _maxSize; ++i) {
        tree1->addNode(i);
    }

    BinaryTree* tree2 = allocateTree();
    *tree2 = *tree1; // Конструктор копирования

    std::vector<const BinaryTree::Node *> tree1Nodes = treeNodes(tree1);
    std::vector<const BinaryTree::Node *> tree2Nodes = treeNodes(tree2);

    check_assign(tree1Nodes, tree2Nodes); // Проверка копирования

    *tree1 = *tree2; // Оператор присваивания

    tree1Nodes = treeNodes(tree1);
    tree2Nodes = treeNodes(tree2);

    check_assign(tree1Nodes, tree2Nodes); // Проверка присваивания

    deallocateTree(tree1);
    deallocateTree(tree2);
}

void BinaryTreeTester::check_assign(const std::vector<const BinaryTree::Node *> &tree1Nodes,
                                    const std::vector<const BinaryTree::Node *> &tree2Nodes) {
    assert(tree1Nodes.size() == tree2Nodes.size());

    for (int i = 0; i < tree1Nodes.size(); ++i) {
        assert(tree1Nodes[i] != tree2Nodes[i]); // Проверка адресов различных узлов
        assert(tree1Nodes[i]->getKey() == tree2Nodes[i]->getKey()); // Проверка значений ключей узлов
    }
}

void BinaryTreeTester::check_assign(const BinaryTree *tree1, const BinaryTree *tree2) {
    std::vector<const BinaryTree::Node *> tree1Nodes = treeNodes(tree1);
    std::vector<const BinaryTree::Node *> tree2Nodes = treeNodes(tree2);
    check_assign(tree1Nodes, tree2Nodes);
}

std::vector<const BinaryTree::Node *> BinaryTreeTester::treeNodes(const BinaryTree *tree)
{
    std::vector<const BinaryTree::Node*> nodes;
    std::queue<const BinaryTree::Node*> nodesToProcess;
    nodesToProcess.push(tree->getRoot());

    while (!nodesToProcess.empty()) {
        const BinaryTree::Node* node = nodesToProcess.front();
        if (node != nullptr) {
            nodesToProcess.push(node->getLeftChild());
            nodesToProcess.push(node->getRightChild());
            nodes.push_back(node);
        }
        nodesToProcess.pop();
    }

    return nodes;
}

void BinaryTreeTester::remove() {
    int invalidKey = -1;
    std::vector<int> nodeKeys;

    BinaryTree* tree = allocateTree();
    tree->removeNode(invalidKey);

    check_remove(*tree, nodeKeys.size());

    for (int i = 0 ; i < _maxSize; ++i) {
        nodeKeys.push_back(i);
        tree->addNode(i);
    }
    //tree->printTree();

    while (!nodeKeys.empty()) {

        int removedNodeIndex = rand() % nodeKeys.size();

        tree->removeNode(invalidKey);
        check_remove(*tree, nodeKeys.size());

        //std::cout << nodeKeys[removedNodeIndex] << ":\n";

        tree->removeNode(nodeKeys[removedNodeIndex]);
        nodeKeys.erase(nodeKeys.begin() + removedNodeIndex);
        check_remove(*tree, nodeKeys.size());

        //std::cout<<tree->getSize() << " " << nodeKeys.size() <<"\n";
        //tree->printTree();
    }

    tree->removeNode(invalidKey);
    check_remove(*tree, nodeKeys.size());
    deallocateTree(tree);
}

void BinaryTreeTester::check_remove(const BinaryTree &tree, const int size) {
    assert(tree.getSize() == size);
}

void BinaryTreeTester::clear() {
    BinaryTree* tree = allocateTree();

    tree->clear();
    check_clear(*tree);

    for (int i = 0; i < 100; i++) {
        for (int j = 0 ; j < _maxSize; ++j) {
            tree->addNode(j);
        }
        tree->clear();
        check_clear(*tree);
    }
    deallocateTree(tree);
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
    BinaryTree *tree = allocateTree();
    check_height(*tree, 0);
    tree->addNode(0);
    check_height(*tree, 1);

    deallocateTree(tree);
}

void BinaryTreeTester::height_longOnlyLeftSubtree() {
    BinaryTree *longTree = allocateTree();
    longTree->addNode(0);
    BinaryTree::Node *runner = longTree->getRoot();
    for (int i = 1; i < _maxSize; ++i) {
        runner->setLeftChild(new BinaryTree::Node(i));
        runner = runner->getLeftChild();
        check_height(*longTree, i + 1);
    }
    deallocateTree(longTree);
}

void BinaryTreeTester::height_longOnlyRightSubtree() {
    BinaryTree *longTree = allocateTree();
    longTree->addNode(0);
    BinaryTree::Node *runner = longTree->getRoot();
    for (int i = 1; i < _maxSize; ++i) {
        runner->setRightChild(new BinaryTree::Node(i));
        runner = runner->getRightChild();
        check_height(*longTree, i + 1);
    }
    deallocateTree(longTree);
}

void BinaryTreeTester::height_longOnlyLeftAndRightSubtrees() {
    BinaryTree *longTree = allocateTree();
    longTree->addNode(0);
    BinaryTree::Node *leftRunner = longTree->getRoot();
    BinaryTree::Node *rightRunner = longTree->getRoot();
    for (int i = 1; i < _maxSize/2; ++i) {
        leftRunner->setLeftChild(new BinaryTree::Node(i));
        leftRunner = leftRunner->getLeftChild();
        check_height(*longTree, i + 1);

        rightRunner->setRightChild(new BinaryTree::Node(i));
        rightRunner = rightRunner->getRightChild();
        check_height(*longTree, i + 1);
    }
    deallocateTree(longTree);
}

void BinaryTreeTester::height_longRandomZigzagSubtrees() {
    std::random_device rd;
    std::mt19937 gen(rd());

    BinaryTree *longTree = allocateTree();
    longTree->addNode(0);
    BinaryTree::Node *leftRunner = longTree->getRoot();
    BinaryTree::Node *rightRunner = longTree->getRoot();

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
        check_height(*longTree, i + 1);

        if (gen() % 2 == 0) {
            rightRunner->setLeftChild(new BinaryTree::Node(i));
            rightRunner = rightRunner->getLeftChild();
        } else {
            rightRunner->setRightChild(new BinaryTree::Node(i));
            rightRunner = rightRunner->getRightChild();
        }
        check_height(*longTree, i + 1);
    }
    //longTree.printTree();
    deallocateTree(longTree);
}

void BinaryTreeTester::copySubtreeAndDelete() {
    std::random_device rd;
    std::mt19937 gen(rd());

    BinaryTree *longTree = allocateTree();
    longTree->addNode(0);
    BinaryTree::Node *leftRunner = longTree->getRoot();
    BinaryTree::Node *rightRunner = longTree->getRoot();

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
        check_height(*longTree, i + 1);

        if (gen() % 2 == 0) {
            rightRunner->setLeftChild(new BinaryTree::Node(i));
            rightRunner = rightRunner->getLeftChild();
        } else {
            rightRunner->setRightChild(new BinaryTree::Node(i));
            rightRunner = rightRunner->getRightChild();
        }
        check_height(*longTree, i + 1);
    }

    std::uniform_int_distribution<> dis(0, longTree->getHeight());
    int copySubtreeKey = dis(gen);

    BinaryTree *copySubtree = allocateTree();
    *copySubtree = longTree->copySubtree(copySubtreeKey);

    BinaryTree *copySubtreeForDel = allocateTree();
    *copySubtreeForDel = *longTree;
    copySubtreeForDel->deleteSubtree(copySubtreeKey);

    check_copySubtreeAndDelete(*copySubtree, *copySubtreeForDel, *longTree);

    deallocateTree(longTree);
    deallocateTree(copySubtree);
    deallocateTree(copySubtreeForDel);
}
void BinaryTreeTester::check_copySubtreeAndDelete(const BinaryTree &copySubtree,
                                                  const BinaryTree &copySubtreeForDel,
                                                  const BinaryTree &longTree) {
    assert((copySubtree.getSize() + copySubtreeForDel.getSize()) == longTree.getSize());
}
