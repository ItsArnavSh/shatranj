# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -g -std=c++17

# SFML libraries
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Target executable
TARGET = main_program

# Source files
SRCS = main.cpp util.cpp maingraphics.cpp eventhandler.cpp moves.cpp moveshelper.cpp board.cpp engine.cpp

# Object files (replace .cpp with .o)
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(SFML_LIBS)

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean the build
clean:
	rm -f $(OBJS) $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)
