#include "board.h"
#include <cstdint>

// Bitboards for the pieces based on the description:
// 0: Black pieces, 1: White pieces, 2: All available moves (could be updated dynamically)
// 3,9: Black and White Kings
// 4,10: Black and White Queens
// 5,11: Black and White Rooks
// 6,12: Black and White Knights
// 7,13: Black and White Bishops
// 8,14: Black and White Pawns

uint64_t* getBoard() {
    uint64_t* board = new uint64_t[16];

    // Initialize all bitboards to 0
    for (int i = 0; i < 16; ++i) {
        board[i] = 0;
    }

    // Black pieces
    board[0] = 0xFFFF000000000000;  // Black pieces occupy ranks 7 and 8 (rows 6 and 7 in 0-indexing)

    // White pieces
    board[1] = 0x000000000000FFFF;  // White pieces occupy ranks 1 and 2 (rows 0 and 1 in 0-indexing)

    // Kings
    board[3] = 0x1000000000000000;  // Black king starts at e8
    board[9] = 0x0000000000000010;  // White king starts at e1

    // Queens
    board[4] = 0x0800000000000000;  // Black queen starts at d8
    board[10] = 0x0000000000000008;  // White queen starts at d1

    // Rooks
    board[5] = 0x8100000000000000;  // Black rooks start at a8, h8
    board[11] = 0x0000000000000081;  // White rooks start at a1, h1

    // Knights
    board[6] = 0x4200000000000000;  // Black knights start at b8, g8
    board[12] = 0x0000000000000042;  // White knights start at b1, g1

    // Bishops
    board[7] = 0x2400000000000000;  // Black bishops start at c8, f8
    board[13] = 0x0000000000000024;  // White bishops start at c1, f1

    // Pawns
    board[8] = 0x00FF000000000000;  // Black pawns start on rank 7
    board[14] = 0x000000000000FF00;  // White pawns start on rank 2

    //turn
    board[15] = 1;
    // Moves bitboard (dynamic, initially 0)
    board[2] = 0x0;  // This will be populated dynamically when calculating available moves

    return board;
}
