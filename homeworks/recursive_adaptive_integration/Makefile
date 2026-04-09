# ===== Compiler =====
CXX := g++

# ===== Flags (portable across CPUs & systems) =====
CXXFLAGS := -O2 -std=c++17 -Wall -Wextra -pedantic -MMD -MP

# ===== Automatically find all source files =====
SRC := $(wildcard *.cc)
OBJ := $(SRC:.cc=.o)

# ===== Find all gnuplot files =====
GP := $(wildcard *.gp)

# ===== Executable name =====
TARGET := main

# ===== Default target =====
all: run plot

# ===== Link step =====
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

# ===== Compile step =====
%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ===== Run program → produce + print out.txt =====
run: $(TARGET)
	@echo "Running program..."
	./$(TARGET) > out.txt
	@echo "===== out.txt ====="
	@cat out.txt

# ===== Run all gnuplot scripts =====
plot: out.txt
	@echo "Running gnuplot scripts..."
	@for f in $(GP); do \
		echo "Plotting $$f"; \
		gnuplot $$f; \
	done

# ===== Clean everything =====
clean:
	rm -f *.o *.d $(TARGET) out.txt *.png

# ===== Include dependency files =====
-include $(OBJ:.o=.d)

.PHONY: all clean run plot