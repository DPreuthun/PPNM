CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2

SRC = $(wildcard *.cc)
OBJ = $(SRC:.cc=.o)

TARGET = main

GPFILES = $(wildcard *.gp)

all: $(TARGET)
	./$(TARGET) < higgs_data.txt | tee output.txt
	@for gp in $(GPFILES); do \
		echo "Running $$gp..."; \
		gnuplot $$gp; \
	done

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o $(TARGET) output.txt *.dat *.png