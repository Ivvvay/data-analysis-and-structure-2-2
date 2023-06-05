#ifndef LAB5_HUFFMANCODING_HUFFMANCODING_H
#define LAB5_HUFFMANCODING_HUFFMANCODING_H
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include "Set.h"

class HuffmanCoding {
public:
    class Node {
    public:
        Node();
        Node(unsigned char symbol, int frequency);
        Node(Node* left, Node* right);
        ~Node() = default;

        Set symbols();
        int frequency();

        Node* left() const;
        Node* right() const;

    private:
        Set _symbols;
        int _frequency;
        Node* _left;
        Node* _right;
    };

    HuffmanCoding();
    ~HuffmanCoding();

    void build(const std::string& inputFile);
    double encode(const std::string& inputFile, const std::string& outputFile);
    bool decode(const std::string& inputFile, const std::string& outputFile);

private:
    Node* _root = nullptr;
    void _delete(Node* root);
};


#endif //LAB5_HUFFMANCODING_HUFFMANCODING_H
