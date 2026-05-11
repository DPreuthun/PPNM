CXX ?= g++
CXXFLAGS ?= -std=c++17 -O3 -Wall -Wextra

MAIN_OBJS = main.o jacobi.o vecmatrix.o
SCALE_OBJS = time_scaling.o jacobi.o vecmatrix.o

# Output files
MAIN_OUTPUT = output.txt
SCALING_OUTPUT = scaling.dat

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
	@./main -rmax 10 -dr 0.2 | tee $(MAIN_OUTPUT)
	@echo "Output also saved to $(MAIN_OUTPUT)"

# ---------- scaling test ----------

scaling: time_scaling
	@echo "=== Running scaling test ==="
	@./time_scaling | tee $(SCALING_OUTPUT)
	@echo "Scaling data saved to $(SCALING_OUTPUT)"

# ---------- plotting ----------

plots:
	@echo "=== Generating plots ==="
	@command -v gnuplot >/dev/null 2>&1 || { \
		echo "Warning: gnuplot not found, skipping plots."; \
		exit 0; \
	}
	@gnuplot plot_wavefunctions.gp
	@gnuplot plot_dr.gp
	@gnuplot plot_rmax.gp
	@gnuplot plot_scaling.gp

# ---------- cleaning ----------

clean:
	@echo "=== Cleaning ==="
	rm -f *.o main time_scaling
	rm -f *.dat *.pdf *.png *.txt