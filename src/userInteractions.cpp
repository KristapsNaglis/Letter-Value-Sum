//
// Created by kristapsn on 02.04.22.
//

#include "userInteractions.h"

// Get user input with getline
std::string userInteractions::getUserWord() {
    std::string return_word;
    getline(std::cin, return_word);
    return return_word;
}


// Ask user question with yes/no answer possibilities, return true/false accordingly
bool userInteractions::questionYesNo(const std::string &question) {
    // Acceptable answers:
    //  * [0] - true
    //  * [1] - false
    std::vector<std::vector<std::string>> answers{{"y", "Y", "yes", "YES", ""},
                                                  {"n", "N", "no",  "NO"}};
    std::string reply;

    unsigned int repeatCounter = 0;
    while (repeatCounter < 3) {
        std::cout << question << ": ";
        getline(std::cin, reply);
        int counter = 0;
        for (const std::vector<std::string> &vec: answers) {
            counter++;
            for (const std::string &answer: vec) {
                if (answer == reply) {
                    if (counter == 1) {
                        return true;
                    } else {
                        return false;
                    }
                }
            }
        }
        repeatCounter++;
    }
    return false;
}

unsigned int userInteractions::questionMultiRange(const std::string &question, const unsigned int &from,
                                                  const unsigned int &to) {
    unsigned int reply;

    unsigned int repeatCounter = 0;
    while (repeatCounter < 3) {
        std::cout << question << ": ";
        std::cin >> reply;

        std::cin.clear();
        std::cin.ignore(256, '\n'); // clear all remaining input chars until newline

        if (reply >= from && reply <= to) {
            return reply;
        }

        std::cout << "Input not correct, please, try again\n";
        repeatCounter++;
    }
    return 0;
}
