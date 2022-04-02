//
// Created by kristapsn on 13.03.22.
//
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <unordered_map>
#include "letterCalc.h"
#include "structures/helperStructures.h"

#ifndef LETTER_VALUE_SUM_WORDLIST_H
#define LETTER_VALUE_SUM_WORDLIST_H


class wordlist {
public:
    // File operations
    static std::ifstream openFile(const std::string &filename);

    // Additional challenge functions
    static std::string findWordByValue(std::ifstream &file, const unsigned int &value);

    static unsigned int countResultsEvenOdd(std::ifstream &file, const bool &odd);

    static std::pair<unsigned int, unsigned int> findMostCommonLetterSum(std::ifstream &file);

    static std::vector<twoWordsOneSum> findPairWithSameSum(std::ifstream &file, const unsigned int &diff);

    static std::vector<twoWordsOneSum>
    findSameSumNoCommonLetters(std::ifstream &file, const unsigned int &sumThreshold);

    static std::vector<std::string> task6(std::ifstream &file);

private:
    static void fileReturnToBeginning(std::ifstream &file);

    static std::unordered_map<unsigned int, std::vector<std::string>>
    sortWordsBySum(std::ifstream &file, const unsigned int &sumThreshold);

    static std::map<unsigned int, std::map<unsigned int, std::vector<std::string>>> sortWordsByLenAndSum(std::ifstream &file);

    static unsigned int calcDiff(const unsigned int &i1, const unsigned int &i2);

    static bool checkIfCommonLetter(const std::pair<std::string, std::string> &words);
};


#endif //LETTER_VALUE_SUM_WORDLIST_H
