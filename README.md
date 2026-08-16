# shatranj

A chess engine and graphical client for **Shatranj**, the ancient predecessor of modern chess. Written in C++17 with SFML.

## Features

- Bitboard representation of the board
- Search engine (`carlsen`, `levy`) with position evaluation
- Graphical chessboard rendered with SFML and custom piece sprites (in `pieces/`)

## Layout

```
Shatranj/
├── src/            # C++ source files
├── include/        # C++ header files
├── pieces/         # Piece sprite images (PNG)
├── Makefile
└── README.md
```

## Requirements

- C++17 compiler (`g++`)
- SFML 2.x (`libsfml-graphics`, `libsfml-window`, `libsfml-system`)

## Build & Run

Run from the project root (the `pieces/` sprites are loaded relative to the working directory):

```
make build     # compile into ./main_program
make run       # build and run
make clean     # remove object files and the binary
make status    # show project file/line stats
```
