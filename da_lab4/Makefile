CXX = g++
CXXFLAGS = -std=c++11 -O2 -Wextra -Wall -Wno-sign-compare -Wno-unused-result
FILES = main.cpp
NAME = solution

all: example

example:
	$(CXX) $(CXXFLAGS) -o $(NAME) $(FILES) -g

clean:
	rm -f *.o $(NAME)