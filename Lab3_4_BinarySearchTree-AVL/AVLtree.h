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

    Node* addNode(int key);
    Node* addNode(Node* root, int key);

    bool removeNode(int key);
    Node* removeNode(Node* root, int key, bool& result);

    AVLtree& operator=(const AVLtree& other);

    Node* balanceNode(Node* node);
    int getBalanceFactor(Node* node);
    Node* rightRotate(Node* node);
    Node* leftRotate(Node* node);

    Node* findMin(Node* node);
    Node* removeMin(Node* node);
};


#endif //LAB3_4_BINARYSEARCHTREE_AVL_AVLTREE_H
