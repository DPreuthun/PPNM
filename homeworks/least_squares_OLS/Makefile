# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Files
SRCS = $(wildcard *.cc)
OBJS = $(SRCS:.cc=.o)
TARGET = main
OUT = out.txt

# Gnuplot files
GPFILES = $(wildcard *.gp)
PNGFILES = $(GPFILES:.gp=.png)

# Default
all: run plot

# Build executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile
%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run program
run: $(TARGET)
	./$(TARGET) > $(OUT)
	@echo "===== Program Output ====="
	@cat $(OUT)

# Run all gnuplot scripts
plot: $(GPFILES)
	@for file in $(GPFILES); do \
		echo "Running $$file"; \
		gnuplot $$file; \
	done

# Clean
clean:
	rm -f *.o $(TARGET) $(OUT) *.png data.txt