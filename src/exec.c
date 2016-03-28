#include <stdlib.h>

#include "log.h"
#include "expr.h"
#include "exec.h"

runtime_error_t exec_assignment(runtime_t *runtime, asign_t* asign) {
    return OK;
}

runtime_error_t exec_stmt(runtime_t *runtime, stmt_t *stmt) {
    if (stmt->type == ASIGN) {
        log("Executing assignment statement");
        return exec_assignment(runtime, (asign_t*)stmt->data);
    } else if (stmt->type == EXPR) {
        log("Executing Expression statement");
    } else {
        error("Unknown statement type %d", stmt->type);
        return INTERPRETER_ERROR;
    }
    return OK;
}

runtime_error_t exec_stmt_list(runtime_t *runtime, stmt_list_t *stmt_list) {
    for (uint16_t i=0; i < stmt_list->size; ++i) {
        stmt_t stmt = stmt_list->stmt_array[i];
        runtime_error_t error = exec_stmt(runtime, &stmt);
        if (error != OK) {
            return error;
        }
    }
    return OK;
}

runtime_error_t execute(runtime_t *runtime, module_t *module) {
    exec_stmt_list(runtime, module->stmt_list);
    return OK;
}
