//
// Created by kristapsn on 13.03.22.
//
#include <iostream>
#include <fstream>
#include <string>
#include "letterCalc.h"

#ifndef LETTER_VALUE_SUM_WORDLIST_H
#define LETTER_VALUE_SUM_WORDLIST_H


class wordlist {
public:
    static std::ifstream openFile(const std::string& filename);

    static std::string find_word_by_value(std::ifstream& file, const unsigned int &value);
};


#endif //LETTER_VALUE_SUM_WORDLIST_H
