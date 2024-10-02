#include <cstdint>

// Masks the moves based on the side of the board to prevent leaking
uint64_t mask(uint64_t moves, uint64_t click) {
    // Left and right leak masks
    uint64_t left_leak = 0b0011111100111111001111110011111100111111001111110011111100111111;
    uint64_t right_leak = 0b1111110011111100111111001111110011111100111111001111110011111100;

    // Check if the click is in the right half of the board
    if (click & 0b1111000011110000111100001111000011110000111100001111000011110000) {
        moves &= right_leak;  // Clear the left side
    } else {
        moves &= left_leak;   // Clear the right side
    }

    return moves;
}

// Checks if the moves stay within board bounds, returns the lower 64 bits
uint64_t boardBoundCheck(__uint128_t moves) {
    __uint128_t board_bounds = 0xFFFFFFFFFFFFFFFF;  // 64 bits set to 1
    return static_cast<uint64_t>(moves & board_bounds);  // Returns the lower 64 bits of the masked moves
}

// Finds the possible moves based on direction and board boundaries
uint64_t findMoves(uint64_t moves, int8_t xdirection, int8_t ydirection, uint64_t enemy, uint64_t you) {
    uint64_t result = 0;

    // Define boundaries for left and right edges
    uint64_t xboundary_left = 0b10000000'10000000'10000000'10000000'10000000'10000000'10000000'10000000;
    uint64_t xboundary_right = 0b00000001'00000001'00000001'00000001'00000001'00000001'00000001'00000001;

    // Define boundaries for top and bottom edges
    uint64_t yboundary_top = 0b11111111'00000000'00000000'00000000'00000000'00000000'00000000'00000000;
    uint64_t yboundary_bottom = 0b00000000'00000000'00000000'00000000'00000000'00000000'00000000'11111111;

    while (true) {
        // Handle horizontal movement
        if (xdirection > 0) {
            if (moves & xboundary_right) {
                break;  // Moving right would go out of bounds
            }
            moves >>= xdirection;  // Move right
        } else if (xdirection < 0) {
            if (moves & xboundary_left) {
                break;  // Moving left would go out of bounds
            }
            moves <<= -xdirection;  // Move left
        }

        // Handle vertical movement
        if (ydirection > 0) {
            if (moves & yboundary_bottom) {
                break;  // Moving down would go out of bounds
            }
            moves >>= 8 * ydirection;  // Move down
        } else if (ydirection < 0) {
            if (moves & yboundary_top) {
                break;  // Moving up would go out of bounds
            }
            moves <<= 8 * (-ydirection);  // Move up
        }

        // Check if the move lands on a youly piece
        if (moves & you) {
            break;
        } else if (moves & enemy) {
            result |= moves;  // Capture the enemy piece
            break;
        }

        result |= moves;  // Add the valid move to the result
    }

    return result;
}
