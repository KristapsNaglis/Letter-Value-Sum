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
    static std::ifstream openFile(const std::string &filename);

    static std::string findWordByValue(std::ifstream &file, const unsigned int &value);

    static std::pair<unsigned int, unsigned int> findMostCommonLetterSum(std::ifstream &file);

    static std::vector<twoWordsOneSum> findPairWithEqualSum(std::ifstream &file, unsigned int diff);

    static unsigned int countResultsEvenOdd(std::ifstream &file, bool odd);

private:
    static void fileReturnToBeginning(std::ifstream &file);
};


#endif //LETTER_VALUE_SUM_WORDLIST_H
