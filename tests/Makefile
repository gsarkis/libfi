#This makefile builds the test files
CC=g++

CPPFLAGS=-Wall -Wextra -pedantic -I../src -I/sw/include
LDLIBS=-L/sw/lib -lboost_unit_test_framework 

TESTS=$(patsubst %.cpp,%, $(wildcard *_test.cpp))
LIBFILES=$(wildcard ../src/*.hpp)

.phony: all
all: $(TESTS)

%_test: %_test.cpp
	$(CC) $(CPPFLAGS) $(<) -o $(@) $(LDLIBS)

$(TESTS): $(LIBFILES)

.phony: runtests
runtests: $(TESTS)
	for a in $(TESTS); do ./$$a || exit 1; done


.phony: clean
clean:
	rm -f *.o $(TESTS)

