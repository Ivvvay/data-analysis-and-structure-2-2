#ifndef LAB3_4_BINARYSEARCHTREE_AVL_AVLTESTER_H
#define LAB3_4_BINARYSEARCHTREE_AVL_AVLTESTER_H
#include "AVLtree.h"
#include "BinarySearchTreeTester.h"

class AVLtester : public BinarySearchTreeTester {
public:
    AVLtester() = default;
    ~AVLtester() = default;
    void test(const int size);

protected:
    void check_AVL(AVLtree &tree);
private:
    void isAVL();
};


#endif //LAB3_4_BINARYSEARCHTREE_AVL_AVLTESTER_H
