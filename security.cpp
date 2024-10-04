#include "security.h"
//This section exists as a way to ensure data persistance
uint64_t* verifyBoard(uint64_t* board){
    board[0] = board[3]|board[4]|board[5]|board[6]|board[7]|board[8];
    board[1] = board[9]|board[10]|board[11]|board[12]|board[13]|board[14];
    return board;
}
