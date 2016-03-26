#include <stdio.h>
#include <unistd.h>

#include "exec.h"
#include "module.h"

extern FILE *yyin;

module_t *parse(char*, FILE*);

bool debug = true;

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: lang <input>\n");
    }
    char* filename = argv[1];

    FILE* f = fopen(filename, "r");

    module_t *module = parse(filename, f);
    memspace_t memspace;

    runtime_error_t error = execute(module, &memspace);



    fclose(f);
    return error;
}
