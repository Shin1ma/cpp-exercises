//
// Created by nebur on 23/11/2024.
//

#ifndef WUMPUSGAME_UTILS_H
#define WUMPUSGAME_UTILS_H

#include <iostream>
#include <random>
#include <chrono>
#include <windows.h>

int getRandomInt(int min, int max);

void error(const std::string &);

void print_centered_with_offset(const std::string &msg, int xoffset, int yoffset);

void clear_terminal();

#endif //WUMPUSGAME_UTILS_H
