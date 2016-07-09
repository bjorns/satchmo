#include <stdio.h>
#include <unistd.h>

#include "core/log.h"
#include "parser/module.h"
#include "runtime/exec.h"

extern FILE *yyin;

module_t *parse(char*, FILE*);

bool debug = true;

int main(int argc, char** argv) {
    init_log("satchmo.log");

    if (argc < 2) {
        printf("Usage: lang <input>\n");
    }
    char* filename = argv[1];

    FILE* f = fopen(filename, "r");

    module_t *module = parse(filename, f);


    runtime_t *runtime = new_runtime();
    log("Executing module %s", module->name);
    runtime_error_t error = execute(runtime, module);

    if (error.type != OK) {
        error("Failed to execute %s", filename);
    }

    fclose(f);

    return error.type;
}
