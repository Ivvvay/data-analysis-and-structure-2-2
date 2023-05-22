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
    std::ifstream input(inputFile);
    std::ofstream output(outputFile, std::ios::binary);

    if (!input || !output) {
        std::cerr << "Error opening files." << std::endl;
        return -1;
    }

    std::string text((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
    input.close();

    std::unordered_map<std::string, int> frequencyTable;
    buildFrequencyTable(text, frequencyTable);
    buildTree(frequencyTable);

    std::unordered_map<std::string, std::string> codeTable;
    buildCodeTable(_root, "", codeTable);

    std::string encodedText;
    encodeText(text, codeTable, encodedText);

    int padLength = 8 - (encodedText.length() % 8);
    std::string padding = std::string(padLength, '0');
    std::bitset<8> padSize(padLength);

    std::string outputText;
    outputText += padSize.to_string() + padding + encodedText;

    output.write(outputText.c_str(), outputText.length());
    output.close();

    double compressionRatio = static_cast<double>(outputText.length()) / (text.length() * sizeof(char));
    return compressionRatio;
}

bool HuffmanCoding::decode(const std::string &inputFile, const std::string &outputFile) {
    std::ifstream input(inputFile, std::ios::binary);
    std::ofstream output(outputFile);

    if (!input || !output) {
        std::cerr << "Error opening files." << std::endl;
        return false;
    }

    std::string encodedText((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
    input.close();

    std::bitset<8> padSize(encodedText.substr(0, 8));
    int padLength = padSize.to_ulong();
    encodedText = encodedText.substr(8 + padLength);

    int index = 0;
    std::string decodedText;
    while (index < encodedText.length())
        decodeText(encodedText, _root, index, decodedText);

    output.write(decodedText.c_str(), decodedText.length());
    output.close();

    return true;
}

void HuffmanCoding::buildFrequencyTable(const std::string &text, std::unordered_map<std::string, int> &frequencyTable) {
    for (char c : text) {
        std::string symbol(1, c);
        ++frequencyTable[symbol];
    }
}

void HuffmanCoding::buildTree(const std::unordered_map<std::string, int> &frequencyTable) {
    std::list<Node*> nodes;

    for (const auto& pair : frequencyTable)
        nodes.push_back(new Node(pair.first, pair.second));

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

void HuffmanCoding::buildCodeTable(HuffmanCoding::Node *node, const std::string &code,
                                   std::unordered_map<std::string, std::string> &codeTable) {
    if (!node->getLeft() && !node->getRight()) {
        codeTable[node->getData()] = code;
        return;
    }

    buildCodeTable(node->getLeft(), code + "0", codeTable);
    buildCodeTable(node->getRight(), code + "1", codeTable);
}

void HuffmanCoding::encodeText(const std::string &text, const std::unordered_map<std::string,
        std::string> &codeTable, std::string &encodedText) {
    for (char c : text) {
        std::string symbol(1, c);
        encodedText += codeTable.at(symbol);
    }
}

void HuffmanCoding::decodeText(const std::string &encodedText, HuffmanCoding::Node *node,
                               int &index, std::string &decodedText) {
    if (!node->getLeft() && !node->getRight()) {
        decodedText += node->getData();
        return;
    }
    if (index >= encodedText.length())
        return;

    if (encodedText[index] == '0')
        decodeText(encodedText, node->getLeft(), ++index, decodedText);
    else
        decodeText(encodedText, node->getRight(), ++index, decodedText);
}