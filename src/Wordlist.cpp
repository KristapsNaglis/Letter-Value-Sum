//
// Created by kristapsn on 13.03.22.
//

#include "Wordlist.h"

std::string Wordlist::openFile(std::string filename) {
    std::ifstream file{filename};
    std::string output;
    if (!file) {
        output = "error opening file " + filename;
    } else {
        output = "ok opening file " + filename;
    }
    return output;
}
