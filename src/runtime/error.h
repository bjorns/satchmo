#pragma once

#include "core/str.h"
/**
 * A runtime generated error
 */
typedef enum {
    OK = 0,
    SCRIPT_ERROR,
    INTERPRETER_ERROR
} error_type_t;

typedef struct {
    // Undefined
} stack_trace_t;

typedef struct {
    error_type_t type;
    stack_trace_t stack_trace;
    str_t message;
} runtime_error_t;

extern runtime_error_t last_error;

runtime_error_t new_error(error_type_t);
