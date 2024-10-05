#ifndef EVAL_H
#define EVAL_H

//This will be the evaluator function
#include <cstdint>

//6 Cases to consider
#include "util.h"

float evaluate(uint64_t* board);
float pieceAdvantage(uint64_t* board);
float piecePositioning(uint64_t* board);
float pieceCoordination(uint64_t* board);
float squaresUnderControl(uint64_t* board);

#endif
