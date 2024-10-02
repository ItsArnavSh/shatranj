#include "maingraphics.h"
#include "util.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <vector>

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
/*
        for(int i=3;i<15;i++)
        {
            std::vector<int> num = bitboardToVector(board[i]);

            //drawPiece({1,1}, i-3);
        }
*/
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
