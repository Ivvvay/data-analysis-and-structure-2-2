#include "AVLtree.h"

AVLtree::AVLtree() : BinarySearchTree() {}

AVLtree::AVLtree(const AVLtree &other) : BinarySearchTree(other) {}

AVLtree::AVLtree(Node *newRoot) : BinarySearchTree(newRoot) {}