#ifndef UTIL_H
#define UTIL_H

#include <cstdint>
#include <vector>
uint64_t intToBitboard(int num);
int bitBoardToInt(uint64_t bitboard);  // Ensure proper casing
std::vector<int> bitboardToVector(uint64_t bitboard);
#endif // UTIL_H
