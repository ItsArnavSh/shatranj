#ifndef UTIL_H
#define UTIL_H

#include <cstdint>
#include <vector>

using namespace std;

vector<uint8_t> bitboardToVector(uint64_t bitboard);

uint64_t intToBitboard(uint8_t num);

uint8_t bitBoardToInt(uint64_t bitboard);  // Ensure proper casing

uint8_t oneNumber(uint64_t bitboard);

#endif // UTIL_H
