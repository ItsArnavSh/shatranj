
#include "engine.h"
#include "engineHelper.h"

float alphaBeta(uint64_t* position, uint8_t depth, bool maximizingPlayer, float alpha, float beta) {
    if (depth == 0) {
        return evaluate(position); // Assuming evaluate() returns an evaluation score
    }

    vector<uint64_t*> possibleMoves = allMoves(position, maximizingPlayer); // Get all moves for the current player

    if (maximizingPlayer) { // Engine's turn (Maximizing)
        float maxEval = -100; // Initialize to a low value
        for (auto& move : possibleMoves) {
            float eval = alphaBeta(move, depth - 1, !maximizingPlayer, alpha, beta); // Opponent's turn next
            maxEval = std::max(maxEval, eval);
            alpha = std::max(alpha, eval);
            if (beta <= alpha) {
                break; // Beta cut-off
            }
        }
        return maxEval;
    } else { // Opponent's turn (Minimizing)
        float minEval = 100; // Initialize to a high value
        for (auto& move : possibleMoves) {
            float eval = alphaBeta(move, depth - 1, !maximizingPlayer, alpha, beta); // Engine's turn next
            minEval = std::min(minEval, eval);
            beta = std::min(beta, eval);
            if (beta <= alpha) {
                break; // Alpha cut-off
            }
        }
        return minEval;
    }
}

uint64_t* levy(uint64_t* board, bool enginePlaysWhite) {
    // Get all possible moves for the current board state
    vector<uint64_t*> allM = allMoves(board, enginePlaysWhite); // Current player
    if (allM.empty()) return nullptr; // Safety check if no moves are available

    uint64_t* bestMove = allM[0]; // Default to the first move
    float alpha = -1000000;
    float beta = 1000000;
    float bestEval = -10000000;

    // Evaluate each possible move using alpha-beta pruning
    for (uint8_t i = 0; i < allM.size(); ++i) {
        // If engine is White, maximizingPlayer is true. If engine is Black, maximizingPlayer is false.
        bool maximizingPlayer = !enginePlaysWhite;
        float eval = alphaBeta(allM[i], 3, !maximizingPlayer, alpha, beta); // Opponent's turn initially
        if (eval > bestEval) {
            bestEval = eval;
            bestMove = allM[i]; // Select the best move
        }
    }

    return bestMove;
}
