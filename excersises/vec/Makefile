CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

TARGET = vecprog

OBJS = main.o vec.o

all: $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cc vec.h
	$(CXX) $(CXXFLAGS) -c main.cc

vec.o: vec.cc vec.h
	$(CXX) $(CXXFLAGS) -c vec.cc

clean:
	rm -f *.o $(TARGET)