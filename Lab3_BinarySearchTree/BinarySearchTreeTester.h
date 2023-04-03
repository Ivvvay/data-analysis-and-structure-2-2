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
private:
    void isBST();
private:
    int _maxSize;
};


#endif //LAB3_BINARYSEARCHTREE_BINARYSEARCHTREETESTER_H
