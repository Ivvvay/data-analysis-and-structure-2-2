#ifndef LAB3_4_BINARYSEARCHTREE_AVL_BINARYTREETESTER_H
#define LAB3_4_BINARYSEARCHTREE_AVL_BINARYTREETESTER_H
#include "BinaryTree.h"
#include <vector>
#include <queue>

class BinaryTreeTester {
public:
    BinaryTreeTester() = default;
    virtual ~BinaryTreeTester() = default;

    virtual void test(const int size);

protected:
    virtual BinaryTree* allocateTree();

    virtual void check_addAndCount(const BinaryTree &tree, const int size);
    void check_assign(const std::vector<const BinaryTree::Node *> &tree1Nodes, const std::vector<const BinaryTree::Node *> &tree2Nodes);
    virtual void check_assign(const BinaryTree *tree1, const BinaryTree *tree2);
    virtual void check_remove(const BinaryTree &tree, const int size);
    virtual void check_clear(const BinaryTree &tree);
    void check_height(const BinaryTree &tree, const int size);
    virtual void check_copySubtreeAndDelete(const BinaryTree &copySubtree, const BinaryTree &copySubtreeForDel, const BinaryTree &longTree);

protected:
    virtual void deallocateTree(BinaryTree *tree);

    void addAndCount();
    void destructor();
    void assign();
    void remove();
    void clear();
    void height();
    void height_trivialCases();
    void height_longOnlyLeftSubtree();
    void height_longOnlyRightSubtree();
    void height_longOnlyLeftAndRightSubtrees();
    void height_longRandomZigzagSubtrees();
    void copySubtreeAndDelete();
    std::vector<const BinaryTree::Node *> treeNodes(const BinaryTree *tree);

protected:
    int _maxSize;
};


#endif //LAB3_4_BINARYSEARCHTREE_AVL_BINARYTREETESTER_H
