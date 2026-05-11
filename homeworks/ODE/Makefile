CXX = g++
CXXFLAGS = -O2 -std=c++23

SRC = $(wildcard *.cc)
OBJ = $(SRC:.cc=.o)

TARGET = main
OUTPUT = output.txt

GP = $(wildcard *.gp)

all: $(TARGET)
	@echo "Running program..."
	@./$(TARGET) | tee $(OUTPUT)

	@echo "Generating plots..."
	@for gp in $(GP); do gnuplot $$gp; done

	@echo "Done."

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o $(TARGET)
	rm -f *.txt
	rm -f *.png