CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O3

# Common source files (NO main files here)
COMMON = vecmatrix.o qr.o

# Default target: ONLY compile everything
all: main time_scaling

# -------- Main program --------
main: main.o $(COMMON)
	$(CXX) $(CXXFLAGS) $^ -o main

# -------- Timing program --------
time_scaling: time_scaling.o $(COMMON)
	$(CXX) $(CXXFLAGS) $^ -o time_scaling

# Compile rule
%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Timing data generation
out.times.data: time_scaling
	@> $@
	@for N in $$(seq 100 50 600); do \
		/usr/bin/time --format "$$N %e" --output $@ --append \
		./time_scaling -size $$N ; \
	done

# Plot generation
plot: out.times.data
	gnuplot plot.gp

# -------- RUN EVERYTHING --------
run: main plot
	./main

clean:
	rm -f *.o *.pdf *.log out err main time_scaling out.times.data