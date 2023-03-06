#include <iostream>
#include <fstream>
#include <random>

bool createFileWithRandomNumbers(const std::string& fileName, const int numbersCount, const int maxNumberValue);
bool isFileContainsSortedArray(const std::string& fileName);
void splitFile(const std::string& fileName, std::fstream* F);



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

void splitFile(const std::string& fileName, std::fstream* F) {
    std::ifstream file(fileName);
    F[0].open("F1.txt", std::fstream::out);
    F[1].open("F2.txt", std::fstream::out);

    if (!F[0].is_open() || !F[1].is_open() || !file.is_open()) {
        std::cerr << "Error in 'void splitFile'" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    long int number1;
    long int number2;
    int n = 0;

    file >> number1;
    while (!file.eof()) {
        F[n] << number1 << " ";
        file >> number2;
        while (!file.eof() && number1 <= number2) {
            number1 = number2;
            F[n] << number1 << " ";
            file >> number2;
        }
        number1 = number2;
        n = 1 - n;
    }

    file.close();
    F[0].close();
    F[1].close();
}