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

#if defined(__STRICT_ANSI__) && __STDC_VERSION__ + 0 <= 199900L &&             \
    __cplusplus + 0 <= 201103L
#define va_copy(d, s) __builtin_va_copy(d, s)
#endif

// Returns NULL str if allocation or formatting fails.
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
  result.str = (char *)malloc(size + 1);
  if (result.str == NULL) {
    return result;
  }
  vsnprintf(result.str, size + 1, fmt, args_copy);
  va_end(args_copy);
  return result;
}

// Returns NULL str if allocation or formatting fails.
__attribute__((format(printf, 1, 2))) static str_size format(const char *fmt,
                                                             ...) {
  va_list args;
  va_start(args, fmt);
  str_size result = formatv(fmt, args);
  va_end(args);
  return result;
}

static void str_size_free(str_size str) { free(str.str); }
