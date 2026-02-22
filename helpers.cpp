#include <random>
#include "helpers.h"

//Chat GPT: Write a C++ function to generate a number between 0 and 255 inclusive
int generateRandom(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}