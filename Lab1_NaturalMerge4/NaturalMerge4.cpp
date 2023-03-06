#include <iostream>
#include <fstream>
#include <random>

bool createFileWithRandomNumbers(const std::string& fileName, const int numbersCount, const int maxNumberValue);
bool isFileContainsSortedArray(const std::string& fileName);


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

bool isFileContainsSortedArray(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open())
        return false;

    int num1, num2;
    file >> num1;
    while(!file.eof()) {
        file >> num2;
        if (num1 > num2) {
            file.close();
            return false;
        }
        num1 = num2;
    }

    file.close();
    return true;
}