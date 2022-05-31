CFLAGS=-Wall -Wextra -Wpedantic
CXXFLAGS=$(CFLAGS)

test: tests_c tests_cpp
	./tests_c
	./tests_cpp

tests_c: fmt.h tests.c
	$(CC) -std=c99 $(CFLAGS) tests.c -o tests_c

tests_cpp: fmt.h tests.c
	$(CXX) -std=c++98 $(CXXFLAGS) tests.c -o tests_cpp

format:
	clang-format -i fmt.h tests.c

clean:
	rm tests_c tests_cpp

.PHONY: test format clean
