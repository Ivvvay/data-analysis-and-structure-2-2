#include "HuffmanCoding.h"

HuffmanCoding::HuffmanCoding() : _root(nullptr) {}

HuffmanCoding::~HuffmanCoding() {
    delete _root;
}