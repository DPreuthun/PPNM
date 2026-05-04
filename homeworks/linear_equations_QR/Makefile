CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O3

COMMON = vecmatrix.o qr.o

# Default target
all: run plot

# -------- Main program --------
main: main.o $(COMMON)
	$(CXX) $(CXXFLAGS) $^ -o main

# -------- Timing program --------
time_scaling: time_scaling.o $(COMMON)
	$(CXX) $(CXXFLAGS) $^ -o time_scaling

# -------- Compile rule --------
%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

# -------- Run main program --------
run: main
	@echo "=== Running main ==="
	./main

# -------- Timing data generation --------
out.times.data: time_scaling
	@echo "=== Generating timing data ==="
	@> $@
	@for N in $$(seq 100 50 600); do \
		echo "Running N=$$N"; \
		/usr/bin/time --format "$$N %e" --output $@ --append \
		./time_scaling -size $$N ; \
	done
	@echo "Timing data saved to $@"

# -------- Plot generation --------
plot: out.times.data
	@echo "=== Generating plot ==="
	gnuplot plot.gp

# -------- Clean --------
clean:
	rm -f *.o *.pdf *.log main time_scaling out.times.data