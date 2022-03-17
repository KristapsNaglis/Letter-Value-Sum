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

// Get user input with getline
std::string getUserWord() {
    std::cout << "----------------\nWrite something: ";
    std::string return_word;
    getline(std::cin, return_word);
    return return_word;
}

// Calculate letter sum using individual char ASCII values
int letterSum(const std::string& word) {
    // Create a place to hold a-z ASCII lower and upper limits
    // Lower limit also acts as subtract value to get actual letter ASCII value down to the desired values,
    // for example:
    // +--------+---------------+---------------+-----------+
    // | letter | ascii value   | subtraction   | got value |
    // +--------+---------------+---------------+-----------+
    // |      a | 97            | 97-96         | 1         |
    // |      b | 98            | 98-96         | 2         |
    // |      c | 99            | 98-96         | 3         |
    // ......................................................
    // |      z | 122           | 122-96        | 26        |
    // +--------+---------------+---------------+-----------+
    const std::vector<int> bounds {96, 123};

    // Loop each char in the word string and check if it is located in the needed ASCII bounds
    // If ok, then add to the sum
    int value{0};
    for (char c : word) {
        int c_val = (unsigned char) c;
        if (c_val > bounds[0] && c_val < bounds[1]) {
            value += c_val - bounds[0];
        }
    }
    return value;
}

// Ask user about continuing or quitting the program and handle the reply accordingly
bool question_y_n(const std::string& question) {
    std::vector<std::vector<std::string>> answers{{"y", "Y", "yes", "YES", ""}, {"n", "N", "no", "NO"}};
    std::string reply;

    int repeat_counter = 0;
    while (repeat_counter < 3) {
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
        repeat_counter++;
    }
    return false;
}

int main() {
    std::cout << "Welcome to Lettersum - r/dailyprogrammer challenge #399 [EASY]!\n";

    wordlist wl;
    std::string t = wl.openFile("wordlist.txt");
    std::cout << t;

    bool action = true;
    while (action) {
        std::string word = getUserWord();
        int sum = letterSum(word);
        std::cout << "=> Sum of word '" << word << "' is " << sum << "\n";

        action = question_y_n("Do you want to repeat? [ENTER/Y]es [N]o");
    }
    std::cout << "Quitting...\n";
    return 0;
}
