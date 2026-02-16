CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O 
LINK.o = $(CXX) $(LDFLAGS)
LDLIBS += -lstdc++ -lm

Out.txt : main
	./main > Out.txt

main : main.o computeepsilon.o actualepsilon.o

main.o : computeepsilon.o actualepsilon.o

actualepsilon.o: actualepsilon.h actualepsilon.cc

computeepsilon.o: computeepsilon.h computeepsilon.cc

clean:
	$(RM) main main.o Out.txt *.o

test:
	@echo CXX
	@echo $(CXX)
	@echo $(RM)
	@echo $(CC)
