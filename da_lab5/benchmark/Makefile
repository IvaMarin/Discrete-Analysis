CXX = g++
CXXFLAGS = -std=c++11 -O2 -Wextra -Wall -Wno-sign-compare -Wno-unused-result
FILES = main.cpp
NAME = solution

all: solution

solution:
	$(CXX) $(CXXFLAGS) -o $(NAME) $(FILES)

run:
	./$(NAME) < ../tests/test_100.t

clean:
	rm -f *.o $(NAME)