//
// Created by kristapsn on 02.04.22.
//

#include "chronoTimer.h"


void chronoTimer::start() {
    startTime = std::chrono::high_resolution_clock::now();
}


unsigned int chronoTimer::stop() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - startTime).count();
}
