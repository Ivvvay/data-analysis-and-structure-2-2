#ifndef LAB5_HUFFMANCODING_SET_H
#define LAB5_HUFFMANCODING_SET_H
#include <iostream>

class Set {
public:
    Set();
    Set(unsigned char symbol);
    Set(const Set& other);
    ~Set() = default;

    Set& operator=(const Set& other);
    Set operator|(const Set& other);
    Set operator|=(const Set& other);

    bool inSet(unsigned char symbol);

    void add(unsigned char symbol);

    friend std::ostream& operator<<(std::ostream& out, const Set& other) {
        for (int i = 0; i < 256; i++) {
            int index = i / 8;
            int bit = i % 8;
            if ((other._setArray[index] & (1 << (7 - bit))) != 0)
                out << (unsigned char)i;
        }
        return out;
    }
private:
    static const int _setSize = 32;
    unsigned char _setArray[_setSize];
};


#endif //LAB5_HUFFMANCODING_SET_H
