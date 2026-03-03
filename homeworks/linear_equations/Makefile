# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Wextra -g

# Target executable name
TARGET = main

# Automatically find all .cc files
SOURCES = $(wildcard *.cc)

# Replace .cc with .o
OBJECTS = $(SOURCES:.cc=.o)

# Default rule (runs when you type "make")
all: $(TARGET)

# Link object files into final executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)

# Compile each .cc file into .o file
%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJECTS) $(TARGET)

# Run program
run: $(TARGET)
	./$(TARGET)