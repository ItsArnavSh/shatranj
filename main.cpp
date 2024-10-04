
#include "board.h"
#include "maingraphics.h"
#include <stdint.h>
int main(){
    //We first of all load the initial data from board.cpp
    uint64_t* gameState = getBoard();
    chessBoard game(gameState);
    game.drawBoard();
    //Now, we will send the data to graphics and boot the menu up

}
