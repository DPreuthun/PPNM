# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Target
TARGET = main

# Source files
SRCS = $(wildcard *.cc)
OBJS = $(SRCS:.cc=.o)

# Plot scripts
GPS = $(wildcard *.gp)

# Output files
DATA = interp.dat integ.dat data.dat
PLOTS = $(patsubst %.gp,%.png,$(GPS))

# Default: build everything
all: $(TARGET) run plot

# Link executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile
%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $<

# Run program → generates data files
run: $(TARGET)
	./$(TARGET)

# Run all gnuplot scripts → generates pngs
plot: $(GPS)
	@for file in $(GPS); do \
		echo "Running $$file"; \
		gnuplot $$file; \
	done

# Clean everything
clean:
	rm -f *.o $(TARGET) *.dat *.pdf