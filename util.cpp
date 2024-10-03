#include "util.h"

uint64_t intToBitboard(uint8_t num) {
    if (num < 0 || num > 63) {
        return 0;  // Invalid position, return 0
    }
    return 1ULL << num;  // Shift a 1 to the left by `num` positions
}

uint8_t bitBoardToInt(uint64_t bitboard) {
    if (bitboard == 0) {
        return -1;  // No valid bit set
    }

    // Find the position of the first (and only) bit set to 1
    int pos = 0;
    while ((bitboard & 1) == 0) {
        bitboard >>= 1;
        pos++;
    }
    return pos;
}

std::vector<uint8_t> bitboardToVector(uint64_t bitboard) {
    std::vector<uint8_t> positions;

    for (int i = 0; i < 64; ++i) {
        if (bitboard & (1ULL << i)) {  // Check if the i-th bit is set
            positions.push_back(i);     // Add the position to the vector
        }
    }

    return positions;
}

uint8_t oneNumber(uint64_t bitboard){
    //Returns the number of bits
    uint8_t count;
    while(bitboard){
        if(bitboard&0b1)
            count++;
        bitboard >>= 1;
    }
    return count;
}
