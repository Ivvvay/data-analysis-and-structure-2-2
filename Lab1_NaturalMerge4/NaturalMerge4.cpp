#include "NaturalMerge4.h"

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

bool fileIsEmpty(std::fstream* F, std::fstream* G) {
    F[0].open("F1.txt", std::ios::in);
    F[1].open("F2.txt", std::ios::in);
    G[0].open("G1.txt", std::ios::in);
    G[1].open("G2.txt", std::ios::in);

    if (!G[0] || !G[1] || !F[0] || !F[1]) {
        std::cerr << "Error in read G1 and G2 (F1 and F2)! ";
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 2; i++) {
        if (F[i].peek() == EOF) {
            F[0].close(); F[1].close(); G[0].close(); G[1].close();
            return true;
        }
        if (G[i].peek() == EOF) {
            F[0].close(); F[1].close(); G[0].close(); G[1].close();
            return true;
        }
    }

    F[0].close(); F[1].close(); G[0].close(); G[1].close();
    return false;
}

void sortFile(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Error: File A isn't open" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    ///Split
    std::fstream F[2];
    splitFile(fileName, F);

    ///Merge
    std::fstream G[2];
    bool flag = false;
    while (!flag) {
        F[0].open("F1.txt", std::ios::in);
        F[1].open("F2.txt", std::ios::in);
        if (!F[0] || !F[1]) {
            std::cerr << "Error in create F1 and F2! ";
            exit(EXIT_FAILURE);
        }
        G[0].open("G1.txt", std::ios::out);
        G[1].open("G2.txt", std::ios::out);
        if (!G[0] || !G[1]) {
            std::cerr << "Error in create G1 and G2! ";
            exit(EXIT_FAILURE);
        }

        mergeFile(F, G);

        for (int i = 0; i < 2; i++) {
            F[i].close();
            G[i].close();
        }

        if (fileIsEmpty(F, G))
            break;

        F[0].open("F1.txt", std::ios::out);
        F[1].open("F2.txt", std::ios::out);
        if (!F[0] || !F[1]) {
            std::cerr << "Error in create F1 and F2";
            exit(EXIT_FAILURE);
        }
        G[0].open("G1.txt", std::ios::in);
        G[1].open("G2.txt", std::ios::in);
        if (!G[0] || !G[1]) {
            std::cerr << "Error in create G1 and G2! ";
            exit(EXIT_FAILURE);
        }

        mergeFile(G, F);

        for (int i = 0; i < 2; i++) {
            F[i].close();
            G[i].close();
        }

        flag = fileIsEmpty(F, G);
    }
    file.close();
    F[0].close();
    F[1].close();
}

int createAndSortFile(const std::string& fileName, const int numbersCount, const int maxNumberValue) {
    if (!createFileWithRandomNumbers(fileName, numbersCount, maxNumberValue))
        return -1;

    sortFile(fileName);

    if (!isFileContainsSortedArray("F1.txt")
        && !isFileContainsSortedArray("G1.txt"))
        return -2;

    return 1;
}

void NaturalMerge4() {
    std::string fileName = "F.txt";
    const int numbersCount = 10000;
    const int maxNumberValue = 100000;

    for (int i = 1; i < 11; i++) {
        switch (createAndSortFile(fileName, numbersCount, maxNumberValue)) {
            case 1:
                std::cout << "Test passed." << std::endl;
                break;

            case -1:
                std::cout << "Test failed: can't create file." << std::endl;
                break;

            case -2:
                std::cout << "Test failed: file isn't sorted." << std::endl;
                break;
        }
    }
}