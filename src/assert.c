#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "core/str.h"

void _macro_assert(const char *file, const int line, const char* msg, bool expr) {
    if (!expr) {
        printf("%s:%d error: %s\n", file, line, msg);
        exit(-1);
    }
}

void assert_streq(const char* expected, str_t value) {
    int result = strcmp(expected, value.data);
    if (result != 0) {
        printf("error: Expected %s but was %s\n", expected, value.data);
        exit(-1);
    }
}
