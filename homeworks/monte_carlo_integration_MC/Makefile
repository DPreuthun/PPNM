# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall

# Executable name
TARGET = mc
OUT = output.txt

# Source files
SRCS = $(wildcard *.cc)
OBJS = $(SRCS:.cc=.o)

# All gnuplot scripts
GPFILES = $(wildcard *.gp)

# Default target
all: $(TARGET) run plots done

# Link step
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile step
%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run program (print + save output)
run: $(TARGET)
	@echo "Running program..."
	@./$(TARGET) | tee $(OUT)

# Run all gnuplot scripts (each .gp creates its own .png)
plots: $(OUT)
	@echo "Generating plots..."
	@if [ -z "$(GPFILES)" ]; then \
		echo "No .gp files found."; \
	else \
		for f in $(GPFILES); do \
			echo "→ Running $$f"; \
			gnuplot $$f; \
		done \
	fi

# Final message
done:
	@echo "Done!"
	@echo "→ Output file: $(OUT)"
	@echo "→ PNG plots generated from all .gp files"

# Clean everything
clean:
	rm -f $(OBJS) $(TARGET) *.txt *.png fit.log