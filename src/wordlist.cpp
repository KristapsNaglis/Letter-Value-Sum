//
// Created by kristapsn on 13.03.22.
//

#include "wordlist.h"

// ===
// Public functions
// ===

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

// Task 1
// Find a specific word by knowing its value in a wordlist file
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

// Task 2
// Count even or odd letter sums in a wordlist file
unsigned int wordlist::countResultsEvenOdd(std::ifstream &file, const bool &odd) {
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

// Task 3
// Find most common letter sum in a wordlist file
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

// Task 4
// Finds word pairs in a wordlist file which:
//  * share same value
//  * both words have a length difference of "diff"
std::vector<twoWordsOneSum> wordlist::findPairWithSameSum(std::ifstream &file, const unsigned int &diff) {
    const auto sums = sortWordsBySumAndLen(file);
    std::vector<twoWordsOneSum> matches;

    // Loop through all word SUM VALUES
    for (const auto &sum: sums) {
        if (sum.second.size() > 2) {
            // Loop and store all LENGTH values in sum
            std::vector<unsigned int> lengths;
            for (const auto &len: sum.second) {
                lengths.push_back(len.first);
            }
            // Loop through all the saved LENGTHS combinations and check if there is a difference of 11
            for (unsigned int i = 0; i < lengths.size() - 1; ++i) {
                for (unsigned int j = 0; j < lengths.size(); ++j) {
                    if (lengths[j] - lengths[i] == 11) {
                        // Loop through all LENGTHS again and save to a temporary vector if the word is under OK sum
                        std::vector<std::string> tmp;
                        for (const auto &len: sum.second) {
                            if (len.first == lengths[i] || len.first == lengths[j]) {
                                tmp.push_back(len.second[0]);
                            }
                        }
                        matches.push_back({{tmp[0], tmp[1]}, sum.first});
                    }
                }
            }
        }
    }
    return matches;
}

// Task 5
// Finds word pairs in a wordlist file which:
//  * share same letter sum value
//  * letter sum value is above uint sumThreshold
//  * both words share no letters
std::vector<twoWordsOneSum>wordlist::findSameSumNoCommonLetters(std::ifstream &file, const unsigned int &sumThreshold) {
    // Loop through file and save words only with value > sumThreshold - unordered_map<value, vector<words>>
    const auto sums = sortWordsBySum(file, sumThreshold);

    // Create a place where to store the found matches
    std::vector<twoWordsOneSum> matches;

    // Loop each saved word sets - pair<value, vector<words>>
    for (const auto& s: sums) {
        const unsigned int sVectorSize = s.second.size();
        // Loop (i,j) all word pair combinations in the vector of words
        for (unsigned int i = 0; i < sVectorSize - 1; ++i) {
            const std::string referenceWord = s.second[i];
            for (unsigned int j = i + 1; j < sVectorSize; ++j) {
                const std::string currentWord = s.second[j];

                // Find common element
                bool res;
                if (referenceWord.length() > currentWord.length()) {
                    res = checkIfCommonLetter({referenceWord, currentWord});
                } else {
                    res = checkIfCommonLetter({currentWord, referenceWord});
                }
                if (!res) {
                    matches.push_back({{referenceWord, currentWord}, s.first});
                }
            }
        }
    }
    return matches;
}

// Task 6
// Finds the longest possible vector of words in which:
//  * each word has a different length and sum
//  * vector sorted:
//      * descending word length
//      * ascending word sum
std::vector<std::string> wordlist::task6(std::ifstream &file) {
    // Sort all words in an unordered_map by their LENGTH -> SUM_VALUES
    // ==> unordered_map<int LENGTH, unordered_map<int SUM_VALUE, vector<WORDS>>>
    auto sortedMap = sortWordsByLenAndSum(file);
    std::vector<std::string> ret;

    // Loop through the sortedMap as many times as there are LENGTH elements
    for (auto retries = sortedMap.rbegin(); retries != sortedMap.rend(); ++retries) {
        // Actual checker
        // Loops through all lengths
        unsigned int lastSum{0};
        std::vector<std::string> tmpRet; // This vector temporarily stores found words

        // Loop through all remaining word LENGTHS. Each time it starts from a lesser LENGTH (last LENGTH - 1)
        for (auto length = retries; length != sortedMap.rend(); ++length) {
            // Loop through word VALUES
            for (const auto &sum: length->second) {

                // If current word VALUE if larger than the previous saved word VALUE, then append the first
                // word from current VALUE vector to the temporary word vector
                if (sum.first > lastSum) {
                    lastSum = sum.first;
                    tmpRet.push_back(sum.second[0]);
                    break;
                }
            }
        }
        // If the temporary vector has more words, then save it as the new best vector
        if (tmpRet.size() > ret.size()) {
            ret = tmpRet;
        }
    }

    return ret;
}

// ===
// Private functions
// ===
std::unordered_map<unsigned int, std::vector<std::string>> wordlist::sortWordsBySum(std::ifstream &file, const unsigned int &sumThreshold) {
    std::unordered_map<unsigned int, std::vector<std::string>> sums;
    std::string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            const unsigned int sum = letterCalc::calculateSum(line);
            if (sum > sumThreshold) {
                // Save each word in a vector inside a map that belongs to its sum
                sums[sum].push_back(line);
            }
        }
        fileReturnToBeginning(file);
    }
    return sums;
}

std::map<unsigned int, std::map<unsigned int, std::vector<std::string>>> wordlist::sortWordsByLenAndSum(std::ifstream &file) {
    std::map<unsigned int, std::map<unsigned int, std::vector<std::string>>> res;
    std::string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            res[line.length()][letterCalc::calculateSum(line)].push_back(line);
        }
        fileReturnToBeginning(file);
    }
    return res;
}

std::map<unsigned int, std::map<unsigned int, std::vector<std::string>>> wordlist::sortWordsBySumAndLen(std::ifstream &file) {
    std::map<unsigned int, std::map<unsigned int, std::vector<std::string>>> res;
    std::string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            res[letterCalc::calculateSum(line)][line.length()].push_back(line);
        }
        fileReturnToBeginning(file);
    }
    return res;
}


void wordlist::fileReturnToBeginning(std::ifstream &file) {
    file.clear();
    file.seekg(0);
}

unsigned int wordlist::calcDiff(const unsigned int &i1, const unsigned int &i2) {
    if (i1 > i2) {
        return i1 - i2;
    } else {
        return i2 - i1;
    }
}

bool wordlist::checkIfCommonLetter(const std::pair<std::string, std::string> &words) {
    for (const char letterWord1: words.first) {
        for (const char letterWord2: words.second) {
            if (letterWord1 == letterWord2) {
                return true;
            }
        }
    }
    return false;
}
