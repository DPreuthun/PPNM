CXX ?= g++
CXXFLAGS ?= -std=c++17 -O3 -Wall -Wextra

MAIN_OBJS = main.o jacobi.o vecmatrix.o
SCALE_OBJS = time_scaling.o jacobi.o vecmatrix.o

# Default target
all: run scaling plots

# ---------- compilation ----------

main: $(MAIN_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

time_scaling: $(SCALE_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $<

# ---------- run hydrogen solver ----------

run: main
	@echo "=== Running main (hydrogen solver) ==="
	./main -rmax 10 -dr 0.2 | tee output.txt
	@echo "Output also saved to output.txt"

# ---------- scaling test ----------

scaling: time_scaling
	@echo "=== Running scaling test ==="
	./time_scaling | tee scaling.dat
	@echo "Scaling data saved to scaling.dat"

# ---------- plotting ----------

plots:
	@echo "=== Generating plots ==="
	@command -v gnuplot >/dev/null 2>&1 || { \
		echo "Warning: gnuplot not found, skipping plots."; \
		exit 0; \
	}
	gnuplot plot_wavefunctions.gp
	gnuplot plot_dr.gp
	gnuplot plot_rmax.gp
	gnuplot plot_scaling.gp

# ---------- cleaning ----------

clean:
	@echo "=== Cleaning ==="
	rm -f *.o main time_scaling
	rm -f *.dat *.pdf *.png *.txt