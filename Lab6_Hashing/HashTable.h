#ifndef LAB6_HASHING_HASHTABLE_H
#define LAB6_HASHING_HASHTABLE_H
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

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

    explicit HashTable(int tableSize) : _size(0), _capacity(tableSize), _hashFunction(new HashFunction1()) {
        _table.resize(_capacity, nullptr);
    }

    HashTable(const HashTable& other) : _size(0), _capacity(other._capacity), _hashFunction(other._hashFunction->clone()) {
        copyTable(other);
    }

    // Деструктор
    ~HashTable() {
        clear();
        delete _hashFunction;
    }

    // Методы
    bool insert(const int& key, const ValueType& value) {
        /*if (_size + 1 > _capacity) {
            std::cerr << "Error: Number of elements exceeds table capacity. Resizing the table or performing rehashing is recommended." << std::endl;
            return false;
        }*/

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
                    return true;
                }
                current = current->_next;
            }
            if (current->_key == key) {
                current->_value = value;
                delete newNode;
                return true;
            }
            current->_next = newNode;

            int i = 0;
            while (i < _capacity && _table[i] != nullptr)
                i++;

            if (i >= _capacity)
                return false;

            _table[i] = newNode;
        }
        _size++;
        return true;
    }
    bool remove(const int& key) {
        int hash = _hashFunction->computeHash(key, _capacity);
        HashNode* current = _table[hash];
        HashNode* previous = nullptr;

        while (current != nullptr) {
            if (current->_key == key) {
                if (previous == nullptr) {
                    _table[hash] = current->_next;
                    for (int i = 0; i < _capacity; i++)
                        if (_table[i] == current->_next && i != hash)
                            _table[i] = _table[i]->_next;
                } else {
                    previous->_next = current->_next;

                    for (int i = 0; i < _capacity; i++)
                        if (_table[i]->_key == key)
                            _table[i] = _table[i]->_next;
                }
                delete current;
                _size--;
                return true;
            }
            previous = current;
            current = current->_next;
        }
    }

    bool contains(const int& key) const {
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
        std::cout << "Hash" << std::setw(18) << "(Key, Value)" << std::setw(30) << "(_table[i], _next)" << std::endl;
        for (int i = 0; i < _capacity; i++) {
            std::cout << "Hash " << i << ":" << std::setw(4);
            HashNode* current = _table[i];
            if (current != nullptr) { // while (current != nullptr)
                std::cout << "(" << current->_key << ", " << current->_value << ") \t ";
                std::cout << "(" << current << ", " << current->_next << ") ";
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

    void resize(int newSize) {
        _capacity = newSize;
        rehash();
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

        // Ключ не найден, вставим новый узел с значением
        insert(key, ValueType());

        return _table[index]->_value;
    }

    void rehash() {
        std::vector<HashNode*> oldTable = _table;
        int oldCapacity = _capacity;

        _table.clear();
        _table.resize(_capacity, nullptr);
        _size = 0;

        for (int i = 0; i < oldCapacity; i++) {
            HashNode* current = oldTable[i];
            while (current != nullptr) {
                insert(current->_key, current->_value);
                HashNode* temp = current;
                current = current->_next;
                if (current != nullptr)
                    delete temp;
            }
        }
    }

private:
    // Внутренний класс для хранения пар "ключ-значение"
    struct HashNode {
    public:
        int _key;
        ValueType _value;
        HashNode* _next;

        HashNode(const int& k, const ValueType& v)
                : _key(k), _value(v), _next(nullptr) {}
    };

    // Приватные члены класса
    std::vector<HashNode*> _table;
    int _size;
    int _capacity;
    IHashFunction* _hashFunction;

    // Вспомогательные методы
    void clear() {
        for (int i = 0; i < _capacity; i++) {
            HashNode* current = _table[i];
            while (current != nullptr) {
                HashNode* temp = current;
                current = current->_next;
                if (current != nullptr)
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
