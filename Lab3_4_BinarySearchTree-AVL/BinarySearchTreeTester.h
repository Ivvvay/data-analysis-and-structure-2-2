#ifndef LAB3_BINARYSEARCHTREE_BINARYSEARCHTREETESTER_H
#define LAB3_BINARYSEARCHTREE_BINARYSEARCHTREETESTER_H

#include "BinarySearchTree.h"
#include "BinaryTreeTester.h"

class BinarySearchTreeTester : public BinaryTreeTester {
public:
    BinarySearchTreeTester() = default;
    ~BinarySearchTreeTester() override = default;

    void test(const int size) override;
protected:
    BinaryTree *allocateTree() override;
    void check_addAndCount(const BinaryTree &tree, const int size) override;
    void check_assign(const BinaryTree *tree1, const BinaryTree *tree2) override;
    void check_remove(const BinaryTree &tree, const int size) override;
    void check_clear(const BinaryTree &tree) override;

    void isBST(const BinaryTree& tree);
};


#endif //LAB3_BINARYSEARCHTREE_BINARYSEARCHTREETESTER_H
