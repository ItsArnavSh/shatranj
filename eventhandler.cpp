#include "eventhandler.h"
#include "util.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <cstdint>
#include <sys/types.h>
#include <iostream>
bool validCLick(coord coordinates,uint64_t* board,bool turn){
;    uint8_t location = coordinates.x+coordinates.y*8;
    //We will tell if the click is valid or not
    if(intToBitboard(location)&board[turn]){
        return true;
    }
    return false;
}
uint64_t handleClick(coord coordinate, uint64_t* board){

    uint8_t location = coordinate.x+coordinate.y*8;
    //Now we need to see which case was clicked and send it to the appropriate function
    uint64_t click = intToBitboard(location);
    return handleClick(click, board);
}
uint64_t handleClick(uint64_t click, uint64_t* board){
    if(click&board[8]){
    return padatiMoves(click, board[0], board[1], 0);}
    else if(click&board[6]){
    return ashvaMoves(click, board[0]);
     }
    else if(click&board[3]){
    return rajaMoves(click, board[0]);
}
    else if(click&board[4]){
    return mantriMoves(click, board[0]);
}
    else if(click&board[5]){
    return rathaMoves(click, board[0],board[1]);
}
    else if(click&board[7]){
    return gajaMoves(click, board[0]);
}
    else if(click&board[14]){
    return padatiMoves(click, board[1], board[0], 1);}
    else if(click&board[12]){
    return ashvaMoves(click, board[1]);
}
    else if(click&board[9]){
    return rajaMoves(click, board[1]);
}
    else if(click&board[10]){
    return mantriMoves(click, board[1]);
}
    else if(click&board[11]){
    return rathaMoves(click, board[1],board[0]);
}
    else if(click&board[13]){
    return gajaMoves(click, board[1]);
}
return 0;
}

uint64_t* playMove(uint64_t click,uint64_t* board){
    //First we need to find the older piece
    printBitMap(board[1]&click);
    if(board[16]&board[0]){
        std::cout << "Affecting white";
    board[0] = board[0]&(~board[16]) | click;
    for(int i=3;i<9;i++)
    {
        if(board[16]&board[i])
        {
            board[i] = (board[i])&(~board[16]) | click;
        }
    }

        board[1] &= ~board[0];
        board[9] &= ~board[0];
        board[10] &= ~board[0];
        board[11] &= ~board[0];
        board[12] &= ~board[0];
        board[13] &= ~board[0];
        board[14] &= ~board[0];
    board[16] = 0;
    }
    else{
        std::cout << "Affecting black";
    board[1] = board[1]&(~board[16]) | click;
    for(int i=9;i<15;i++)
    {
        if(board[16]&board[i])
        {
            board[i] = (board[i])&(~board[16]) | click;
        }
    }
    board[0] &= ~board[1];
    board[3] &= ~board[1];
    board[4] &= ~board[1];
    board[5] &= ~board[1];
    board[6] &= ~board[1];
    board[7] &= ~board[1];
    board[8] &= ~board[1];
    board[16] = 0;
    }
    return board;
}
