CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

TARGET = cinout

SRCS = main.cc io_tasks.cc
OBJS = $(SRCS:.cc=.o)

all: $(TARGET)
	./$(TARGET) --input input.txt --output output.txt
	cat output.txt

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET) output.txt