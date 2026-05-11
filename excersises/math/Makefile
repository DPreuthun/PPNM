CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++20

TARGET = math

OBJS = main.o sfuns.o

all: $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cc sfuns.h
	$(CXX) $(CXXFLAGS) -c main.cc

sfuns.o: sfuns.cc sfuns.h
	$(CXX) $(CXXFLAGS) -c sfuns.cc

clean:
	rm -f *.o $(TARGET)