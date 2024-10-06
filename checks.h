#include <cstdint>
#ifndef CHECKS_H
#define CHECKS_H

uint64_t removeIllegal(uint64_t* board,uint64_t moves);
bool checkForCheck(uint64_t* board,bool turn);
#endif
