#include "HuffmanCoding.h"

HuffmanCoding::HuffmanCoding() : _root(nullptr) {}

HuffmanCoding::~HuffmanCoding() {
    delete _root;
}

void HuffmanCoding::build(const std::string &text) {
    std::unordered_map<std::string, int> frequencyTable;
    buildFrequencyTable(text, frequencyTable);
    buildTree(frequencyTable);
}

double HuffmanCoding::encode(const std::string &inputFile, const std::string &outputFile) {

}

bool HuffmanCoding::decode(const std::string &inputFile, const std::string &outputFile) {

}

void HuffmanCoding::buildFrequencyTable(const std::string &text, std::unordered_map<std::string, int> &frequencyTable) {
    for (char c : text) {
        std::string symbol(1, c);
        ++frequencyTable[symbol];
    }
}

void HuffmanCoding::buildTree(const std::unordered_map<std::string, int> &frequencyTable) {
    std::list<Node*> nodes;

    for (const auto& pair : frequencyTable) {
        nodes.push_back(new Node(pair.first, pair.second));
    }

    while (nodes.size() > 1) {
        nodes.sort([](const Node* a, const Node* b) {
            return a->getFrequency() < b->getFrequency();
        });

        Node* left = nodes.front();
        nodes.pop_front();

        Node* right = nodes.front();
        nodes.pop_front();

        Node* parent = new Node(left->getData() + right->getData(), left->getFrequency() + right->getFrequency());
        parent->setLeft(left);
        parent->setRight(right);

        nodes.push_back(parent);
    }
    _root = nodes.front();
}