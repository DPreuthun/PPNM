CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O 
LINK.o = $(CXX) $(LDFLAGS)
LDLIBS += -lstdc++ -lm

Out.txt : main
	./main > Out.txt

main : main.o sfuns.o
#	$(CXX) $(LDFLAGS) main.o hello.o sfuns.o $(LDLIBS) -o main
#	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o main 

main.o : sfuns.o
#	$(CXX) $(CXXFLAGS) -c main.cc -o main.o

sfuns.o: sfuns.h sfuns.cc
#	$(CXX) $(CXXFLAGS) -c sfuns.cc -o sfuns.o

clean:
	$(RM) main main.o Out.txt *.o

test:
	@echo CXX
	@echo $(CXX)
	@echo $(RM)
	@echo $(CC)
