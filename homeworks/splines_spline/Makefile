# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Target
TARGET = main
OUT = output.txt

# Source files
SRCS = $(wildcard *.cc)
OBJS = $(SRCS:.cc=.o)

# Plot scripts
GPS = $(wildcard *.gp)

# Output files
DATA = interp.dat integ.dat data.dat
PLOTS = $(patsubst %.gp,%.png,$(GPS))

# Default: build everything
all: run plot

# Link executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile
%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $<

# Run program → print + save output
run: $(TARGET)
	@echo "=== Running main ==="
	@./$(TARGET) | tee $(OUT)
	@echo "Output saved to $(OUT)"

# Run all gnuplot scripts → generates pngs
plot: $(GPS)
	@echo "=== Generating plots ==="
	@command -v gnuplot >/dev/null 2>&1 || { \
		echo "Warning: gnuplot not found, skipping plots."; \
		exit 0; \
	}
	@for file in $(GPS); do \
		echo "Running $$file"; \
		gnuplot $$file; \
	done

# Clean everything
clean:
	@echo "=== Cleaning ==="
	rm -f *.o $(TARGET) *.dat *.pdf *.png *.txt