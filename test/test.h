#pragma once
#include <assert.h>
#include <stdbool.h>

#include "core/str.h"

void assert_streq(const char* expected, str_t value);

void _macro_assert(const char *file, const int line, const char* msg, bool expr);
#define ASSERT(expr) _macro_assert(__FILE__, __LINE__, #expr, expr)
