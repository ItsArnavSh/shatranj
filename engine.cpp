
#include "engine.h"
#include "engineHelper.h"
int randomInt(int min, int max) {
    // Create a random device and use it to seed the random number generator
    std::random_device rd;
    std::mt19937 gen(rd()); // Mersenne Twister generator seeded with random_device
    std::uniform_int_distribution<> distr(min, max); // Define range

    // Return a random number in the range [min, max]
    return distr(gen);
}
uint64_t* dunningKruger(uint64_t* board)
{
    //This is a test function,
    //All it will do is return a random move
    //Just for seeing if the frontend works
    vector<uint64_t*> answers = allMoves(board,true);

    return answers[randomInt(0, answers.size()-1)];
    //Pick any piece at random, and any move at random to make things interesting
}
int8_t minimax(uint64_t* position,uint8_t depth,bool turn)
{
    if(depth==0)
    {
        return evaluate(position);
    }
        if(turn)
        {
            uint8_t maxEval = -100;
            vector<uint64_t*> eachCase = allMoves(position,turn);
            for(auto ec:eachCase)
            {
                uint8_t eval = minimax(ec, depth-1, !turn);
                maxEval = eval>maxEval?eval:maxEval;
            }
            return maxEval;
        }
        else{
            uint8_t minEval = 100;
            vector<uint64_t*> eachCase = allMoves(position,turn);
            for(auto ec:eachCase)
            {
                uint8_t eval = minimax(ec, depth-1, !turn);
                minEval = eval<minEval?eval:minEval;
            }
            return minEval;
        }

}
uint64_t* carlsen(uint64_t* board){
    //Now We will just get the winning case here
    vector<uint64_t*> allM = allMoves(board,true);
    uint8_t bestMoveIndex = 0;
    uint8_t worstEval = -100;
    for(uint8_t i=0;i<allM.size();i++){
        uint8_t eval = minimax(board, 3, true);
        if(eval<worstEval)
        {
            worstEval = eval;
            bestMoveIndex = i;
        }
    }
    return allM[bestMoveIndex];
}
