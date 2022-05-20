# [fmt](https://github.com/tekknolagi/fmt)

This very small formatting library provides two functions and a data type for
when you need to heap-allocate and format a string at once. You could try and
remember exactly how to do that dance, or you could include `fmt.h` and go on
your way.

```c
// NUL-terminated string and length. Length does not include NUL.
typedef struct str_size {
  char *str;
  size_t length;
} str_size;

str_size format(const char *fmt, ...);
str_size formatv(const char *fmt, va_list args);
void str_size_free(str_size str);  // or you can free(str.str)
```

Happy hacking.
