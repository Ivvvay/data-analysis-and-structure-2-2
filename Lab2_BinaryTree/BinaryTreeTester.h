#ifndef DATA_ANALYSIS_AND_STRUCTURE_2_2_BINARYTREETESTER_H
#define DATA_ANALYSIS_AND_STRUCTURE_2_2_BINARYTREETESTER_H
#include "BinaryTree.h"

class BinaryTreeTester {
public:
    BinaryTreeTester() = default;
    ~BinaryTreeTester() = default;

    void test(const int size);
protected:
    void check_addAndCount(const BinaryTree &tree, const int size);
    void check_assign(BinaryTree &tree1, BinaryTree &tree2);
    void check_remove(const BinaryTree &tree, const int size);
    void check_clear(const BinaryTree &tree);
    void check_height(const BinaryTree &tree, const int size);
    void check_copySubtreeAndDelete(const BinaryTree &copySubtree, const BinaryTree &copySubtreeForDel, const BinaryTree &longTree);

private:
    void addAndCount();
    void destructor();
    void assign();
    void remove();
    void clear();
    void height();
    void height_trivialCases();
    void height_longOnlyLeftSubtree();
    void height_longOnlyRightSubtree();
    void height_longOnlyLeftAndRightSubtrees();
    void height_longRandomZigzagSubtrees();
    void copySubtreeAndDelete();

private:
    int _maxSize;
};


#endif //DATA_ANALYSIS_AND_STRUCTURE_2_2_BINARYTREETESTER_H
