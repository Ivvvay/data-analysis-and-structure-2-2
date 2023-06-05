#ifndef LAB5_HUFFMANCODING_SET_H
#define LAB5_HUFFMANCODING_SET_H

class Set {
public:
    Set();
    Set(unsigned char symbol);
    Set(const Set& other);
    ~Set() = default;

    Set& operator=(const Set& other);
    Set operator|(const Set& other);
    Set operator|=(const Set& other);

private:
    static const int _setSize = 32;
    unsigned char _setArray[_setSize];
};


#endif //LAB5_HUFFMANCODING_SET_H
