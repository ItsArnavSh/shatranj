#ifndef ENGINE_HELPER_H
#define ENGINE_HELPER_H

#include <cstdint>
#include <vector>

#include "eventhandler.h"

using namespace std;
uint64_t* copyArray(uint64_t* originalArray, int size) ;
vector<uint64_t> bitBreaker(uint64_t bitboard);

vector<uint64_t*> allMoves(uint64_t* board,bool turn);

int8_t gameOver(uint64_t* board);

#endif
