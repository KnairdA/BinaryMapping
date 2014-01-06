CXX      = g++
CXXFLAGS = -std=c++11 -W -Wall -Wextra -Winline -pedantic -Isrc/

all: test

test:
	$(CXX) $(CXXFLAGS) -o test test.cc -lgtest
	./test

