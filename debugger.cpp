#include <iostream>
#include "debugger.h"
void printBitMap(uint64_t map)
{
    std::cout << std::endl;
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            std::cout << (map&1)<<" ";
            map >>=1;
        }
        std::cout << std::endl;
    }
}
