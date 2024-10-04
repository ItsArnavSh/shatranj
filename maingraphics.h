#ifndef MAINGRAPHICS_H
#define MAINGRAPHICS_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#include "debugger.h"
#include "board.h"

/// Chessboard dimensions
const int BOARD_SIZE = 8;
const int SQUARE_SIZE = 100;

// Struct to represent a coordinate
struct coord {
    uint8_t x;
    uint8_t y;
};

class chessBoard {
public:
    uint64_t* board;
    // Constructor
    chessBoard(uint64_t* bitboard);

    // Function to draw the chessboard
    void drawBoard();

    // Function to draw a chess piece
    void drawPiece(coord coordinate, uint8_t index);

private:
    // Function to load textures for chess pieces
    bool loadTexture(const std::string &filename, sf::Texture &texture);

    // SFML RenderWindow instance
    sf::RenderWindow window;

    // Vector to hold textures of chess pieces
    std::vector<sf::Texture> textures;
};

#endif // CHESSBOARD_H
