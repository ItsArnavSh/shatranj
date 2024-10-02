//This section will handle all the clicks for us
#include "maingraphics.h"
#include "util.h"
#include "moves.h"
#include <cstdint>
#include <sys/types.h>
bool validCLick(coord coordinates,uint64_t* board);
uint64_t handleClick(coord coordinate, uint64_t* board);
uint64_t* playMove(uint64_t click,uint64_t* board);
