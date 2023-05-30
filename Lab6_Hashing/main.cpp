#include "HashTable.h"

int main() {
    HashTable<int, std::string> table;
    table.insert(1, "One");
    table.insert(2, "Two");
    table.insert(3, "Three");
    table.insert(4, "Four");

    // Тест метода contains
    assert(table.contains(1));
    assert(!table.contains(5));

    // Тест метода printTable
    table.printTable();

    // Тест метода remove
    table.remove(3);
    assert(!table.contains(3));

    // Тест метода changeHashFunction
    table.changeHashFunction(2);

    // Тест метода resize
    table.resize(10);
    assert(table.contains(1));
    assert(!table.contains(3));

    table.printTable();

    // Тест оператора присваивания
    HashTable<int, std::string> table2;
    table2 = table;
    table2.insert(5, "Five");
    assert(table2.contains(1));
    assert(!table2.contains(3));

    table2.printTable();

    table.changeHashFunction(3);
    table.printTable();

    return 0;
}
