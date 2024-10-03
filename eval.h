//This will be the evaluator function
#include <cstdint>
//6 Cases to consider
#ifndef UTIL_H
#define UTIL_H

int8_t evaluate(uint64_t* board);
int8_t pieceAdvantage(uint64_t* board);
int8_t piecePositioning(uint64_t* board);
int8_t pieceCoordination(uint64_t* board);
int8_t squaresUnderControl(uint64_t* board);

#endif
