#ifndef LAB3_4_BINARYSEARCHTREE_AVL_AVLTREE_H
#define LAB3_4_BINARYSEARCHTREE_AVL_AVLTREE_H
#include "BinarySearchTree.h"

class AVLtree : public BinarySearchTree {
public:
    AVLtree();
    AVLtree(const AVLtree& other);
    explicit AVLtree(Node* newRoot);
    ~AVLtree() override = default;
};


#endif //LAB3_4_BINARYSEARCHTREE_AVL_AVLTREE_H
