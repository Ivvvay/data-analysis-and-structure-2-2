#include "HuffmanCoding.h"

int main() {
    HuffmanCoding huffman;

    // Пример использования
    std::string inputFile = "input.txt";
    std::string encodedFile = "encoded.bin";
    std::string decodedFile = "decoded.txt";

    std::string inputText = "Hello World!";
    std::ofstream inputFileStream(inputFile);
    inputFileStream << inputText;
    inputFileStream.close();

    huffman.build(inputText);

    double compressionRatio = huffman.encode(inputFile, encodedFile);
    std::cout << "Compression ratio: " << compressionRatio << std::endl;

    bool success = huffman.decode(encodedFile, decodedFile);
    if (success) {
        std::ifstream decodedFileStream(decodedFile);
        std::string decodedText((std::istreambuf_iterator<char>(decodedFileStream)), std::istreambuf_iterator<char>());
        decodedFileStream.close();
        std::cout << "Decoded text: " << decodedText << std::endl;
    } else {
        std::cout << "Decoding failed." << std::endl;
    }

    return 0;
}
