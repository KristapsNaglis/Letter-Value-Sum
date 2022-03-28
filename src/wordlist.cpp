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

std::vector<twoWordsOneSum> wordlist::findPairWithEqualSum(std::ifstream &file, unsigned int diff) {
    std::string line;
    std::unordered_map<unsigned int, std::vector<std::string>> sums;

    if (file.is_open()) {
        while (getline(file, line)) {
            // Save each word in a vector inside a map that belongs to its sum
            sums[letterCalc::calculateSum(line)].push_back(line);
        }
        fileReturnToBeginning(file);
    }

    // Create a place where to store the found matches
    std::vector<twoWordsOneSum> matches;

    // Loop through all sums and their corresponding words
    for (const std::pair<unsigned int, std::vector<std::string>> s: sums) {

        // Nested loops to test all word combinations in the same sum vector
        for (int i = 0; i < s.second.size(); ++i) {
            const unsigned int referenceWordLen = s.second[i].length();

            for (int j = i + 1; j < s.second.size(); ++j) {
                const unsigned int currentWordLen = s.second[j].length();

                // Find which word is longer and calculate difference accordingly
                unsigned int diffLen;
                if (referenceWordLen > currentWordLen) {
                    diffLen = referenceWordLen - currentWordLen;
                } else {
                    diffLen = currentWordLen - referenceWordLen;
                }

                if (diffLen == diff) {
                    matches.push_back({{s.second[i], s.second[j]}, s.first});
                }
            }
        }
    }


    return matches;
}


void wordlist::fileReturnToBeginning(std::ifstream &file) {
    file.clear();
    file.seekg(0);
}