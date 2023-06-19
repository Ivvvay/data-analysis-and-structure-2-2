#include "HashTester.h"

IHashFunction *getHashFunction(int hashFunctionIndex) {
    switch (hashFunctionIndex) {
        case 1:
            return new HashFunction1();
        case 2:
            return new HashFunction2();
        case 3:
            return new HashFunction3();
        default:
            return new HashFunction1();
    }
}

int main() {
    HashTester tester;

    for (int size = 10; size < 200; size += 10)
        tester.test(size);

    /*/// Тест insert
    std::cout << "Тест insert" << std::endl;
    HashTable<std::string> table;

    table.insert(1, "1");
    table.insert(2, "2");
    table.insert(3, "3");
    table.insert(4, "4");
    table.insert(5, "5");
    table.insert(8, "8");
    table.insert(7, "7");
    table.insert(9, "9");
    table.printTable();

    table.changeHashFunction(getHashFunction(2));
    table.resize(10);

    table.printTable();

    /// Тест метода contains
    assert(table.contains(1));
    assert(!table.contains(6));

    /// Тест operator[]
    std::cout << "Тест operator[]" << std::endl;
    std::cout << table[5] << std::endl;


    /// Тест метода remove
    std::cout << "Тест метода remove" << std::endl;
    table.remove(1);
    assert(table.contains(9));
    table.printTable();

    /// Тест метода changeHashFunction
    std::cout << "Тест метода changeHashFunction" << std::endl;
    table.changeHashFunction(getHashFunction(2));
    table.printTable();


    /// Тест метода resize
    std::cout << "Тест метода resize" << std::endl;
    table.resize(10);
    table.printTable();

    /// Тест оператора присваивания
    std::cout << "Тест оператора присваивания" << std::endl;
    HashTable<std::string> table2;
    table2 = table;
    table2.insert(5, "Five");
    assert(table2.contains(5));
    assert(!table2.contains(1));

    table2.printTable();

    table.changeHashFunction(getHashFunction(3));
    table.printTable();*/

    return 0;
}