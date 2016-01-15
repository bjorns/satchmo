#pragma once

#include "stmt.h"

typedef struct {
    void *data;
} module_t;

module_t *new_module(stmt_list_t *stmt_list);
