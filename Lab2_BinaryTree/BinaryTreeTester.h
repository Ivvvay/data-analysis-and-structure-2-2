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

private:
    void addAndCount();


private:
    int _maxSize;
};


#endif //DATA_ANALYSIS_AND_STRUCTURE_2_2_BINARYTREETESTER_H
