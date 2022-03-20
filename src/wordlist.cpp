//
// Created by kristapsn on 13.03.22.
//

#include "wordlist.h"

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


std::string wordlist::find_word_by_value(std::ifstream &file, const unsigned int &value) {
    std::string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            unsigned int sum = letterCalc::calculateSum(line);
            if (sum == value) {
                return line;
            }
        }
    } else {
        std::cout << "file is not open anymore\n";
    }
    // Return to the beginning of the file
    file.clear();
    file.seekg(0);
    return "";
}