//
// Created by kristapsn on 02.04.22.
//

#include <chrono>

#ifndef LETTER_VALUE_SUM_TIMER_H
#define LETTER_VALUE_SUM_TIMER_H


class chronoTimer {
public:
    void start();

    unsigned int stop();

private:
    std::chrono::high_resolution_clock::time_point startTime;
};


#endif //LETTER_VALUE_SUM_TIMER_H
