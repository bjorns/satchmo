#include <stdio.h>
#include <unistd.h>

#include "lexer.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: lang <input>\n");
    }
    char* filename = argv[1];

    FILE* f = fopen(filename, "r");

    parse(f);

    fclose(f);
    return 0;
}
