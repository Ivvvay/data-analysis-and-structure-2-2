#ifndef LAB6_HASHING_HASHTABLE_H
#define LAB6_HASHING_HASHTABLE_H
#include <iostream>
#include <vector>
#include <cmath>

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
        const int c = 3 % 5;
        const int d = 4 % 7;
        int i = 1; int hash = key % tableSize;

        return (hash + c * i + d * i * i) % tableSize;
    }
                return hash;
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

        return static_cast<int>(hash * a * tableSize) % tableSize;
            if (hash < tableSize)
                return hash;
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
        int i = 1; int hash = key % tableSize;

        return (hash + i * (1 + key % (tableSize - 2))) % tableSize;
            if (hash < tableSize)
                return hash;
    }
    IHashFunction *clone() const override {
        return new HashFunction3(*this);
    }
};

template <typename KeyType, typename ValueType>
class HashTable {
public:
    // Конструкторы
    HashTable() : _size(0), _capacity(8), _hashFunction(new HashFunction1()) {
        _table.resize(_capacity, nullptr);
    }

    explicit HashTable(int tableSize) : _size(0), _capacity(tableSize), _hashFunction(new HashFunction1()) {
        _table.resize(_capacity, nullptr);
    }

    HashTable(const HashTable& other) : _size(0), _capacity(other._capacity), _hashFunction(other._hashFunction) {
        copyTable(other);
    }

    // Деструктор
    ~HashTable() {
        clear();
    }

    // Методы
    void insert(const KeyType& key, const ValueType& value) {
        int hash = _hashFunction->computeHash(key, _capacity);
        auto* newNode = new HashNode(key, value);

        if (_table[hash] == nullptr) {
            _table[hash] = newNode;
        } else {
            HashNode* current = _table[hash];
            while (current->_next != nullptr) {
                if (current->_key == key) {
                    current->_value = value;
                    delete newNode;
                    return;
                }
                current = current->_next;
            }
            if (current->_key == key) {
                current->_value = value;
                delete newNode;
                return;
            }
            current->_next = newNode;
        }
        _size++;
    }
    void remove(const KeyType& key) {
        int hash = _hashFunction->computeHash(key, _capacity);
        HashNode* current = _table[hash];
        HashNode* previous = nullptr;

        while (current != nullptr) {
            if (current->_key == key) {
                if (previous == nullptr) {
                    _table[hash] = current->_next;
                } else {
                    previous->_next = current->_next;
                }
                delete current;
                _size--;
                return;
            }
            previous = current;
            current = current->_next;
        }
    }

    bool contains(const KeyType& key) const {
        int hash = _hashFunction->computeHash(key, _capacity);
        HashNode* current = _table[hash];

        while (current != nullptr) {
            if (current->_key == key) {
                return true;
            }
            current = current->_next;
        }
        return false;
    }

    void printTable() const {
        for (int i = 0; i < _capacity; i++) {
            //if (_table[i] != nullptr) {
            std::cout << "Hash: " << i << " - ";
            HashNode* current = _table[i];
            while (current != nullptr) {
                std::cout << "(" << current->_key << ", " << current->_value << ")";
                current = current->_next;
            }
            std::cout << std::endl;
            //}
        }
        std::cout << std::endl;
    }
    void changeHashFunction(int hashFunctionIndex) {
        delete _hashFunction;

        switch (hashFunctionIndex) {
            case 1:
                _hashFunction = new HashFunction1();
                break;
            case 2:
                _hashFunction = new HashFunction2();
                break;
            case 3:
                _hashFunction = new HashFunction3();
                break;
            default:
                _hashFunction = new HashFunction1();
                break;
        }

        rehash();
    }

    void resize(int newSize) {
        _capacity = newSize;
        rehash();
    }

    HashTable& operator=(const HashTable& other) {
        if (this != &other) {
            clear();
            delete _hashFunction;
            _capacity = other._capacity;
            _hashFunction = other._hashFunction;
            _table.resize(_capacity, nullptr);
            copyTable(other);
        }
        return *this;
    }

    void rehash() {
        std::vector<HashNode*> oldTable = _table;
        int oldCapacity = _capacity;

        _table.clear();
        _table.resize(_capacity, nullptr);
        _size = 0;

        for (size_t i = 0; i < oldCapacity; i++) {
            HashNode* current = oldTable[i];
            while (current != nullptr) {
                insert(current->_key, current->_value);
                HashNode* temp = current;
                current = current->_next;
                delete temp;
            }
        }
    }

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

    // Вспомогательные методы
    void clear() {
        for (int i = 0; i < _capacity; i++) {
            HashNode* current = _table[i];
            while (current != nullptr) {
                HashNode* temp = current;
                current = current->_next;
                delete temp;
            }
            _table[i] = nullptr;
        }
        _size = 0;
    }

    void copyTable(const HashTable& other) {
        _table.resize(other._capacity, nullptr);
        _size = other._size;
        _capacity = other._capacity;

        for (int i = 0; i < other._capacity; i++) {
            HashNode* current = other._table[i];
            while (current != nullptr) {
                auto* newNode = new HashNode(current->_key, current->_value);
                newNode->_next = _table[i];
                _table[i] = newNode;
                current = current->_next;
            }
        }
    }
};

#endif //LAB6_HASHING_HASHTABLE_H
