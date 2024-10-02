#include "eventhandler.h"
#include "util.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
bool validCLick(coord coordinates,uint64_t* board){
    uint8_t location = coordinates.x+coordinates.y*8;
    //We will tell if the click is valid or not
    if(intToBitboard(location)&board[0] || intToBitboard(location)&board[2]){
        return true;
    }
    return false;
}

uint64_t handleClick(coord coordinate, uint64_t* board){
    uint8_t location = coordinate.x+coordinate.y*8;
    //Now we need to see which case was clicked and send it to the appropriate function

}
