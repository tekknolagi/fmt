test: tests
	./tests

tests: fmt.h tests.c
	gcc tests.c -o tests

format:
	clang-format -i fmt.h tests.c

.PHONY: test format
