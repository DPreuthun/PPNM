CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

TARGET = generic_list

SRCS = main.cc
OBJS = $(SRCS:.cc=.o)

all: $(TARGET)
	./$(TARGET) < input.txt

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)