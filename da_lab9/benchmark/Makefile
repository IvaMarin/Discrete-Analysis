CXX = g++
CXXFLAGS = -std=c++11 -O2 -Wextra -Wall -Wno-sign-compare -Wno-unused-result
FILES = main.cpp
NAME = solution_dfs

all: NAME

NAME:
	$(CXX) $(CXXFLAGS) -o $(NAME) $(FILES)

debug:
	$(CXX) $(CXXFLAGS) -o $(NAME) $(FILES) -g3

run:
	./$(NAME) < ../tests/test_02.t

clean:
	rm -f *.o $(NAME)