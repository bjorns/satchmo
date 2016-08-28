#pragma once

#include "core/str.h"
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
value_t *new_str_value(str_t *str);
