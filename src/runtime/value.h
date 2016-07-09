#pragma once

#include "runtime/gc.h"

typedef enum {
    STRING_VALUE,
    NUMBER_VALUE
} value_type_t;

typedef struct {
    value_type_t type;
    void *data;
    refcount_t refcount;
} value_t;

value_t *new_value(value_type_t type, void *data);
