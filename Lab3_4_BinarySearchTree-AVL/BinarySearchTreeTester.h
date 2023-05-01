#ifndef LAB3_BINARYSEARCHTREE_BINARYSEARCHTREETESTER_H
#define LAB3_BINARYSEARCHTREE_BINARYSEARCHTREETESTER_H
#include "BinarySearchTree.h"

class BinarySearchTreeTester {
public:
    BinarySearchTreeTester() = default;
    ~BinarySearchTreeTester() = default;
    void test(const int size);
protected:
    bool check_BST(BinarySearchTree::Node* root, int minVal, int maxVal);
    void check_copySubtreeSearch(BinarySearchTree &subTree, BinarySearchTree &tree, const int key);
    void check_getMinMaxKey(BinarySearchTree &tree, int min, int max);
    void check_remove(const BinaryTree &tree, const int size);
private:
    void isBST();
    void copySubtreeSearch();
    void getMinMaxKey();
    void remove();
private:
    int _maxSize;
};


#endif //LAB3_BINARYSEARCHTREE_BINARYSEARCHTREETESTER_H
