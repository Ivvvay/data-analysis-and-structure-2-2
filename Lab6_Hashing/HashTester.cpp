#include "HashTester.h"

void HashTester::test(const int capacity) {
    _capacityMax = capacity;
    insert();
    remove();
    assign();
    resize();
}

void HashTester::insert() {
    HashTable<int> tester(_capacityMax);

    for (int i = 0; i < _capacityMax; i++)
        tester.insert(i, i);

    check_insert(tester);

    tester.insert(_capacityMax + 1, _capacityMax + 1);
    assert(!tester.contains(_capacityMax + 1));
}

void HashTester::check_insert(HashTable<int> table) {
    for (int i = 0; i < _capacityMax; i++)
        assert(table.contains(i));
}

void HashTester::remove() {
    HashTable<int> tester(_capacityMax);

    for (int i = 0; i < _capacityMax; i++)
        tester.insert(i, i);

    check_insert(tester);

    for (int i = 0; i < _capacityMax; i++) {
        tester.remove(i);
        check_remove(tester, i);
    }
}

void HashTester::check_remove(HashTable<int> table, int key) {
    assert(!table.contains(key));
}

void HashTester::assign() {
    HashTable<int> tester1(_capacityMax);

    for (int i = 0; i < _capacityMax; i++)
        tester1.insert(i, i);

    check_insert(tester1);

    HashTable<int> tester2;
    tester2 = tester1;
    check_assign(tester1, tester2);

    /*std::cout << "\n--- Tester 1 ---" << std::endl;
    tester1.printTable();
    std::cout << "\n--- Tester 2 ---" << std::endl;
    tester2.printTable();*/
}

void HashTester::check_assign(HashTable<int> table1, HashTable<int> table2) {
    assert(table1.getCapacity() == table2.getCapacity());
    for (int i = 0; i < _capacityMax; i++)
        assert(table1[i] == table2[i]);
}

void HashTester::resize() {
    HashTable<int> tester(_capacityMax);

    for (int i = 0; i < _capacityMax; i++)
        tester.insert(i, i);
    check_insert(tester);

    tester.resize(_capacityMax + 10);
    check_resize(tester, _capacityMax + 10);
}

void HashTester::check_resize(HashTable<int> table, int newCapacity) {
    assert(table.getCapacity() == newCapacity);
}



