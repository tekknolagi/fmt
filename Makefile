CFLAGS=-Wall -Wextra -Wpedantic

test: tests
	./tests

tests: fmt.h tests.o
	$(CC) $(CFLAGS) tests.o -o tests

format:
	clang-format -i fmt.h tests.c

.PHONY: test format
