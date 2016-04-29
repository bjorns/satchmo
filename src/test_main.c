#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void str_test();
void hash_test();

void assert(const char* msg, bool expr) {
    if (!expr) {
        printf("error: %s\n", msg);
        exit(-1);
    }
}

void assert_streq(const char* expected, const char* value) {
    int result = strcmp(expected, value);
    if (result != 0) {
        printf("error: Expected %s but was %s\n", expected, value);
        exit(-1);
    }
}

int main() {
    str_test();
    hash_test();
    printf("OK\n");
}
