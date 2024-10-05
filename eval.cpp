#include "eval.h"
#include "engineHelper.h"
#include "util.h"
#include <limits>
float evaluate(uint64_t* board){
    if(gameOver(board))
    {
        return gameOver(board)*std::numeric_limits<float>::infinity();
    }
    float A= pieceAdvantage(board);
    float B = piecePositioning(board);
    return (A+B);
}

float pieceAdvantage(uint64_t* board){
    float tally=0;
    tally-=50*(oneNumber(board[3])-oneNumber(board[9]));//king
    tally-= 2*(oneNumber(board[4])-oneNumber(board[10]));//mantri
    tally-= 5*(oneNumber(board[6])-oneNumber(board[12]));//ashva
    tally-= 3*(oneNumber(board[7])-oneNumber(board[13]));//gaja
    tally-= 10*(oneNumber(board[5])-oneNumber(board[11]));//ratha
    tally-= (oneNumber(board[8])-oneNumber(board[14]));//padati
    return tally;
}
float piecePositioning(uint64_t *board) {
    // Define the chessboard areas
    uint64_t center = 0b0000000000000000000000000001100000011000000000000000000000000000;
    uint64_t middle = 0b0000000000000000001111000010010000100100001111000000000000000000;
    uint64_t safe = 0b1111111100000000000000000000000000000000000000000000000011111111;

    float positionScore = 0;

    // Reward for pieces in the center and middle, punish for being in the safe zone
    // King: board[3] (Black King), board[9] (White King)
    //positionScore -= 5 * (oneNumber(board[3] & safe) - oneNumber(board[9] & safe));  // Reward kings for staying in the safe zone
    //positionScore -= 5* (oneNumber(board[3] & ~safe) - oneNumber(board[9] & ~safe)); // Punish kings outside the safe zone

    // Other pieces:
    // Reward for controlling the center and middle
    positionScore -= 10 * (oneNumber(board[4] & center) - oneNumber(board[10] & center)); // Mantri in center
    positionScore-= 5 * (oneNumber(board[4] & middle) - oneNumber(board[10] & middle)); // Mantri in middle
    //positionScore -= 2 * (oneNumber(board[4] & safe) - oneNumber(board[10] & safe));     // Punish mantri in safe zone

    positionScore = 10 * (oneNumber(board[6] & center) - oneNumber(board[12] & center)); // Ashva in center
    positionScore -= 5 * (oneNumber(board[6] & middle) - oneNumber(board[12] & middle)); // Ashva in middle
    //positionScore -= 2 * (oneNumber(board[6] & safe) - oneNumber(board[12] & safe));     // Punish ashva in safe zone

    positionScore -= 10 * (oneNumber(board[7] & center) - oneNumber(board[13] & center)); // Gaja in center
    positionScore -= 5 * (oneNumber(board[7] & middle) - oneNumber(board[13] & middle)); // Gaja in middle
    //positionScore -= 2 * (oneNumber(board[7] & safe) - oneNumber(board[13] & safe));     // Punish gaja in safe zone

    positionScore -= 10 * (oneNumber(board[5] & center) - oneNumber(board[11] & center)); // Ratha in center
    positionScore -= 5 * (oneNumber(board[5] & middle) - oneNumber(board[11] & middle)); // Ratha in middle
    //positionScore -= 2 * (oneNumber(board[5] & safe) - oneNumber(board[11] & safe));     // Punish ratha in safe zone

    positionScore -= 20 * (oneNumber(board[8] & center) - oneNumber(board[14] & center)); // Padati in center
    positionScore -= 5 * (oneNumber(board[8] & middle) - oneNumber(board[14] & middle)); // Padati in middle
    //positionScore -= 4 * (oneNumber(board[8] & safe) - oneNumber(board[14] & safe));     // Punish padati in safe zone

    return positionScore;
}
