#include "eventhandler.h"
#include "util.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <cstdint>
#include <sys/types.h>
#include <iostream>
bool validCLick(coord coordinates,uint64_t* board){
    uint8_t location = coordinates.x+coordinates.y*8;
    //We will tell if the click is valid or not
    if(intToBitboard(location)&board[0]){
        return true;
    }
    return false;
}
uint64_t handleClick(coord coordinate, uint64_t* board){

    uint8_t location = coordinate.x+coordinate.y*8;
    //Now we need to see which case was clicked and send it to the appropriate function
    uint64_t click = intToBitboard(location);
    std::cout << "Click was "<<click<<std::endl;
    if(click&board[8]){
        return padatiMoves(click, board[0], board[1], 0);}
    else if(click&board[6]){
        return ashvaMoves(click, board[0]);
    }
    return 0;
}
uint64_t* playMove(uint64_t click,uint64_t* board){
    std::cout << "Plays";
    //First we need to find the older piece
    board[0] = board[0]&(~board[16]) | click;
    for(int i=3;i<9;i++)
    {
        if(board[16]&board[i])
        {
            board[i] = (board[i])&(~board[16]) | click;
        }
    }
    board[16] = 0;
    return board;
}
