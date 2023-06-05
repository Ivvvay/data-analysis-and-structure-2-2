#include "Set.h"

Set::Set() {
    for (int i = 0; i < _setSize; i++)
        _setArray[i] = (char) 0;
}

Set::Set(unsigned char symbol) {
    for (int i = 0; i < _setSize; i++)
        _setArray[i] = (unsigned char) 0;

    int index = (int) symbol / 8;
    int bit = (int) symbol % 8;
    _setArray[index] |= 1 << (7 - bit);
}

Set::Set(const Set& other) {
    for (int i = 0; i < _setSize; i++)
        _setArray[i] = other._setArray[i];
}

Set& Set::operator=(const Set& other) {
    if (this == &other)
        return *this;

    for (int i = 0; i < _setSize; i++)
        _setArray[i] = other._setArray[i];

    return *this;
}

Set Set::operator|(const Set& other) {
    Set tmp(*this);
    tmp |= other;
    return tmp;
}

Set Set::operator|=(const Set& other) {
    for (int i = 0; i < _setSize; i++)
        _setArray[i] |= other._setArray[i];

    return *this;
}

bool Set::inSet(unsigned char symbol) {
    int index = (int) symbol / 8;
    int bit = (int) symbol % 8;

    return (_setArray[index] & (1 << (7 - bit))) != 0;
}

void Set::add(unsigned char symbol) {
    if (!inSet(symbol)) {
        int index = (int) symbol / 8;
        int bit = (int) symbol % 8;
        _setArray[index] |= 1 << (7 - bit);
    }
}