#ifndef LAB3_4_BINARYSEARCHTREE_AVL_AVLTESTER_H
#define LAB3_4_BINARYSEARCHTREE_AVL_AVLTESTER_H
#include "AVLtree.h"
#include "BinarySearchTreeTester.h"

class AVLtester : public BinarySearchTreeTester {
public:
    AVLtester() = default;
    ~AVLtester() override = default;

    void test(const int size) override;
protected:
    BinaryTree *allocateTree() override;
    void check_addAndCount(const BinaryTree &tree, const int size) override;
    void check_assign(const BinaryTree *tree1, const BinaryTree *tree2) override;
    void check_remove(const BinaryTree &tree, const int size) override;
    void check_clear(const BinaryTree &tree) override;

    //void isAVL();
};


#endif //LAB3_4_BINARYSEARCHTREE_AVL_AVLTESTER_H
