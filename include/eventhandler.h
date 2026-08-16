#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

//This section will handle all the clicks for us
#include <cstdint>
#include <sys/types.h>

#include "maingraphics.h"
#include "util.h"
#include "moves.h"
#include "debugger.h"

bool validCLick(coord coordinates,uint64_t* board,bool turn);

uint64_t handleClick(coord coordinate, uint64_t* board);

uint64_t handleClick(uint64_t click, uint64_t* board);

uint64_t* playMove(uint64_t click,uint64_t* board);

#endif
