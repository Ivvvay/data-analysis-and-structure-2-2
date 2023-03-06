#include <iostream>
#include <fstream>
#include <random>

bool createFileWithRandomNumbers(const std::string& fileName, const int numbersCount, const int maxNumberValue);


bool createFileWithRandomNumbers(const std::string& fileName, const int numbersCount, const int maxNumberValue) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::ofstream file(fileName);

    if(!file.is_open())
        return false;

    for (int i = 0; i < numbersCount; i++) {
        int numders = gen() % maxNumberValue;
        file << numders << " ";
    }

    file.close();
    return true;
}