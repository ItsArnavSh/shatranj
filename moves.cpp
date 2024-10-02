#include "moves.h"
#include "util.h"
#include <iostream>
//Normal
uint64_t rajaMoves(uint64_t click,uint64_t* board){}
//Mantri can move one square diagonally
uint64_t mantriMoves(uint64_t click,uint64_t* board){}
//Normal Rook
uint64_t ashvaMoves(uint64_t click,uint64_t* board){}
//2 Squares diagonally
uint64_t gajaMoves(uint64_t click,uint64_t* board){}
//1 Square forward

//Apart from Ratha and Padati all others can be simply masked!

uint64_t rathaMoves(uint64_t click,uint64_t* board){}

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
