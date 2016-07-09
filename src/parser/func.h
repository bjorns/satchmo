#pragma once

#include "parser/expr.h"
#include "stmt.h"

typedef struct {
    int capacity;
    int size;
    var_t *args;
} paramlist_t;

typedef struct {
    str_t name;
    paramlist_t *params;
    stmt_list_t *block;
} func_t;

stmt_t *new_funcdef_stmt(func_t *func);

paramlist_t *new_paramlist(var_t *var);
paramlist_t *append_paramlist(paramlist_t *list, var_t *arg);

func_t *new_func(var_t *object, paramlist_t *params, stmt_list_t *block);
