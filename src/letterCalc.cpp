//
// Created by kristapsn on 17.03.22.
//

#include "letterCalc.h"

// Calculate letter sum using individual char ASCII values
int letterCalc::calculateSum(const std::string &word) {
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
    const std::vector<int> bounds{96, 123};

    // Loop each char in the word string and check if it is located in the needed ASCII bounds
    // If ok, then add to the sum
    int value{0};
    for (char c: word) {
        int c_val = (unsigned char) c;
        if (c_val > bounds[0] && c_val < bounds[1]) {
            value += c_val - bounds[0];
        }
    }
    return value;
}
