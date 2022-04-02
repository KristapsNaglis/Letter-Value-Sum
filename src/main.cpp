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
#include <map>
#include "userInteractions.h"
#include "wordlist.h"
#include "letterCalc.h"
#include "chronoTimer.h"


int main() {
    std::cout << "=======================================================================\n";
    std::cout << "=== Welcome to Lettersum - r/dailyprogrammer challenge #399 [EASY]! ===\n";
    std::cout << "=======================================================================\n";

    // Manual word input
    if (userInteractions::questionYesNo("\nManual word input check? [Enter/Y]es [N]o")) {
        do {
            std::cout << "------------------\n";
            std::cout << "╭─ Write a word: ";
            std::string word = userInteractions::getUserWord();
            int sum = letterCalc::calculateSum(word);
            std::cout << "╰─> Sum of word '" << word << "' is " << sum << "\n";
            std::cout << "------------------\n";
        } while (userInteractions::questionYesNo("Do you want to repeat manual word input? [Enter/Y]es [N]o"));
    }

    // Additional tasks
    if (userInteractions::questionYesNo("\nExecute additional tasks? [Enter/Y]es [N]o")) {
        std::ifstream wlFile = wordlist::openFile("../resources/wordlist.txt");

        std::cout << "! Choose number 1 - 6. For each option, please check documentation\n";
        do {
            std::cout << "------------------\n";
            unsigned int r = userInteractions::questionMultiRange("╭─ Choose task number", 1, 6);
            switch (r) {
                case 1: {
                    unsigned int value = 319;
                    chronoTimer chronoTimer;
                    chronoTimer.start();
                    std::string test = wordlist::findWordByValue(wlFile, value);
                    std::cout << "├─> Word '" + test + "' has a value of " << value << "\n";
                    std::cout << "│\n╰─> Execution time: " << chronoTimer.stop() << "ms\n";
                    break;
                }
                case 2: {
                    chronoTimer chronoTimer;
                    chronoTimer.start();
                    unsigned int result = wordlist::countResultsEvenOdd(wlFile, true);
                    std::cout << "├─> Found " << result << " odd words\n";
                    std::cout << "│\n╰─> Execution time: " << chronoTimer.stop() << "ms\n";
                    break;
                }
                case 3: {
                    chronoTimer chronoTimer;
                    chronoTimer.start();
                    auto mostCommonSum = wordlist::findMostCommonLetterSum(wlFile);
                    std::cout << "├─> Most common sum is '" << mostCommonSum.first << "' with count of "
                              << mostCommonSum.second << "\n";
                    std::cout << "│\n╰─> Execution time: " << chronoTimer.stop() << "ms\n";

                    break;
                }
                case 4: {
                    const unsigned int difference = 11;
                    chronoTimer chronoTimer;
                    chronoTimer.start();
                    // Store found pairs in a vector
                    const auto foundPairs = wordlist::findPairWithSameSum(wlFile, difference);
                    // Print a list of found pairs
                    for (auto& pair: foundPairs) {
                        std::cout << "├─> Words '" << pair.words.first << "', '" << pair.words.second << "' with sum "
                                  << pair.sum << " have length difference by " << difference << " letters\n";
                    }
                    std::cout << "│\n╰─> Execution time: " << chronoTimer.stop() << "ms\n";
                    break;
                }
                case 5: {
                    // Vector
                    chronoTimer chronoTimer;
                    chronoTimer.start();
                    // Store found pairs in a vector
                    const auto foundPairs = wordlist::findSameSumNoCommonLetters(wlFile, 188);
                    // Print a list of found pairs
                    for (auto& pair: foundPairs) {
                        std::cout << "├─> Words '" << pair.words.first << "', '" << pair.words.second << "' with sum "
                                  << pair.sum << " share no letters\n";
                    }
                    std::cout << "│\n╰─> Execution time: " << chronoTimer.stop() << "ms\n";
                    break;
                }
                case 6: {
                    chronoTimer chronoTimer;
                    chronoTimer.start();
                    // Store found pairs in a vector
                    auto foundList = wordlist::task6(wlFile);
                    // Print a list of found pairs
                    std::cout << "├─> Found a chain of " << foundList.size() << " words\n│\n";
                    for (auto& word: foundList) {
                        std::cout << "├─> " << word << "\n";
                    }
                    std::cout << "│\n╰─> Execution time: " << chronoTimer.stop() << "ms\n";
                    break;
                }
                default:
                    break;
            }
            std::cout << "------------------\n";
        } while (userInteractions::questionYesNo("Do you want to repeat additional tasks? [Enter/Y]es [N]o"));

        wlFile.close();
    }

    std::cout << "\nQuitting...\n";
    return 0;
}
