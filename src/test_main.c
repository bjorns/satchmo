#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "str.h"

void str_test();
void hash_test();
void symbol_test();

void _macro_assert(const char *file, const int line, const char* msg, bool expr) {
    if (!expr) {
        printf("%s:%d error: %s\n", file, line, msg);
        exit(-1);
    }
}

void assert(const char* msg, bool expr) {
    _macro_assert("unknown", -1, msg, expr);
}

void assert_streq(const char* expected, str_t value) {
    int result = strcmp(expected, value.data);
    if (result != 0) {
        printf("error: Expected %s but was %s\n", expected, value.data);
        exit(-1);
    }
}

int main() {
    str_test();
    hash_test();
    symbol_test();
    printf("OK\n");
}
