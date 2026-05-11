CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

TARGET = plots

OBJS = main.o sfuns.o

all: $(TARGET) graph
	@echo "All plots generated."

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cc sfuns.h
	$(CXX) $(CXXFLAGS) -c main.cc

sfuns.o: sfuns.cc sfuns.h
	$(CXX) $(CXXFLAGS) -c sfuns.cc

graph: $(TARGET)
	./$(TARGET)
	gnuplot erf_plot.gp
	gnuplot gamma_plot.gp
	gnuplot lngamma_plot.gp

clean:
	rm -f *.o $(TARGET) *.txt *.png