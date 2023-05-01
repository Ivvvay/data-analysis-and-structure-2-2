#ifndef LAB3_4_BINARYSEARCHTREE_AVL_AVLTREE_H
#define LAB3_4_BINARYSEARCHTREE_AVL_AVLTREE_H
#include "BinarySearchTree.h"

class AVLtree : public BinarySearchTree {
public:
    AVLtree();
    AVLtree(const AVLtree& other);
    explicit AVLtree(Node* newRoot);
    ~AVLtree() override = default;

    AVLtree copySubtree(int key);
    Node* copySubtree(const Node* node) const override;
};


#endif //LAB3_4_BINARYSEARCHTREE_AVL_AVLTREE_H
