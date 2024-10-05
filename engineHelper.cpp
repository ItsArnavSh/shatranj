#include "engineHelper.h"
#include <cstdlib>
using namespace std;
std::vector<uint64_t> bitBreaker(uint64_t bitboard){
    std::vector<uint64_t> result;

       while (bitboard) {
           // Get the least significant set bit (isolates the rightmost 1-bit)
           uint64_t lsb = bitboard & -bitboard;

           // Add this bitboard with a single set bit to the result
           result.push_back(lsb);

           // Remove the least significant set bit from the bitboard
           bitboard &= (bitboard - 1);
       }

       return result;
}
uint64_t* copyArray(uint64_t* originalArray, int size) {
    // Allocate memory for the new array
    uint64_t* newArray = new uint64_t[size];

    // Copy elements from original to new array
    for (int i = 0; i < size; i++) {
        newArray[i] = originalArray[i];
    }

    return newArray; // Return the pointer to the new array
}
std::vector<uint64_t*> allMoves(uint64_t* board,bool turn){
   int adder = turn?9:3;
   std::vector<uint64_t*> allMoves;
   for(int i=adder;i<adder+6;i++)
   {
       //To get all instances of the piece
       std::vector<uint64_t> instances = bitBreaker(board[i]);
       //Noe lets mark that piece as the last location
       for(auto instance:instances)
       {
           uint64_t* newArr = copyArray(board, 17);
           newArr[16] = instance;
           //Now we need to find all the possible moves for this
           newArr[2] = handleClick(instance,newArr);
           std::vector<uint64_t> moves = bitBreaker(newArr[2]);
           //Now we need to play each move and add it to allMoves
           for(auto move:moves)
           {
               uint64_t *preserve = copyArray(newArr, 17);
               allMoves.push_back(playMove(move, preserve));
           }
       }
   }
   return allMoves;
}
int8_t gameOver(uint64_t* board){
    if(board[0]&board[9])
        return 1;//Black One
    else if(board[1]&board[3])
        return -1;
    else
        return 0;
}
