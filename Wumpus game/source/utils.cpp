//
// Created by nebur on 23/11/2024.
//

#include "utils.h"


int getRandomInt(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

void error(const std::string &msg) {
    throw std::runtime_error(msg);
}

