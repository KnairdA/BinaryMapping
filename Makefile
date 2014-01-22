CXX      = g++
CXXFLAGS = -std=c++11 -W -Wall -Wextra -Winline -pedantic -Isrc/

TEST_SRC = tests/buffer.cc    \
           tests/tuple.cc     \
           tests/endianess.cc \
           tests/container.cc

TEST_OBJ = $(subst .cc,.o,$(TEST_SRC))

all: test

test: $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) -o test $(TEST_OBJ) test.cc -lgtest
	./test

.PHONY: clean;
clean:
	rm $(TEST_OBJ)
	rm test
