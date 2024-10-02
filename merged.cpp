// Contents of board.h
#include <cstdint>
#ifndef BOARD_H
#define BOARD_H

uint64_t* getBoard();

#endif // BOARD_H


// Contents of engine.h


// Contents of eventhandler.h
//This section will handle all the clicks for us
#include "maingraphics.h"
#include "util.h"
#include <cstdint>
#include <sys/types.h>
bool validCLick(coord coordinates,uint64_t* board);
uint64_t handleClick(coord coordinate, uint64_t* board);


// Contents of maingraphics.h
#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

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
#endif


// Contents of moves.h
//Here are all the functions for the moves which will be made here


// Contents of moveshelper.h


// Contents of util.h
#ifndef UTIL_H
#define UTIL_H

#include <cstdint>
#include <vector>
uint64_t intToBitboard(uint8_t num);
uint8_t bitBoardToInt(uint64_t bitboard);  // Ensure proper casing
std::vector<uint8_t> bitboardToVector(uint64_t bitboard);
#endif // UTIL_H


// Contents of board.cpp
#include "board.h"
#include <cstdint>

// Bitboards for the pieces based on the description:
// 0: Black pieces, 1: White pieces, 2: All available moves (could be updated dynamically)
// 3,9: Black and White Kings
// 4,10: Black and White Queens
// 5,11: Black and White Rooks
// 6,12: Black and White Knights
// 7,13: Black and White Bishops
// 8,14: Black and White Pawns

uint64_t* getBoard() {
    uint64_t* board = new uint64_t[16];

    // Initialize all bitboards to 0
    for (int i = 0; i < 16; ++i) {
        board[i] = 0;
    }

    // Black pieces
    board[0] = 0xFFFF000000000000;  // Black pieces occupy ranks 7 and 8 (rows 6 and 7 in 0-indexing)

    // White pieces
    board[1] = 0x000000000000FFFF;  // White pieces occupy ranks 1 and 2 (rows 0 and 1 in 0-indexing)

    // Kings
    board[3] = 0x1000000000000000;  // Black king starts at e8
    board[9] = 0x0000000000000010;  // White king starts at e1

    // Queens
    board[4] = 0x0800000000000000;  // Black queen starts at d8
    board[10] = 0x0000000000000008;  // White queen starts at d1

    // Rooks
    board[5] = 0x8100000000000000;  // Black rooks start at a8, h8
    board[11] = 0x0000000000000081;  // White rooks start at a1, h1

    // Knights
    board[6] = 0x4200000000000000;  // Black knights start at b8, g8
    board[12] = 0x0000000000000042;  // White knights start at b1, g1

    // Bishops
    board[7] = 0x2400000000000000;  // Black bishops start at c8, f8
    board[13] = 0x0000000000000024;  // White bishops start at c1, f1

    // Pawns
    board[8] = 0x00FF000000000000;  // Black pawns start on rank 7
    board[14] = 0x000000000000FF00;  // White pawns start on rank 2

    //turn
    board[15] = 1;
    // Moves bitboard (dynamic, initially 0)
    board[2] = 0x0;  // This will be populated dynamically when calculating available moves

    return board;
}


// Contents of engine.cpp


// Contents of eventhandler.cpp
#include "eventhandler.h"
#include "util.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
bool validCLick(coord coordinates,uint64_t* board){
    uint8_t location = coordinates.x+coordinates.y*8;
    //We will tell if the click is valid or not
    if(intToBitboard(location)&board[0] || intToBitboard(location)&board[2]){
        return true;
    }
    return false;
}

uint64_t handleClick(coord coordinate, uint64_t* board){
    uint8_t location = coordinate.x+coordinate.y*8;
    //Now we need to see which case was clicked and send it to the appropriate function

}


// Contents of main.cpp

#include "board.h"
#include "util.h"
#include "maingraphics.h"
#include <stdint.h>
#include <iostream>
int main(){
    //We first of all load the initial data from board.cpp
    uint64_t* gameState = getBoard();
    chessBoard game(gameState);
    game.drawBoard();
    //Now, we will send the data to graphics and boot the menu up

}


// Contents of maingraphics.cpp
#include "maingraphics.h"
#include "eventhandler.h"
#include "util.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <vector>
#include <iostream>


