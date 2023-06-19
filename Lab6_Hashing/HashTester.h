#ifndef LAB6_HASHING_HASHTESTER_H
#define LAB6_HASHING_HASHTESTER_H
#include "HashTable.h"

class HashTester {
public:
    HashTester() = default;
    ~HashTester() = default;

    void test(const int capacity);
protected:
    void check_insert(HashTable<int> table);
    void check_remove(HashTable<int> table, int key);
    void check_assign(HashTable<int> table1, HashTable<int> table2);
    void check_resize(HashTable<int> table, int newCapacity);
private:
    void insert();
    void remove();
    void assign();
    void resize();
private:
    int _capacityMax;
};


#endif //LAB6_HASHING_HASHTESTER_H
