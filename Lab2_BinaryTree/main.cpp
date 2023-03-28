#include "BinaryTreeTester.h"

int main() {
    BinaryTreeTester tester;

    for (int size = 10; size < 200; size += 10)
        tester.test(size);
    return 0;
}
