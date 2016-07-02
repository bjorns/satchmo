#pragma once

#include "stmt.h"
#include "core/str.h"


typedef struct {
    const char* name;
    stmt_list_t *stmt_list;
} module_t;

module_t *new_module(const char *name, stmt_list_t *stmt_list);
