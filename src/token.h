#pragma once

#include <stdint.h>

static const int MAX_ID_LEN = 1024;

typedef enum {
    ADD,
    SUB,
    MULT,
    DIV
} op_t;


typedef struct {
    char* name;
} var_t;


var_t *new_var(const char* name, int32_t len);
