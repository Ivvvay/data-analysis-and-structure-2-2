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
    Node* rootOfCopySubtree(int key) override;

    Node* addNode(int key) override;
    Node* addNode(Node* root, int key) override;

    bool removeNode(int key) override;
    Node* removeNode(Node* root, int key, bool& result);

    AVLtree& operator=(const AVLtree& other);

private:
    Node* balanceNode(Node* node);
    int getBalanceFactor(Node* node);
    Node* rightRotate(Node* node);
    Node* leftRotate(Node* node);

    Node* findMin(Node* node);
    Node* removeMin(Node* node);
};


#endif //LAB3_4_BINARYSEARCHTREE_AVL_AVLTREE_H
