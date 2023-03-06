#include <iostream>
#include <fstream>
#include <random>

bool createFileWithRandomNumbers(const std::string& fileName, const int numbersCount, const int maxNumberValue);
bool isFileContainsSortedArray(const std::string& fileName);
void splitFile(const std::string& fileName, std::fstream* F);
void mergeFile(std::fstream* F, std::fstream* G);


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

void mergeFile(std::fstream* F, std::fstream* G) {
    if (!F[0].is_open() || !F[1].is_open() || !G[0].is_open() || !G[1].is_open()) {
        std::cerr << "Error in 'void mergeFile'" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    int number1[2];
    int number2[2];
    int n = 0;
    int k;

    F[0] >> number1[0];
    F[1] >> number1[1];
    while (!F[0].eof() && !F[1].eof()) {
        if (number1[0] < number1[1]) k = 0;
        else k = 1;

        G[n] << number1[k] << " ";
        F[k] >> number2[k];

        if (number1[k] <= number2[k])
            number1[k] = number2[k];
        else {
            G[n] << number1[1 - k] << " ";
            F[1 - k] >> number2[1 - k];

            while (!F[1 - k].eof() && (number1[1 - k] <= number2[1 - k])) {
                number1[1 - k] = number2[1 - k];
                G[n] << number1[1 - k] << " ";
                F[1 - k] >> number2[1 - k];
            }
            number1[1 - k] = number2[1 - k];
            number1[k] = number2[k];
            n = 1 - n;
        }
    }

    while (!F[0].eof()) {
        G[n] << number1[0] << " ";
        F[0] >> number2[0];

        while (!F[0].eof() && (number1[0] <= number2[0])) {
            number1[0] = number2[0];
            G[n] << number1[0] << " ";
            F[0] >> number2[0];
        }
        number1[0] = number2[0];
        n = 1 - n;
    }

    while (!F[1].eof()) {
        G[n] << number1[1] << " ";
        F[1] >> number2[1];

        while (!F[1].eof() && (number1[1] <= number2[1])) {
            number1[1] = number2[1];
            G[n] << number1[1] << " ";
            F[1] >> number2[1];
        }
        number1[1] = number2[1];
        n = 1 - n;
    }
}