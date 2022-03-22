//
// Created by kristapsn on 13.03.22.
//

#include "wordlist.h"

std::ifstream wordlist::openFile(const std::string &filename) {
    std::ifstream file{filename};
    std::string output;
    std::string line;

    if (!file) {
        std::cout << "Err: cannot open " << filename << " file" << "\n\nQuitting...\n";
        exit(1);
    } else {
        return file;
    }
}


std::string wordlist::findWordByValue(std::ifstream &file, const unsigned int &value) {
    std::string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            unsigned int sum = letterCalc::calculateSum(line);
            if (sum == value) {
                fileReturnToBeginning(file);
                return line;
            }
        }
        fileReturnToBeginning(file);
    } else {
        std::cout << "file is not open anymore\n";
    }
    return "";
}

unsigned int wordlist::countResultsEvenOdd(std::ifstream &file, bool odd) {
    std::string line;

    int matchingResultsCounter = 0;
    if (file.is_open()) {
        while (getline(file, line)) {
            unsigned int sum = letterCalc::calculateSum(line);
            if (sum % 2 == odd) {
                matchingResultsCounter++;
            }
        }
        fileReturnToBeginning(file);
    } else {
        std::cout << "file is not open anymore\n";
    }
    return matchingResultsCounter;
}

std::pair<unsigned int, unsigned int> wordlist::findMostCommonLetterSum(std::ifstream &file) {
    std::string line;
    std::map<unsigned int, unsigned int> sumsCount;

    if (file.is_open()) {
        while (getline(file, line)) {
            unsigned int sum = letterCalc::calculateSum(line);
            if (!sumsCount.contains(sum)) {
                sumsCount[sum] = 1;
            } else {
                sumsCount[sum]++;
            }
        }
        fileReturnToBeginning(file);
    } else {
        std::cout << "file is not open anymore\n";
    }

    std::pair<unsigned int, unsigned int> highest = {0, 0};
    for (std::pair<unsigned int, unsigned int> s: sumsCount) {
        if (s.second > highest.second) {
            highest = s;
        }
    }

    return highest;
}


void wordlist::fileReturnToBeginning(std::ifstream &file) {
    file.clear();
    file.seekg(0);
}