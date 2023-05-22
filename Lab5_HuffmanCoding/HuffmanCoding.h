#ifndef LAB5_HUFFMANCODING_HUFFMANCODING_H
#define LAB5_HUFFMANCODING_HUFFMANCODING_H
#include <iostream>
#include <fstream>
#include <list>

class HuffmanCoding {
public:
    class Node {
    public:
        Node(std::string data, int frequency) :
                _data(std::move(data)), _frequency(frequency), _left(nullptr), _right(nullptr) {}
        ~Node() {
            delete _left;
            delete _right;
        }
        std::string getData() const { return _data; };
        void setData(std::string data) { _data = data; }
        int getFrequency() const { return _frequency; };
        void setFrequency(int frequency) { _frequency = frequency; }
        Node* getLeft() const { return _left; };
        void setLeft(Node* left) { _left = left; }
        Node* getRight() const { return _right; };
        void setRight(Node* right) { _right = right; }

    private:
        std::string _data;
        int _frequency = 1;
        Node* _left = nullptr;
        Node* _right = nullptr;
    };

    HuffmanCoding();
    ~HuffmanCoding();
};


#endif //LAB5_HUFFMANCODING_HUFFMANCODING_H
