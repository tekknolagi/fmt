#include "fmt.h"

#include <stdbool.h>
#include <string.h>

#define ASSERT(cond) assertTrue(cond, #cond)

#define TEST(expected, fmt, ...)                                               \
  do {                                                                         \
    str_size result = format(fmt, __VA_ARGS__);                                \
    ASSERT(result.length == strlen(expected));                                 \
    ASSERT(result.str != NULL);                                                \
    ASSERT(strncmp(expected, result.str, strlen(expected)) == 0);              \
    str_size_free(result);                                                     \
  } while (0)

void assertTrue(bool cond, const char *cond_str) {
  if (!cond) {
    fprintf(stderr, "Assertion failure: %s is not true!\n", cond_str);
    abort();
  }
}

int main() {
  do {
    str_size result = format("hello");
    ASSERT(result.length == 5);
    ASSERT(result.str != NULL);
    ASSERT(strncmp("hello", result.str, 5) == 0);
    str_size_free(result);
  } while (0);

  TEST("hello 42", "hello %d", 42);
  TEST("x hello 42", "%s hello %d", "x", 42);
}
