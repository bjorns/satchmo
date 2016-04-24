#include <stdio.h>
#include <unistd.h>

#include "exec.h"
#include "module.h"
#include "log.h"

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


    runtime_t runtime;
    log("Executing module %s", module->name);
    runtime_error_t error = execute(&runtime, module);

    fclose(f);
    return error;
}
