#include <assert.h>
#include <stdlib.h>

#include "core/log.h"
#include "parser/expr.h"
#include "parser/func.h"

#include "runtime/value.h"
#include "runtime/exec.h"

runtime_t *new_runtime() {
    runtime_t *ret = (runtime_t*)malloc(sizeof(runtime_t));
    ret->symbtable = new_symbtable();
    return ret;
}

runtime_error_t exec_assignment(runtime_t *runtime, asign_t* asign) {
    error("Assignment not implemented");
    return new_error(INTERPRETER_ERROR);
}

value_t *eval_expr(runtime_t *runtime, expr_t* expr) {
    if (expr->type == IMMEDIATE_NUM) {
        number_t *value = (number_t*)expr->expr;
        log("eval: Immediate value %d", *value);
        return new_value(NUMBER_VALUE, (void*)value);
    } else if (expr->type == IMMEDIATE_STR) {
        last_error = new_error(INTERPRETER_ERROR);
        return NULL;
    } else if (expr->type == DIRECT) {
        last_error = new_error(INTERPRETER_ERROR);
        return NULL;
    } else {
        error("Unexpected expression type %d", expr->type);
        last_error = new_error(INTERPRETER_ERROR);
        return NULL;
    }
}

runtime_error_t exec_funcdef(runtime_t *runtime, func_t* expr) {
    return new_error(INTERPRETER_ERROR);
}

runtime_error_t exec_stmt(runtime_t *runtime, stmt_t *stmt) {
    if (stmt->type == ASIGN) {
        log("Executing assignment statement");
        return exec_assignment(runtime, (asign_t*)stmt->data);
    } else if (stmt->type == EXPR) {
        log("Executing Expression statement");
        value_t *value = eval_expr(runtime, (expr_t*)stmt->data);
        free(value);
        return new_error(OK);
    } else if (stmt->type == FUNC) {
        log("Executing Function statement");
        return exec_funcdef(runtime, (func_t*)stmt->data);
    } else {
        error("Unknown statement type %d", stmt->type);
        return new_error(INTERPRETER_ERROR);
    }
    return new_error(OK);
}

runtime_error_t exec_stmt_list(runtime_t *runtime, stmt_list_t *stmt_list) {
    assert(stmt_list != NULL);
    log("executing statement list");
    for (uint16_t i=0; i < stmt_list->size; ++i) {
        stmt_t stmt = stmt_list->stmt_array[i];
        log("  executing statement");
        runtime_error_t error = exec_stmt(runtime, &stmt);
        if (error.type != OK) {
            return error;
        }
    }
    return new_error(OK);
}

runtime_error_t execute(runtime_t *runtime, module_t *module) {
    runtime_error_t err = exec_stmt_list(runtime, module->stmt_list);
    return err;
}
