#ifndef DATA_ANALYSIS_AND_STRUCTURE_2_2_NATURALMERGE4_H
#define DATA_ANALYSIS_AND_STRUCTURE_2_2_NATURALMERGE4_H

#include <iostream>
#include <fstream>
#include <random>

bool createFileWithRandomNumbers(const std::string& fileName, const int numbersCount, const int maxNumberValue);
bool isFileContainsSortedArray(const std::string& fileName);
void splitFile(const std::string& fileName, std::fstream* F);
void mergeFile(std::fstream* F, std::fstream* G);
bool fileIsEmpty(std::fstream* F, std::fstream* G);
void sortFile(const std::string& fileName);
int createAndSortFile(const std::string& fileName, const int numbersCount, const int maxNumberValue);
void NaturalMerge4();

#endif //DATA_ANALYSIS_AND_STRUCTURE_2_2_NATURALMERGE4_H
