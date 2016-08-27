#pragma once

#include "symbol.h"
#include "parser/module.h"
#include "parser/func.h"
#include "runtime/error.h"
#include "runtime/value.h"

typedef struct {
    symbtable_t *symbtable;
} runtime_t;

typedef struct {
    value_t *value;
    runtime_error_t error;
} result_t;

runtime_t *new_runtime();

result_t execute(runtime_t *context, module_t *module);
result_t exec_stmt_list(runtime_t *runtime, stmt_list_t *stmt_list);
result_t exec_stmt(runtime_t *runtime, stmt_t *stmt);
result_t exec_assignment(runtime_t *runtime, asign_t* asign);
result_t exec_funcdef(runtime_t *runtime, func_t* funcdef);

result_t eval_expr(runtime_t *runtime, expr_t* expr);
result_t eval_funcall(runtime_t *runtime, funcall_t *funcall);

result_t new_result(runtime_error_t error, value_t *value);
