#ifndef ENGINE_H
#define ENGINE_H
#include <random>
#include <iostream>
#include <cstdint>

#include "eval.h"
#include "engineHelper.h"

uint64_t* dunningKruger(uint64_t* board);
uint64_t* carlsen(uint64_t* board);

#endif // ENGINE_H
