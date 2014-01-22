CXX      = g++
CXXFLAGS = -std=c++11 -W -Wall -Wextra -Winline -pedantic -Isrc/

TEST_SRC = tests/buffer.cc    \
           tests/tuple.cc     \
           tests/endianess.cc \
           tests/container.cc

all: test

test:
	$(CXX) $(CXXFLAGS) -o test $(TEST_SRC) test.cc -lgtest
	./test
