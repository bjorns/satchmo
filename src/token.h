#pragma once

#include <stdint.h>
#include "core/str.h"

static const int MAX_ID_LEN = 1024;

typedef enum {
    ADD,
    SUB,
    MULT,
    DIV
} op_t;


typedef struct {
    str_t name;
} var_t;


var_t *new_var(str_t token);
