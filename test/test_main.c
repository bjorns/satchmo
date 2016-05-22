#include <stdio.h>
#include "_test.h"

int main() {
    int i = 0;
    #include "_test_exec.c"
    printf("Ran %d tests\n", i);
    printf("OK\n");
}