// Constructor for chessBoard class
chessBoard::chessBoard(uint64_t* bitboard)
    : window(sf::VideoMode(BOARD_SIZE * SQUARE_SIZE, BOARD_SIZE * SQUARE_SIZE), "Chess Game")
{
    this->board = bitboard;
    // Load all chess piece textures
    textures.resize(12);  // Assuming 12 pieces (6 for each side)
    loadTexture("pieces/raja-b.png", textures[0]);
    loadTexture("pieces/mantri-b.png", textures[1]);
    loadTexture("pieces/ratha-b.png", textures[2]);
    loadTexture("pieces/gaja-b.png", textures[3]);
    loadTexture("pieces/ashva-b.png", textures[4]);
    loadTexture("pieces/padati-b.png", textures[5]);
    loadTexture("pieces/raja-w.png", textures[6]);
    loadTexture("pieces/mantri-w.png", textures[7]);
    loadTexture("pieces/ratha-w.png", textures[8]);
    loadTexture("pieces/gaja-w.png", textures[9]);
    loadTexture("pieces/ashva-w.png", textures[10]);
    loadTexture("pieces/padati-w.png", textures[11]);
}

// Function to load textures by reference
bool chessBoard::loadTexture(const std::string &filename, sf::Texture &texture) {
    if (!texture.loadFromFile(filename)) {
        // Handle error
        return false;
    }
    return true;
}
// Function to draw the chessboard
void chessBoard::drawBoard() {
    // Colors for the board squares
    sf::Color lightSquareColor(240, 217, 181);  // Light squares (like beige)
    sf::Color darkSquareColor(181, 136, 99);    // Dark squares (like brown)

    // Main game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Handle mouse click event
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Get mouse position relative to the window
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    // Convert mouse position to board coordinates
                    uint8_t col = mousePos.x / SQUARE_SIZE;
                    uint8_t row = mousePos.y / SQUARE_SIZE;
                    if(validCLick({col,row}, this->board))
                    {
                        (this->board)[2] = handleClick({col,row}, this->board);
                    }
                    else {
                        (this->board)[2] = 0;
                    }
                    // Print the board coordinates to console
                    //std::cout << "Mouse clicked at board position: (" << col << ", " << row << ")" << std::endl;
                }
            }
        }

        // Clear the window
        window.clear();

        // Draw the chessboard squares
        for (int row = 0; row < BOARD_SIZE; ++row) {
            for (int col = 0; col < BOARD_SIZE; ++col) {
                sf::RectangleShape square(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
                square.setPosition(col * SQUARE_SIZE, row * SQUARE_SIZE);

                // Alternate colors for checkerboard pattern
                if ((row + col) % 2 == 0) {
                    square.setFillColor(lightSquareColor);  // Light square
                } else {
                    square.setFillColor(darkSquareColor);   // Dark square
                }

                // Draw each square
                window.draw(square);
            }
        }

        for (int i = 3; i < 15; i++) {
            std::vector<uint8_t> num = bitboardToVector(board[i]);
            for (auto j : num)
                drawPiece({uint8_t(j % 8), uint8_t(j / 8)}, i - 3);
        }

        // Display the window contents
        window.display();
    }
}

// Function to draw a piece at a given coordinate
void chessBoard::drawPiece(coord coordinate, uint8_t index) {
    sf::Sprite pieceSprite;
    pieceSprite.setTexture(textures[index]);
    pieceSprite.setPosition(coordinate.x * SQUARE_SIZE, coordinate.y * SQUARE_SIZE);
    window.draw(pieceSprite);
}


// Contents of merged.cpp


// Contents of moves.cpp


// Contents of moveshelper.cpp


// Contents of util.cpp
#include "util.h"

uint64_t intToBitboard(uint8_t num) {
    if (num < 0 || num > 63) {
        return 0;  // Invalid position, return 0
    }
    return 1ULL << num;  // Shift a 1 to the left by `num` positions
}

uint8_t bitBoardToInt(uint64_t bitboard) {
    if (bitboard == 0) {
        return -1;  // No valid bit set
    }

    // Find the position of the first (and only) bit set to 1
    int pos = 0;
    while ((bitboard & 1) == 0) {
        bitboard >>= 1;
        pos++;
    }
    return pos;
}

std::vector<uint8_t> bitboardToVector(uint64_t bitboard) {
    std::vector<uint8_t> positions;

    for (int i = 0; i < 64; ++i) {
        if (bitboard & (1ULL << i)) {  // Check if the i-th bit is set
            positions.push_back(i);     // Add the position to the vector
        }
    }

    return positions;
}


