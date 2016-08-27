#pragma once

#include "symbol.h"
#include "parser/module.h"
#include "parser/func.h"
#include "runtime/error.h"
#include "runtime/value.h"

typedef struct {
    symbtable_t *symbtable;
} runtime_t;

runtime_t *new_runtime();

runtime_error_t execute(runtime_t *context, module_t *module);
runtime_error_t exec_stmt_list(runtime_t *runtime, stmt_list_t *stmt_list);
runtime_error_t exec_stmt(runtime_t *runtime, stmt_t *stmt);
runtime_error_t exec_assignment(runtime_t *runtime, asign_t* asign);
runtime_error_t exec_funcdef(runtime_t *runtime, func_t* funcdef);

value_t *eval_expr(runtime_t *runtime, expr_t* expr);
value_t *eval_funcall(runtime_t *runtime, funcall_t *funcall);
