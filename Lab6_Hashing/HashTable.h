#ifndef LAB6_HASHING_HASHTABLE_H
#define LAB6_HASHING_HASHTABLE_H
#include <iostream>
#include <cmath>

// Указатель на интерфейс хеш-функции
class HashFunction {
public:
    virtual int computeHash(int key, int tableSize) = 0;
    virtual ~HashFunction() = default;
};

// Реализация хеш-функции 1
// h_i(K) = (h_{i-1}(K) + c*i + d*i^2) mod N; параметры c и d определяются
// как остаток от деления вашего номера в списке ниже на 5 и 7 соответственно;
class HashFunction1 : public HashFunction {
public:
    int computeHash(int key, int tableSize) override {
        const int c = 2 % 5;
        const int d = 4 % 7;
        int hash = key % tableSize;
        for (int i = 1; true; i++) {
            hash = (hash + c * i + d * i * i) % tableSize;
            if (hash < tableSize)
                return hash;
        }
    }
};

// Реализация хеш-функции 2
// h_i(K) = [h_{i-1}(K)*a*N] mod N; a = – (1 – √5) / 2, [ ] – целая часть.
class HashFunction2 : public HashFunction {
public:
    int computeHash(int key, int tableSize) override {
        const double a = - (1 - std::sqrt(5.0)) / 2.0;
        int hash = key % tableSize;
        for (int i = 1; true; i++) {
            hash = static_cast<int>(hash * a * tableSize) % tableSize;
            if (hash < tableSize)
                return hash;
        }
    }
};

// Реализация хеш-функции 3
// h_i(K)= (K mod N) + i*(1+ K mod (N – 2)) mod N.
class HashFunction3 : public HashFunction {
public:
    int computeHash(int key, int tableSize) override {
        int hash = key % tableSize;
        for (int i = 1; true; i++) {
            hash = (hash + i * (1 + key % (tableSize - 2))) % tableSize;
            if (hash < tableSize)
                return hash;
        }
    }
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
