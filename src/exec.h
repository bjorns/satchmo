#pragma once

#include "module.h"

/**
 * A runtime generated error
 */
typedef enum {
    OK = 0,
    SCRIPT_ERROR,
    INTERPRETER_ERROR
} runtime_error_t;

typedef struct {

} memspace_t;

runtime_error_t execute(module_t *module, memspace_t *context);