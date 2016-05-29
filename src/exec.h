#pragma once

#include "module.h"
#include "symbol.h"

/**
 * A runtime generated error
 */
typedef enum {
    OK = 0,
    SCRIPT_ERROR,
    INTERPRETER_ERROR
} runtime_error_t;

typedef struct {
    symbtable_t *symbtable;
} runtime_t;

runtime_t *new_runtime();

runtime_error_t execute(runtime_t *context, module_t *module);
