# Allow overriding compiler (portable)
CXX ?= g++
CXXFLAGS ?= -std=c++17 -O3 -Wall -Wextra

MAIN_OBJS = main.o jacobi.o vecmatrix.o
SCALE_OBJS = time_scaling.o jacobi.o vecmatrix.o

# Default target
all: main time_scaling run scaling plots

# ---------- compilation ----------

main: $(MAIN_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

time_scaling: $(SCALE_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $<

# ---------- run hydrogen solver ----------

run: main
	./main -rmax 10 -dr 0.2 > output.txt

# ---------- scaling test ----------

scaling: time_scaling
	./time_scaling > scaling.dat

# ---------- plotting ----------

plots:
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
	rm -f *.o main time_scaling
	rm -f *.dat *.pdf *.txt