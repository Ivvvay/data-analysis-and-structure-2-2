#ifndef LAB6_HASHING_HASHTABLE_H
#define LAB6_HASHING_HASHTABLE_H

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <string>

// Указатель на интерфейс хеш-функции
class IHashFunction {
public:
    virtual int computeHash(int key, int tableSize) = 0;
    virtual IHashFunction *clone() const = 0;
    virtual ~IHashFunction() = default;
};

// Реализация хеш-функции 1
// h_i(K) = (h_{i-1}(K) + c*i + d*i^2) mod N; параметры c и d определяются
// как остаток от деления вашего номера в списке ниже на 5 и 7 соответственно;
class HashFunction1 : public IHashFunction {
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
    IHashFunction *clone() const override {
        return new HashFunction1(*this);
    }
};

// Реализация хеш-функции 2
// h_i(K) = [h_{i-1}(K)*a*N] mod N; a = – (1 – √5) / 2, [ ] – целая часть.
class HashFunction2 : public IHashFunction {
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
    IHashFunction *clone() const override {
        return new HashFunction2(*this);
    }
};

// Реализация хеш-функции 3
// h_i(K)= (K mod N) + i*(1+ K mod (N – 2)) mod N.
class HashFunction3 : public IHashFunction {
public:
    int computeHash(int key, int tableSize) override {
        int hash = key % tableSize;
        for (int i = 1; true; i++) {
            hash = (hash + i * (1 + key % (tableSize - 2))) % tableSize;
            if (hash < tableSize)
                return hash;
        }
    }
    IHashFunction *clone() const override {
        return new HashFunction3(*this);
    }
};

template <typename ValueType>
class HashTable {
public:
    // Конструкторы
    HashTable() : HashTable(8) {}

    explicit HashTable(int tableSize) : _capacity(tableSize), _hashFunction(new HashFunction1()) {
        _table.resize(_capacity, nullptr);
    }

    HashTable(const HashTable& other) : _capacity(other._capacity), _hashFunction(other._hashFunction->clone()) {
        copyTable(other);
    }

    // Деструктор
    ~HashTable() {
        clear();
        delete _hashFunction;
    }

    // Методы
    bool insert(const int key, const ValueType& value) {
        int hash = _hashFunction->computeHash(key, _capacity);

        if (_table[hash] == nullptr) {
            _table[hash] = new HashNode(key, value);
        } else {
            HashNode* current = _table[hash];
            while (current->_next != nullptr) {
                if (current->_key == key) {
                    current->_value = value;
                    return true;
                }
                current = current->_next;
            }
            if (current->_key == key) {
                current->_value = value;
                return true;
            }
            int i = 0;
            while (i < _capacity && _table[i] != nullptr)
                i++;

            if (i >= _capacity)
                return false;

            _table[i] = new HashNode(key, value);
            current->_next = _table[i];
        }
        return true;
    }

    bool remove(const int key) {
        HashNode* node = nullptr;
        HashNode* parent = nullptr;
        getNodeAndParent(key, node, parent);

        if (node == nullptr) {
            return false;
        }

        if (parent == nullptr) {
            int currentIndex = findIndex(node);

            HashNode* nextCurrent = node->_next;
            while (nextCurrent != nullptr) {
                int temp = currentIndex;
                currentIndex = findIndex(nextCurrent);
                _table[temp] = nextCurrent;
                nextCurrent = nextCurrent->_next;
            }
            _table[currentIndex] = _table[currentIndex]->_next;
        } else {
            parent->_next = node->_next;

            HashNode* nextCurrent = node->_next;
            int currentIndex = findIndex(node);
            while (nextCurrent != nullptr) {
                int temp = currentIndex;
                currentIndex = findIndex(nextCurrent);
                _table[temp] = nextCurrent;
                nextCurrent = nextCurrent->_next;
            }
            _table[currentIndex] = _table[currentIndex]->_next;
        }

        delete node;
        return true;
    }

    bool contains(const int key) {
        HashNode* node = containsGetNode(key);
        return (node != nullptr);
    }

    void printTable() const {
        std::cout << "Hash" << std::setw(18) << "(Key, Value)" << std::setw(26) << "(_table[i], _next)" << std::endl;
        for (int i = 0; i < _capacity; i++) {
            std::cout << "Hash " << i << ":" << std::setw(4);
            HashNode* current = _table[i];
            if (current != nullptr) { // while (current != nullptr)
                std::cout << std::setw(4) << "(" << current->_key << ", " << current->_value << ")";
                std::cout << std::setw(9) << "(" << current << ", " << current->_next << ") ";
                //current = current->_next;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    void changeHashFunction(IHashFunction *hashFunction) {
        delete _hashFunction;
        _hashFunction = hashFunction;
        rehash();
    }

    void rehash() {
        resize(_capacity);
    }

    HashTable& operator=(const HashTable& other) {
        if (this != &other) {
            clear();
            delete _hashFunction;
            _capacity = other._capacity;
            _hashFunction = other._hashFunction->clone();
            _table.resize(_capacity, nullptr);
            copyTable(other);
        }
        return *this;
    }

    ValueType& operator[](const int& key) {
        int index = _hashFunction->computeHash(key, _capacity);
        HashNode* current = _table[index];

        while (current != nullptr) {
            if (current->_key == key)
                return current->_value;
            current = current->_next;
        }

        insert(key, ValueType());

        return _table[index]->_value;
    }

    void resize(int capacity) {
        std::vector<HashNode*> oldTable = _table;
        int oldCapacity = _capacity;
        _capacity = capacity;

        _table.clear();
        _table.resize(_capacity, nullptr);


        for (int i = 0; i < oldCapacity; i++) {
            HashNode* current = oldTable[i];
            if (current != nullptr)
                insert(current->_key, current->_value);
        }
    }

    int getCapacity() {
        return _capacity;
    }

private:
    // Внутренний класс для хранения пар "ключ-значение"
    struct HashNode {
    public:
        int _key;
        ValueType _value;
        HashNode* _next;

        HashNode(const int k, const ValueType& v)
                : _key(k), _value(v), _next(nullptr) {}
    };

    // Приватные члены класса
    std::vector<HashNode*> _table;
    int _capacity;
    IHashFunction* _hashFunction;

    // Вспомогательные методы
    void clear() {
        for (int i = 0; i < _capacity; i++) {
            delete _table[i];
            _table[i] = nullptr;
        }
    }

    void copyTable(const HashTable& other) {
        _table.resize(other._capacity, nullptr);

        for (int i = 0; i < other._capacity; i++) {
            if (other._table[i] != nullptr)
                insert(other._table[i]->_key, other._table[i]->_value);
        }
    }
    
    void getNodeAndParent(const int key, HashNode*& node, HashNode*& parent) {
        int hash = _hashFunction->computeHash(key, _capacity);
        node = _table[hash];
        parent = nullptr;

        while (node != nullptr && node->_key != key) {
            parent = node;
            node = node->_next;
        }
    }

    HashNode* containsGetNode(const int key) {
        int hash = _hashFunction->computeHash(key, _capacity);
        HashNode* current = _table[hash];

        while (current != nullptr && current->_key != key) {
            current = current->_next;
        }
        return current;
    }

    int findIndex(HashNode* elem) const {
        for (int i = 0; i < _capacity; i++)
            if (_table[i] == elem) {
                return i;
            }
        return -1;
    }
};

#endif //LAB6_HASHING_HASHTABLE_H