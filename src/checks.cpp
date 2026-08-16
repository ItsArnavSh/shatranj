#include "moves.h"
#include "eventhandler.h"
#include "engineHelper.h"
#include <cstdint>
#include <vector>
uint64_t removeIllegal(uint64_t* board,uint64_t moves,uint64_t click,bool turn){
    //First lets get all the moves
    std::vector<uint64_t> allMoves = bitBreaker(moves);
    //Now we will make a copy, to play all these moves, then we check if the king is safe in all, if not, we remove it
    uint64_t* newB = copyArray(board, 17);
    for(auto move : allMoves)
    {

        if(playMove(click, board)){}
    }
}

bool checkForCheck(uint64_t* board,bool turn){
    //This will check if the king is safe or not
    if(turn)
    {
        //Blacks Turn
        if(rajaMoves(board[3], board[0])&board[9]||
            mantriMoves(board[3], board[0])&board[10]||
            rathaMoves(board[3], board[0],board[1])&board[11]||
            ashvaMoves(board[3], board[0])&board[12]||
            gajaMoves(board[3], board[0])&board[13]||
            padatiMoves(board[3], board[0],board[1],turn)&board[14])
        {
            return false;
        }
        return true;
    }
    else
    {
        //Blacks Turn
        if(rajaMoves(board[9], board[1])&board[3]||
            mantriMoves(board[9], board[1])&board[4]||
            rathaMoves(board[9], board[1],board[0])&board[5]||
            ashvaMoves(board[9], board[1])&board[6]||
            gajaMoves(board[9], board[1])&board[7]||
            padatiMoves(board[9], board[1],board[0],turn)&board[8])
        {
            return false;
        }
        return true;
    }
    return true;

}
