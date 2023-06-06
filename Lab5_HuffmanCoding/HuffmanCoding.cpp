#include "HuffmanCoding.h"

HuffmanCoding::Node::Node() :
        _symbols(Set()), _frequency(0),
        _left(nullptr), _right(nullptr) {}

HuffmanCoding::Node::Node(unsigned char symbol, int frequency) :
        _symbols(Set(symbol)), _frequency(frequency),
        _left(nullptr), _right(nullptr) {}

HuffmanCoding::Node::Node(HuffmanCoding::Node *left, HuffmanCoding::Node *right) :
        _symbols(left->_symbols | right->_symbols),
        _frequency(left->_frequency + right->_frequency),
        _left(left), _right(right) {}

Set HuffmanCoding::Node::symbols() {
    return _symbols;
}

int HuffmanCoding::Node::frequency() {
    return _frequency;
}

HuffmanCoding::Node *HuffmanCoding::Node::left() const {
    return _left;
}

HuffmanCoding::Node *HuffmanCoding::Node::right() const {
    return _right;
}

HuffmanCoding::HuffmanCoding() : _root(nullptr) {}

HuffmanCoding::~HuffmanCoding() {
    _delete(_root);
}

void HuffmanCoding::build(const std::string &inputFile) {
    _delete(_root);

    std::ifstream text(inputFile);
    if (!text)
        std::cerr << "Error opening files." << std::endl;

    int frequencies[256];
    for (int i = 0; i < 256; i++)
        frequencies[i] = 0;

    char ch;
    while (text.get(ch))
        frequencies[(unsigned char) ch]++;

    text.close();

    std::vector<Node*> nodes;

    for (int i = 0; i < 256; i++) {
        if (frequencies[i] != 0) {
            Node* temp = new Node((unsigned char)i, frequencies[i]);
            nodes.push_back(temp);
        }
    }

    std::sort(nodes.begin(), nodes.end(),[](Node* a, Node* b){
        return a->frequency() < b->frequency();
    });

    while (nodes.size() > 1) {
        Node* temp = new Node(nodes[0], nodes[1]);
        nodes.erase(nodes.begin());
        nodes.erase(nodes.begin());
        nodes.push_back(temp);
        std::sort(nodes.begin(), nodes.end(),[](Node* a, Node* b){
            return a->frequency() < b->frequency();
        });
    }
    _root = nodes[0];
}

double HuffmanCoding::encode(const std::string &inputFile, const std::string &outputFile) {
    build(inputFile);


    std::ifstream input(inputFile);
    std::ofstream output(outputFile);

    if (!input || !output) {
        std::cerr << "Error opening files." << std::endl;
        return -1;
    }

    if (_root == nullptr)
        return 0;

    int result_count_of_bits = 0;
    int input_count_of_bits = 0;

    char ch;
    while (input.get(ch)) {
        Node* temp = _root;
        while (temp->left() != nullptr && temp->right() != nullptr) {
            if (temp->left()->symbols().inSet(ch)){
                temp = temp->left();
                output << '0';
            } else {
                temp = temp->right();
                output << '1';
            }
            result_count_of_bits++;
        }
        input_count_of_bits++;
    }

    if (_root->left() == nullptr && _root->right() == nullptr) {
        for (int i = 0; i < input_count_of_bits; i++)
            output << '1';
        result_count_of_bits = input_count_of_bits;
    }

    input.close();
    output.close();

    return (double) result_count_of_bits / ((double) input_count_of_bits * 8);
}

bool HuffmanCoding::decode(const std::string &inputFile, const std::string &outputFile) {
    if (_root == nullptr)
        return false;

    std::ifstream input(inputFile);
    std::ofstream output(outputFile);

    if (!input || !output) {
        std::cerr << "Error opening files." << std::endl;
        return false;
    }

    char ch;
    Node* temp = _root;
    while (input.get(ch)) {
        switch (ch) {
            case '0':
                if(temp->left() != nullptr)
                    temp = temp->left();
                break;
            case '1':
                if(temp->right() != nullptr)
                    temp = temp->right();
                break;
            default:
                return false;
        }
        if (temp->left() == nullptr && temp->right() == nullptr) {
            output << temp->symbols();
            temp = _root;
        }
    }

    input.close();
    output.close();

    return true;
}

void HuffmanCoding::_delete(HuffmanCoding::Node *root) {
    if (root != nullptr) {
        _delete(root->left());
        _delete(root->right());
        delete root;
    }
}
