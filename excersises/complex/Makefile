CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

TARGET = complex

SRCS = main.cc complex_tasks.cc approx.cc
OBJS = $(SRCS:.cc=.o)

all: $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)