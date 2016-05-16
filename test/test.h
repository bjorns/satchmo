#pragma once
#include <stdbool.h>

#include "str.h"

void assert(const char* msg, bool expr);
void assert_streq(const char* expected, str_t value);

void _macro_assert(const char *file, const int line, const char* msg, bool expr);
#define ASSERT(expr) _macro_assert(__FILE__, __LINE__, #expr, expr)
