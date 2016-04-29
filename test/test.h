#pragma once
#include <stdbool.h>

void assert(const char* msg, bool expr);
void assert_streq(const char* expected, const char* value);
