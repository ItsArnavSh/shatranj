
#include "engine.h"

uint64_t* dunningKruger(uint64_t* board)
{
    //This is a test function,
    //All it will do is return a random move
    //Just for seeing if the frontend works
    uint64_t* ans = new uint64_t();
    ans = allMoves(board,true)[0];
    return ans;
    //Pick any piece at random, and any move at random to make things interesting
}
