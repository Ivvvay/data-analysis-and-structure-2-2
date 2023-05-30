#ifndef LAB6_HASHING_HASHTABLE_H
#define LAB6_HASHING_HASHTABLE_H
#include <iostream>

// Указатель на интерфейс хеш-функции
class HashFunction {
public:
    virtual int computeHash(int key, int tableSize) = 0;
    virtual ~HashFunction() = default;
};

template <typename KeyType, typename ValueType>
class HashTable {

private:
    // Внутренний класс для хранения пар "ключ-значение"
    struct HashNode {
    public:
        KeyType _key;
        ValueType _value;
        HashNode* _next;

        HashNode(const KeyType& k, const ValueType& v)
                : _key(k), _value(v), _next(nullptr) {}
    };

    // Приватные члены класса
    std::vector<HashNode*> _table;
    int _size;
    int _capacity;
    HashFunction* _hashFunction;
};

#endif //LAB6_HASHING_HASHTABLE_H
