# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -g -std=c++17

# Source files and object files
SOURCES = main.cpp util.cpp maingraphics.cpp eventhandler.cpp moves.cpp moveshelper.cpp board.cpp engine.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Target executable
TARGET = main_program

# Build the executable
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Compile the .cpp files into .o object files
%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the program
run: $(TARGET)
	./$(TARGET)



# Clean object files and executable
clean:
	rm -f $(OBJECTS) $(TARGET)
