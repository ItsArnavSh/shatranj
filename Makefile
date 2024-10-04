# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -g -std=c++17

# SFML libraries
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Target executable
TARGET = main_program

# Source files
SRCS = board.cpp  engine.cpp  engineHelper.cpp  eval.cpp  eventhandler.cpp  evhelp.cpp  main.cpp  maingraphics.cpp  moves.cpp  moveshelper.cpp  util.cpp debugger.cpp security.cpp

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
# check status
status:
	@echo Currently `ls *.h *.cpp 2>/dev/null | wc -l` files in the project;
	@echo There are `cat *.h *.cpp 2>/dev/null | wc -l` lines completed;
	@echo `expr 1000 - \`cat *.h *.cpp 2>/dev/null | wc -l\`` lines remaining to reach 1000;
