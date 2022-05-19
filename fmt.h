#pragma once

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// NUL-terminated string and length. Length does not include NUL.
typedef struct str_size {
  char *str;
  size_t length;
} str_size;

static str_size formatv(const char *fmt, va_list args) {
  va_list args_copy;
  va_copy(args_copy, args);
  str_size result = (str_size){.str = NULL, .length = 0};
  int size = vsnprintf(result.str, /*size=*/0, fmt, args);
  if (size < 0) {
    return result;
  }
  result.length = (size_t)size;
  // +1 to include NUL
  result.str = malloc(size + 1);
  vsnprintf(result.str, size + 1, fmt, args_copy);
  va_end(args_copy);
  return result;
}

__attribute__((format(printf, 1, 2))) static str_size format(const char *fmt,
                                                             ...) {
  va_list args;
  va_start(args, fmt);
  str_size result = formatv(fmt, args);
  va_end(args);
  return result;
}

static void str_size_free(str_size str) { free(str.str); }
