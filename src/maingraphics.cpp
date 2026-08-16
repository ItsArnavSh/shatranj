#include "maingraphics.h"
#include "eval.h"
#include "eventhandler.h"
#include "engineHelper.h"
#include "security.h"
#include "util.h"
#include "engine.h"
#include "debugger.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>
#include <stack>
#include <vector>
#include <algorithm>
#include "eventhandler.h"
#include <iostream>
// Constructor for chessBoard class
std::vector<uint64_t> copyArrayToVector(uint64_t* src, size_t size) {
    return std::vector<uint64_t>(src, src + size);
}
void assignVectorToBoard(const std::vector<uint64_t>& vec, uint64_t* dest, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        dest[i] = vec[i];
    }
}
bool turn = false;
chessBoard::chessBoard(uint64_t* bitboard)
    : window(sf::VideoMode({BOARD_SIZE * SQUARE_SIZE, BOARD_SIZE * SQUARE_SIZE}), "Chess Game")
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
    stack<vector<uint64_t>> history;
    history.push(copyArrayToVector(this->board, 17));
    // Colors for the board squares
    sf::Color lightSquareColor(240, 217, 181);  // Light squares (like beige)
    sf::Color darkSquareColor(181, 136, 99);    // Dark squares (like brown)
    sf::Color moveCircleColor(50, 205, 50, 150); // Semi-transparent green for move indication

    // Main game loop
    while (window.isOpen()) {
        // Board layout: square board scaled to the actual window size
        sf::Vector2u wsize = window.getSize();
        window.setView(sf::View(sf::FloatRect({0.0f, 0.0f}, {float(wsize.x), float(wsize.y)})));
        float boardPx = std::min(float(wsize.x), float(wsize.y));
        float squareSize = boardPx / BOARD_SIZE;
        sf::Vector2f origin((float(wsize.x) - boardPx) / 2.0f, (float(wsize.y) - boardPx) / 2.0f);

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>() || gameOver(board)==-1 || gameOver(board)==1)
                window.close();

            // Handle mouse click event
            if(!turn){
                if (const auto* mouseButton = event->getIf<sf::Event::MouseButtonPressed>()) {
                    if (mouseButton->button == sf::Mouse::Button::Right) {
                        if(!history.empty()){
                            history.pop();
                            assignVectorToBoard(history.top(), board,17);
                        }
                    }
                    if (mouseButton->button == sf::Mouse::Button::Left) {
                        // Convert mouse position to board coordinates
                        bool inside = mouseButton->position.x >= origin.x &&
                                      mouseButton->position.y >= origin.y &&
                                      mouseButton->position.x < origin.x + boardPx &&
                                      mouseButton->position.y < origin.y + boardPx;
                        if (!inside) {
                            (this->board)[2] = 0;
                        }
                        else {
                            uint8_t col = uint8_t((mouseButton->position.x - origin.x) / squareSize);
                            uint8_t row = uint8_t((mouseButton->position.y - origin.y) / squareSize);

                            if (validCLick({col, row}, this->board,turn)) {
                                (this->board)[2] = handleClick({col, row}, this->board);

                                (this->board)[16] = intToBitboard(col+row*8);
                            }
                            else if(intToBitboard(col+row*8)&this->board[2]){

                                this->board = playMove(intToBitboard(col+row*8),board);
                                this->board[2]=0;
                                turn=!turn;
                                history.push(copyArrayToVector(this->board, 17));
                                std::cout << "User: "<<std::endl;
                                printBitMap(board[0]);
                                std::cout << "Evaluation" << int(evaluate(board));

                            }
                            else {
                                (this->board)[2] = 0;
                            }
                        }
                    }
                }
                board = verifyBoard(board);
            }
            else{
                board = levy(board,true);
                turn=!turn;
                board[2] = 0;
                history.push(copyArrayToVector(this->board, 17));
                board = verifyBoard(board);
            }
        }



        // Clear the window
        window.clear();

        // Draw the chessboard squares
        for (int row = 0; row < BOARD_SIZE; ++row) {
            for (int col = 0; col < BOARD_SIZE; ++col) {
                sf::RectangleShape square(sf::Vector2f(squareSize, squareSize));
                square.setPosition({origin.x + col * squareSize, origin.y + row * squareSize});
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
                drawPiece({uint8_t(j % 8), uint8_t(j / 8)}, i - 3, origin, squareSize);
        }

        // Plotting all the moves in this->board[2]
        if (this->board[2] != 0) {
            std::vector<uint8_t> moves = bitboardToVector(this->board[2]);
            for (auto move : moves) {
                uint8_t col = move % 8;
                uint8_t row = move / 8;

                // Draw a semi-transparent circle on the possible move square
                sf::CircleShape moveCircle(squareSize / 4);  // Radius is half the size of the square
                moveCircle.setFillColor(moveCircleColor);
                moveCircle.setPosition({origin.x + col * squareSize + squareSize / 4, origin.y + row * squareSize + squareSize / 4});
                window.draw(moveCircle);
            }
        }

        // Display the window contents
        window.display();
    }
}

// Function to draw a piece at a given coordinate
void chessBoard::drawPiece(coord coordinate, uint8_t index, sf::Vector2f origin, float squareSize) {
    sf::Sprite pieceSprite(textures[index]);
    pieceSprite.setPosition({origin.x + coordinate.x * squareSize, origin.y + coordinate.y * squareSize});
    float scale = squareSize / SQUARE_SIZE;
    pieceSprite.setScale({scale, scale});
    window.draw(pieceSprite);
}
