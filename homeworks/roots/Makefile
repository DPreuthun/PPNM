# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2

# Files
SRCS = $(wildcard *.cc)
OBJS = $(SRCS:.cc=.o)

# Executable
TARGET = main

# Output file
OUT = out.txt

# Plot outputs
PLOTS = wave.png conv_rmax.png conv_rmin.png conv_h.png

# Default target
.PHONY: all run plots clean

all: run plots

# Build executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile source files
%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run program (generates data files)
run: $(TARGET)
	@echo "Running program..."
	@./$(TARGET) | tee $(OUT)

# Generate plots
plots: $(PLOTS)

wave.png: wave.gp wave.txt
	@echo "Generating wave plot..."
	@gnuplot wave.gp

conv_rmax.png: conv_rmax.gp conv_rmax.txt
	@echo "Generating rmax convergence plot..."
	@gnuplot conv_rmax.gp

conv_rmin.png: conv_rmin.gp conv_rmin.txt
	@echo "Generating rmin convergence plot..."
	@gnuplot conv_rmin.gp

conv_h.png: conv_h.gp conv_h.txt
	@echo "Generating step size convergence plot..."
	@gnuplot conv_h.gp

# Clean build files
clean:
	@echo "Cleaning build files..."
	@rm -f $(OBJS) $(TARGET)
	@rm -f $(OUT)
	@rm -f *.txt
	@rm -f $(PLOTS)