#include "moves.h"
#include "util.h"
#include <iostream>
//Normal
uint64_t rajaMoves(uint64_t click, uint64_t you) {
    // Raja (King) move pattern placeholder
    __uint128_t king_pattern = __uint128_t(0);  // Replace with the King's pattern

    // Shift the pattern based on the King's current position (click)
    uint8_t shift = bitBoardToInt(click);
    std::cout << "King position index: " << (int)shift << std::endl;

    if (shift >= 0 && shift < 64) {
        king_pattern >>= shift;
    } else {
        king_pattern = 0;  // Prevent overflow if the shift is invalid
    }

    // Bound the moves to the board and remove invalid ones
    uint64_t king_moves = boardBoundCheck(king_pattern);
    // king_moves &= ~you;  // Remove friendly pieces (no attacking your own pieces)

    // Apply mask to ensure valid King moves
    king_moves = mask(king_moves, click);

    // Debugging output
    std::cout << "King Moves: " << std::hex << king_moves << std::endl;

    return king_moves;
}

uint64_t mantriMoves(uint64_t click, uint64_t you) {
    // Mantri (Queen) move pattern placeholder
    __uint128_t queen_pattern = __uint128_t(0);  // Replace with the Queen's pattern

    // Shift the pattern based on the Queen's current position (click)
    uint8_t shift = bitBoardToInt(click);
    std::cout << "Queen position index: " << (int)shift << std::endl;

    if (shift >= 0 && shift < 64) {
        queen_pattern >>= shift;
    } else {
        queen_pattern = 0;  // Prevent overflow if the shift is invalid
    }

    // Bound the moves to the board and remove invalid ones
    uint64_t queen_moves = boardBoundCheck(queen_pattern);
    // queen_moves &= ~you;  // Remove friendly pieces (no attacking your own pieces)

    // Apply mask to ensure valid Queen moves
    queen_moves = mask(queen_moves, click);

    // Debugging output
    std::cout << "Queen Moves: " << std::hex << queen_moves << std::endl;

    return queen_moves;
}

uint64_t ashvaMoves(uint64_t click, uint64_t you) {
    // Knight move pattern (L-shape) as a 128-bit integer
    __uint128_t knight_pattern = __uint128_t(0b10100001000100000000000100010000101)<<(64+18+15);
    // Shift the pattern based on the knight's current position (click)
    uint8_t shift = bitBoardToInt(click);  // Convert click to square index (0-63)
    std::cout << "Knight position index: " << (int)shift << std::endl;

    if (shift >= 0 && shift < 64) {
        //62-43 = 19
        //57-33 = 24
        //The position of the block
        knight_pattern >>= shift;  // Shift pattern to align with the knight's current position
    } else {
        knight_pattern = 0;  // Prevent overflow if the shift is invalid
    }

    // Bound the moves to the board and remove invalid ones
    uint64_t knight_moves = boardBoundCheck(knight_pattern);  // Check for out-of-bound moves
    //knight_moves &= ~you;  // Remove friendly pieces (no attacking your own pieces)

    // Apply mask to ensure valid knight moves
    knight_moves = mask(knight_moves, click);

    // Debugging output
    std::cout << "Knight Moves: " << std::hex << knight_moves << std::endl;

    return knight_moves;
}


uint64_t gajaMoves(uint64_t click, uint64_t you) {
    // Gaja (Bishop) move pattern placeholder
    __uint128_t bishop_pattern = __uint128_t(0);  // Replace with the Bishop's pattern

    // Shift the pattern based on the Bishop's current position (click)
    uint8_t shift = bitBoardToInt(click);
    std::cout << "Bishop position index: " << (int)shift << std::endl;

    if (shift >= 0 && shift < 64) {
        bishop_pattern >>= shift;
    } else {
        bishop_pattern = 0;  // Prevent overflow if the shift is invalid
    }

    // Bound the moves to the board and remove invalid ones
    uint64_t bishop_moves = boardBoundCheck(bishop_pattern);
    // bishop_moves &= ~you;  // Remove friendly pieces (no attacking your own pieces)

    // Apply mask to ensure valid Bishop moves
    bishop_moves = mask(bishop_moves, click);

    // Debugging output
    std::cout << "Bishop Moves: " << std::hex << bishop_moves << std::endl;

    return bishop_moves;
}

//Apart from Ratha and Padati all others can be simply masked!

uint64_t rathaMoves(uint64_t click, uint64_t friendPieces, uint64_t enemyPieces) {
    uint64_t moves = findMoves(click, (int)1, (int)0, enemyPieces, friendPieces);  // Left
    moves |= findMoves(click, 0, 1, enemyPieces, friendPieces);          // Up
    moves |= findMoves(click, -1, 0, enemyPieces, friendPieces);         // Right
    moves |= findMoves(click, 0, -1, enemyPieces, friendPieces);         // Down
    std::cout << moves<<"Moves"<<std::endl;
    return moves;
}


uint64_t padatiMoves(uint64_t click, uint64_t you, uint64_t enemy, bool turn) {
    uint64_t moves = 0;

    // Shifts for one and two steps forward
    uint64_t one_step = turn ? (click << 8) : (click >> 8);
    uint64_t two_steps = turn ? (click << 16) : (click >> 16);

    // Start ranks for white and black pawns
    uint64_t start_rank = turn ? 0x000000000000FF00 : 0x00FF000000000000;

    // Single move forward (one step)
    if ((one_step & (you | enemy)) == 0) {
        moves |= one_step;

        // Double move forward (two steps) from starting rank
        if ((click & start_rank) != 0 && (two_steps & (you | enemy)) == 0) {
            moves |= two_steps;
        }
    }

    // Capture moves
    uint64_t left_capture, right_capture;

    if (turn) {
        left_capture = (click << 9) & 0xFEFEFEFEFEFEFEFE; // Shift left-up for white
        right_capture = (click << 7) & 0x7F7F7F7F7F7F7F7F; // Shift right-up for white
    } else {
        left_capture = (click >> 7) & 0x7F7F7F7F7F7F7F7F; // Shift right-down for black
        right_capture = (click >> 9) & 0xFEFEFEFEFEFEFEFE; // Shift left-down for black
    }

    // Apply captures only if enemy pieces are present
    moves |= (left_capture & enemy);
    moves |= (right_capture & enemy);

    // Ensure moves do not include your own pieces
    moves &= ~you;
    std::cout << moves<<std::endl;
    return moves;
}
