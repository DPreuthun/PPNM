CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -pthread

TARGET = multiprocessing

OBJS = main.o harm.o

N = 100000000

all: $(TARGET) benchmark plot
	@echo "Done."
	@echo "Plot saved as plot.png"

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cc harm.h
	$(CXX) $(CXXFLAGS) -c main.cc

harm.o: harm.cc harm.h
	$(CXX) $(CXXFLAGS) -c harm.cc

benchmark:
	@echo "#threads time" > times.txt
	@for t in 1 2 3 4 5 6 7 8; do \
		echo "Running $$t thread(s)..."; \
		/usr/bin/time -f "$$t %e" ./$(TARGET) -threads $$t -terms $(N) 2>> times.txt > /dev/null; \
	done

plot:
	gnuplot plot.gp

clean:
	rm -f *.o $(TARGET) times.txt plot.png