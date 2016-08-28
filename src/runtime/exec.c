#include <assert.h>
#include <stdlib.h>

#include "core/log.h"
#include "parser/expr.h"

#include "runtime/value.h"
#include "runtime/builtin.h"
#include "runtime/exec.h"

runtime_t *new_runtime() {
    runtime_t *ret = (runtime_t*)malloc(sizeof(runtime_t));
    ret->symbtable = new_symbtable();
    return ret;
}

result_t execute(runtime_t *runtime, module_t *module) {
    result_t ret = exec_stmt_list(runtime, module->stmt_list);
    return ret;
}

result_t new_result(runtime_error_t error, value_t *value) {
    result_t ret;
    ret.error = error;
    ret.value = value;
    return ret;
}

result_t exec_stmt_list(runtime_t *runtime, stmt_list_t *stmt_list) {
    assert(stmt_list != NULL);
    log("executing statement list");

    result_t result;
    for (uint16_t i=0; i < stmt_list->size; ++i) {
        stmt_t stmt = stmt_list->stmt_array[i];
        log("  executing statement");
        result = exec_stmt(runtime, &stmt);
        if (result.error.type != OK) {
            return result;
        }
    }
    return new_result(ok(), result.value);
}

result_t exec_stmt(runtime_t *runtime, stmt_t *stmt) {
    if (stmt->type == ASIGN) {
        log("Executing assignment statement");
        return exec_assignment(runtime, (asign_t*)stmt->data);
    } else if (stmt->type == EXPR) {
        log("Executing Expression statement");
        result_t result = eval_expr(runtime, (expr_t*)stmt->data);
        free(result.value);
        return result;
    } else if (stmt->type == FUNC) {
        log("Executing Function definition statement");
        return exec_funcdef(runtime, (func_t*)stmt->data);
    } else {
        error("Unknown statement type %d", stmt->type);
        return new_result(new_error(INTERPRETER_ERROR, "Unknown statement type"), NULL);
    }
}

result_t exec_assignment(runtime_t *runtime, asign_t* asign) {
    error("Assignment not implemented");
    return new_result(new_error(INTERPRETER_ERROR, "Assignment not implemented"), NULL);
}

result_t exec_funcdef(runtime_t *runtime, func_t* funcdef) {
    // TODO: Test for predefined
    symbol_t *func_symb = new_symbol(funcdef->name, SYMB_FUNCTION, funcdef);
    put_symbol(runtime->symbtable, func_symb);
    return new_result(ok(), NULL);
}

/**
 * Translate from parser types to runtime types in the given runtime.
 */
result_t eval_expr(runtime_t *runtime, expr_t* expr) {
    if (expr->type == IMMEDIATE_NUM) {
        number_t *value = (number_t*)expr->expr;
        log("eval: Immediate value %d", *value);
        return new_result(ok(), new_value(VALUE_TYPE_NUMBER, (void*)value));
    } else if (expr->type == IMMEDIATE_STR) {
        str_t *str = expr->expr;
        validate_str(str);
        value_t *value = new_str_value(str);
        return new_result(ok(), value);
    } else if (expr->type == DIRECT) {
        var_t *var = (var_t*)expr->expr;
        str_t name = var->name;
        symbol_t *symbol = get_symbol(runtime->symbtable, name);
        if (symbol == NULL) {
            error("Could not locate symbol %s", name.data);
            runtime_error_t err = new_error(INTERPRETER_ERROR, "Could not find symbol");
            return new_result(err, NULL);
        }
        assert(str_eq(name, symbol->name));
        return eval_symbol(runtime, symbol);
    } else if (expr->type == FUNCALL) {
        funcall_t *funcall = expr->expr;
        result_t result = eval_funcall(runtime, funcall);
        return result;
    } else {
        error("Unexpected expression type %d", expr->type);
        runtime_error_t err = new_error(INTERPRETER_ERROR, "Unexpected expression type");
        return new_result(err, NULL);
    }
}

result_t eval_symbol(runtime_t *runtime, symbol_t *symbol) {
    if (symbol->type == SYMB_FUNCTION) {
        // Not implemented
        return new_result(new_error(INTERPRETER_ERROR, "Not implemented"), NULL);
    } else if (symbol->type == SYMB_OBJECT) {

        value_t *value = symbol->object;
        return new_result(ok(), value);
    } else {
        return new_result(new_error(INTERPRETER_ERROR, "Unknown error"), NULL);
    }
}

result_t eval_funcall(runtime_t *runtime, funcall_t *funcall) {
    symbtable_t *table = runtime->symbtable;

    if (is_builtin_funcall(funcall)) {
        return exec_builtin_funcall(runtime, funcall);
    }

    symbol_t *func_symb = get_symbol(table, funcall->id->name);
    if (func_symb == NULL) {
        return new_result(new_error(INTERPRETER_ERROR, "Failed to locate function"), NULL);
    }
    assert(func_symb->type == SYMB_FUNCTION);
    func_t *funcdef = (func_t*)func_symb->object;

    arglist_t *arglist = funcall->args;
    assert(arglist->size >= 0);
    assert(arglist->capacity >= arglist->size);

    push_frame(table);
    for (int i=0; i < arglist->size; ++i) {
        expr_t arg_expr = arglist->args[i];
        result_t result = eval_expr(runtime, &arg_expr);

        var_t param = funcdef->params->args[i];
        symbol_t *param_symbol = new_symbol(param.name, SYMB_OBJECT, result.value);

        put_symbol(table, param_symbol);
    }

    stmt_list_t *block = funcdef->block;
    result_t result = exec_stmt_list(runtime, block);

    pop_frame(table);

    return result;
}
