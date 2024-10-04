#include "moves.h"
#include "util.h"
#include <iostream>
//Normal
uint64_t rajaMoves(uint64_t click, uint64_t you) {
    // Raja (King) move pattern placeholder
    __uint128_t king_pattern = __uint128_t(0b1110000010100000111)<<(64-19/2);  // Replace with the King's pattern

    // Shift the pattern based on the King's current position (click)
    uint8_t shift = bitBoardToInt(click);

    if (shift >= 0 && shift < 64) {
        king_pattern >>= 64-shift;
    } else {
        king_pattern = 0;  // Prevent overflow if the shift is invalid
    }

    // Bound the moves to the board and remove invalid ones
    uint64_t king_moves = boardBoundCheck(king_pattern);
    king_moves &= ~you;  // Remove friendly pieces (no attacking your own pieces)

    // Apply mask to ensure valid King moves
    king_moves = mask(king_moves, click);

    // Debugging output

    return king_moves;
}

uint64_t mantriMoves(uint64_t click, uint64_t you) {
    // Mantri (Queen) move pattern placeholder
    __uint128_t queen_pattern =  __uint128_t(0b1010000000000000101)<<(64-19/2); // Replace with the Queen's pattern

    // Shift the pattern based on the Queen's current position (click)
    uint8_t shift = bitBoardToInt(click);

    if (shift >= 0 && shift < 64) {
        queen_pattern >>= 64-shift;
    } else {
        queen_pattern = 0;  // Prevent overflow if the shift is invalid
    }

    // Bound the moves to the board and remove invalid ones
    uint64_t queen_moves = boardBoundCheck(queen_pattern);
    queen_moves &= ~you;  // Remove friendly pieces (no attacking your own pieces)

    // Apply mask to ensure valid Queen moves
    queen_moves = mask(queen_moves, click);

    // Debugging output

    return queen_moves;
}

uint64_t ashvaMoves(uint64_t click, uint64_t you) {
    // Knight move pattern (L-shape) as a 128-bit integer
    __uint128_t knight_pattern = __uint128_t(0b10100001000100000000000100010000101)<<(64-35/2);
    // Shift the pattern based on the knight's current position (click)
    uint8_t shift = bitBoardToInt(click);  // Convert click to square index (0-63)
    if (shift >= 0 && shift < 64) {
        //62-43 = 19
        //57-33 = 24
        //The position of the block
        knight_pattern >>= 64-shift;  // Shift pattern to align with the knight's current position
    } else {
        knight_pattern = 0;  // Prevent overflow if the shift is invalid
    }

    // Bound the moves to the board and remove invalid ones
    uint64_t knight_moves = boardBoundCheck(knight_pattern);  // Check for out-of-bound moves
    knight_moves &= ~you;  // Remove friendly pieces (no attacking your own pieces)

    // Apply mask to ensure valid knight moves
    knight_moves = mask(knight_moves, click);
    return knight_moves;
}


uint64_t gajaMoves(uint64_t click, uint64_t you) {
    // Gaja (Bishop) move pattern placeholder
    __uint128_t bishop_pattern = __uint128_t(0b1000100000000000000000000000000010001)<<(64-37/2);  // Replace with the Bishop's pattern

    // Shift the pattern based on the Bishop's current position (click)
    uint8_t shift = bitBoardToInt(click);

    if (shift >= 0 && shift < 64) {
        bishop_pattern >>= 64-shift;
    } else {
        bishop_pattern = 0;  // Prevent overflow if the shift is invalid
    }

    // Bound the moves to the board and remove invalid ones
    uint64_t bishop_moves = boardBoundCheck(bishop_pattern);
    bishop_moves &= ~you;  // Remove friendly pieces (no attacking your own pieces)

    // Apply mask to ensure valid Bishop moves
    bishop_moves = mask(bishop_moves, click);

    return bishop_moves;
}
//Apart from Ratha and Padati all others can be simply masked!
uint64_t rathaMoves(uint64_t click, uint64_t friendPieces, uint64_t enemyPieces) {
    uint64_t moves = findMoves(click, (int)1, (int)0, enemyPieces, friendPieces);  // Left
    moves |= findMoves(click, 0, 1, enemyPieces, friendPieces);          // Up
    moves |= findMoves(click, -1, 0, enemyPieces, friendPieces);         // Right
    moves |= findMoves(click, 0, -1, enemyPieces, friendPieces);         // Down
    return moves;
}
uint64_t padatiMoves(uint64_t click, uint64_t you, uint64_t enemy, bool turn) {
    uint64_t pawn_moves = 0;

    if (!turn) { // Black pawns
        // Black pawns move one square down (shift right by 8 bits)
        uint64_t single_move = (click >> 8) & ~you & ~enemy; // Can't move to squares with your own or enemy pieces

        // Black pawns attack diagonally to the left (shift right by 9 bits)
        uint64_t attack_left = (click >> 9) & enemy & 0x7F7F7F7F7F7F7F7FULL; // Avoid overflow from the left edge

        // Black pawns attack diagonally to the right (shift right by 7 bits)
        uint64_t attack_right = (click >> 7) & enemy & 0xFEFEFEFEFEFEFEFEULL; // Avoid overflow from the right edge

        // Combine all possible moves
        pawn_moves = single_move | attack_left | attack_right;
    }
    else { // White pawns
        // White pawns move one square up (shift left by 8 bits)
        uint64_t single_move = (click << 8) & ~you & ~enemy; // Can't move to squares with your own or enemy pieces

        // White pawns attack diagonally to the left (shift left by 7 bits)
        uint64_t attack_left = (click << 7) & enemy & 0x7F7F7F7F7F7F7F7FULL; // Avoid overflow from the left edge

        // White pawns attack diagonally to the right (shift left by 9 bits)
        uint64_t attack_right = (click << 9) & enemy & 0xFEFEFEFEFEFEFEFEULL; // Avoid overflow from the right edge

        // Combine all possible moves
        pawn_moves = single_move | attack_left | attack_right;
    }

    return pawn_moves;
}
