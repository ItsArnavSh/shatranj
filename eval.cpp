#include "eval.h"
int8_t evaluate(uint64_t* board){
    int8_t A= pieceAdvantage(board);
    return A;
}

int8_t pieceAdvantage(uint64_t* board){
    //Here are the piece value distributions to be used in the eval
    //ratha = 5
    //mantri = 2
    //ashva and gaja = 3
    //padati = 1
    uint8_t tally=0;
    tally+= 2*(oneNumber(board[4])-oneNumber(board[10]));
    tally+= 3*(oneNumber(board[6])-oneNumber(board[12]));
    tally+= 3*(oneNumber(board[13])-oneNumber(board[13]));
    tally+= 5*(oneNumber(board[5])-oneNumber(board[11]));
    return tally;
}
