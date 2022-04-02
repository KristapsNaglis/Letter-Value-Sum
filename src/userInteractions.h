//
// Created by kristapsn on 02.04.22.
//

#include <iostream>
#include <string>
#include <vector>

#ifndef LETTER_VALUE_SUM_USERINTERACTIONS_H
#define LETTER_VALUE_SUM_USERINTERACTIONS_H


class userInteractions {
public:
    static std::string getUserWord();

    static bool questionYesNo(const std::string &question);

    static unsigned int questionMultiRange(const std::string &question, const unsigned int &from, const unsigned int &to);

};


#endif //LETTER_VALUE_SUM_USERINTERACTIONS_H
