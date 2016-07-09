#pragma once

#include "symbol.h"
#include "parser/module.h"
#include "runtime/error.h"

typedef struct {
    symbtable_t *symbtable;
} runtime_t;

runtime_t *new_runtime();

runtime_error_t execute(runtime_t *context, module_t *module);
