#include "maingraphics.h"
#include "eventhandler.h"
#include "util.h"
#include <SFML/Graphics/CircleShape.hpp>
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
    loadTexture("pieces/raja-w.png", textures[0]);
    loadTexture("pieces/mantri-w.png", textures[1]);
    loadTexture("pieces/ratha-w.png", textures[2]);
    loadTexture("pieces/ashva-w.png", textures[3]);
    loadTexture("pieces/gaja-w.png", textures[4]);
    loadTexture("pieces/padati-w.png", textures[5]);
    loadTexture("pieces/raja-b.png", textures[6]);
    loadTexture("pieces/mantri-b.png", textures[7]);
    loadTexture("pieces/ratha-b.png", textures[8]);
    loadTexture("pieces/ashva-b.png", textures[9]);
    loadTexture("pieces/gaja-b.png", textures[10]);
    loadTexture("pieces/padati-b.png", textures[11]);
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
// Function to draw the chessboard
void chessBoard::drawBoard() {
    // Colors for the board squares
    sf::Color lightSquareColor(240, 217, 181);  // Light squares (like beige)
    sf::Color darkSquareColor(181, 136, 99);    // Dark squares (like brown)
    sf::Color moveCircleColor(50, 205, 50, 150); // Semi-transparent green for move indication

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
                    if (validCLick({col, row}, this->board)) {
                        (this->board)[2] = handleClick({col, row}, this->board);
                    (this->board)[16] = intToBitboard(col+row*8);}
                    else if(intToBitboard(col+row*8)&this->board[2]){
                        this->board = playMove(intToBitboard(col+row*8),board);
                        this->board[2]=0;
                    }
                    else {
                        (this->board)[2] = 0;
                    }
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

        // Draw the pieces
        for (int i = 3; i < 15; i++) {
            std::vector<uint8_t> num = bitboardToVector(board[i]);
            for (auto j : num)
                drawPiece({uint8_t(j % 8), uint8_t(j / 8)}, i - 3);
        }

        // Plotting all the moves in this->board[2]
        if (this->board[2] != 0) {
            std::vector<uint8_t> moves = bitboardToVector(this->board[2]);
            for (auto move : moves) {
                uint8_t col = move % 8;
                uint8_t row = move / 8;

                // Draw a semi-transparent circle on the possible move square
                sf::CircleShape moveCircle(SQUARE_SIZE / 4);  // Radius is half the size of the square
                moveCircle.setFillColor(moveCircleColor);
                moveCircle.setPosition(col * SQUARE_SIZE + SQUARE_SIZE / 4, row * SQUARE_SIZE + SQUARE_SIZE / 4);
                window.draw(moveCircle);
            }
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
