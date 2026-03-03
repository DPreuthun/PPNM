CXX = g++ -std=c++23
CXXFLAGS = -Wall -Wextra -Werror -O
LDLIBS += -lstdc++ -lm

Out.txt: main
	./$< > $@

clean:
	$(RM) main Out.txt *.o