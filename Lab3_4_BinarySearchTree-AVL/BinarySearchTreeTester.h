#ifndef LAB3_BINARYSEARCHTREE_BINARYSEARCHTREETESTER_H
#define LAB3_BINARYSEARCHTREE_BINARYSEARCHTREETESTER_H
#include "BinarySearchTree.h"
#include "BinaryTreeTester.h"

class BinarySearchTreeTester : public BinaryTreeTester {
public:
    BinarySearchTreeTester() = default;
    ~BinarySearchTreeTester() = default;
    void test(const int size);
protected:
    void check_BST(BinaryTree &tree);
    void check_copySubtreeSearch(BinarySearchTree &subTree, BinarySearchTree &tree, const int key);
    void check_getMinMaxKey(BinarySearchTree &tree, int min, int max);
    void check_remove(const BinaryTree &tree, const int size) override;

protected:
    void isBST();
    void copySubtreeSearch();
    void getMinMaxKey();
    void remove();

    bool isBST(BinaryTree &tree);
};


#endif //LAB3_BINARYSEARCHTREE_BINARYSEARCHTREETESTER_H
