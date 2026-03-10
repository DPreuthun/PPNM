# Compiler
CXX = g++

# Flags
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Target executable
TARGET = main

# All source files
SRC = $(wildcard *.cc)

# Object files
OBJ = $(SRC:.cc=.o)

# Default rule
all: $(TARGET)

# Link executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET)

# Compile source files
%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f *.o $(TARGET)