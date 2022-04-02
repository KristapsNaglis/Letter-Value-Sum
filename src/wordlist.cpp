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

// Finds word pairs in a wordlist file which:
//  * share same value
//  * both words have a length difference of "diff"
std::vector<twoWordsOneSum> wordlist::findPairWithSameSum(std::ifstream &file, const unsigned int &diff) {
    // Loop through file and save words only with value > sumThreshold - unordered_map<value, vector<words>>
    const auto sums = sortWordsBySum(file, 0);
    // Create a place where to store the found matches
    std::vector<twoWordsOneSum> matches;

    // Loop each saved word sets - pair<value, vector<words>>
    for (const auto& s: sums) {
        const unsigned int sVectorSize = s.second.size();

        // Loop (i,j) all word pair combinations in the vector of words
        for (unsigned int i = 0; i < sVectorSize - 1; ++i) {
            const unsigned int referenceWordLen = s.second[i].length();
            for (unsigned int j = i + 1; j < sVectorSize; ++j) {

                if (calcDiff1(referenceWordLen, s.second[j].length()) == diff) {
                    matches.push_back({{s.second[i], s.second[j]}, s.first});
                }
            }
        }
    }
    return matches;
}

// Finds word pairs in a wordlist file which:
//  * share same letter sum value
//  * letter sum value is above uint sumThreshold
//  * both words share no letters
std::vector<twoWordsOneSum>wordlist::findSameSumNoCommonLetters(std::ifstream &file, const unsigned int &sumThreshold) {
    // Loop through file and save words only with value > sumThreshold - unordered_map<value, vector<words>>
    auto sums = sortWordsBySum(file, sumThreshold);

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

std::vector<std::string> wordlist::task6(std::ifstream &file) {
    // Sort all words in an unordered_map by their LENGTH -> SUM_VALUES
    // ==> unordered_map<int LENGTH, unordered_map<int SUM_VALUE, vector<WORDS>>>
    auto m = sortWordsByLenAndSum(file);
    std::vector<std::string> ret;

    unsigned int largestCombo{0};

    // Retries
    for (auto retries = m.rbegin(); retries != m.rend(); ++retries) {
        // Actual checker
        // Loops through all lengths
        unsigned int currentLastSum{0};
        std::vector<std::string> tmpRet;

        if (m.size() > ret.size()) {
            for (auto length = retries; length != m.rend(); ++length) {
                for (auto sum = length->second.begin(); sum != length->second.end(); ++sum) {
                    if (sum->first > currentLastSum) {
                        currentLastSum = sum->first;
//                        std::cout << sum->second[0] << " => LEN: " << length->first << " SUM: " << sum->first << "\n";
                        tmpRet.push_back(sum->second[0]);
                        break;
                    }
                }
            }
            if (tmpRet.size() > ret.size()) {
                ret = tmpRet;
            }
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
            // Save each word in a vector inside a map that belongs to its sum
            const unsigned int sum = letterCalc::calculateSum(line);
//            sums[sum].push_back(line);

            if (sum > sumThreshold) {
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

void wordlist::fileReturnToBeginning(std::ifstream &file) {
    file.clear();
    file.seekg(0);
}

unsigned int wordlist::calcDiff(const std::pair<unsigned int, unsigned int> &integers) {
    if (integers.first > integers.second) {
        return integers.first - integers.second;
    } else {
        return integers.second - integers.first;
    }
}

unsigned int wordlist::calcDiff1(const unsigned int &i1, const unsigned int &i2) {
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
