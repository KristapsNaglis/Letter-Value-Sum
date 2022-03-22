// === Challenge ===
// Assign every lowercase letter a value, from 1 for a to 26 for z. Given a string of lowercase letters, find the sum of
// the values of the letters in the string.
//
// lettersum("") => 0
// lettersum("a") => 1
// lettersum("z") => 26
// lettersum("cab") => 6
// lettersum("excellent") => 100
// lettersum("microspectrophotometries") => 317
//
// === Additional Challenges ===
// ! Use the word list for the optional bonus challenges.
// TODO 1) microspectrophotometries is the only word with a letter sum of 317. Find the only word with a letter sum of 319.
// ---
// TODO 2) How many words have an odd letter sum?
// ---
// TODO 3) There are 1921 words with a letter sum of 100, making it the second most common letter sum. What letter sum is
// most common, and how many words have it?
// ---
// TODO 4) zyzzyva and biodegradabilities have the same letter sum as each other (151), and their lengths differ by 11
// letters. Find the other pair of words with the same letter sum whose lengths differ by 11 letters.
// ---
// TODO 5) cytotoxicity and unreservedness have the same letter sum as each other (188), and they have no letters in common.
// Find a pair of words that have no letters in common, and that have the same letter sum, which is larger than 188.
// (There are two such pairs, and one word appears in both pairs.)
// ---
// TODO 6) The list of word { geographically, eavesdropper, woodworker, oxymorons } contains 4 words. Each word in the list
// has both a different number of letters, and a different letter sum. The list is sorted both in descending order of
// word length, and ascending order of letter sum. What's the longest such list you can find?


#include <iostream>
#include <vector>
#include "wordlist.h"
#include "letterCalc.h"

// Get user input with getline
std::string getUserWord() {
    std::string return_word;
    getline(std::cin, return_word);
    return return_word;
}

// Ask user question with yes/no answer possibilities, return true/false accordingly
bool question_y_n(const std::string &question) {
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

unsigned int question_multi_range(const std::string &question, unsigned int from, unsigned int to) {
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

int main() {
    std::cout << "=======================================================================\n";
    std::cout << "=== Welcome to Lettersum - r/dailyprogrammer challenge #399 [EASY]! ===\n";
    std::cout << "=======================================================================\n";

    // Manual word input
    if (question_y_n("\nManual word input check? [Enter/Y]es [N]o")) {
        do {
            std::cout << "------------------\n";
            std::cout << "╭─ Write a word: ";
            std::string word = getUserWord();
            int sum = letterCalc::calculateSum(word);
            std::cout << "╰─> Sum of word '" << word << "' is " << sum << "\n";
            std::cout << "------------------\n";
        } while (question_y_n("Do you want to repeat manual word input? [Enter/Y]es [N]o"));
    }

    // Additional tasks
    if (question_y_n("\nExecute additional tasks? [Enter/Y]es [N]o")) {
        std::ifstream wlFile = wordlist::openFile("../resources/wordlist.txt");

        std::cout << "! Choose number 1 - 6. For each option, please check documentation\n";
        do {
            std::cout << "------------------\n";
            unsigned int r = question_multi_range("╭─ Choose task number", 1, 6);
            switch (r) {
                case 1: {
                    unsigned int value = 319;
                    std::string test = wordlist::findWordByValue(wlFile, value);
                    std::cout << "╰─> Word '" + test + "' has a value of " << value << "\n";
                    break;
                }
                case 2: {
                    unsigned int result = wordlist::countResultsEvenOdd(wlFile, true);
                    std::cout << "╰─> Found " << result << " odd words\n";
                }
                // Other cases will be added
                default:
                    break;
            }
            std::cout << "------------------\n";
        } while (question_y_n("Do you want to repeat additional tasks? [Enter/Y]es [N]o"));

        wlFile.close();
    }

    std::cout << "\nQuitting...\n";
    return 0;
}
