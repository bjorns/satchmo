#include "runtime/builtin.h"
#include "runtime/exec.h"

static const char *FUNC_PRINT = "print";

bool is_builtin_funcall(funcall_t *funcall) {
    if (str_eq(str(FUNC_PRINT), funcall->id->name)) {
        return true;
    } else {
        return false;
    }

}

result_t exec_builtin_funcall(runtime_t *runtime, funcall_t *funcall) {
    if (str_eq(str(FUNC_PRINT), funcall->id->name)) {
        return builtin_print(runtime, funcall->args);
    }

    return new_result(ok(), NULL);
}

result_t builtin_print(runtime_t *runtime, arglist_t *arglist) {
    if (arglist->size < 1) {
        return new_result(new_error(SCRIPT_ERROR, "Missing argument for print"), NULL);
    }

    expr_t arg = arglist->args[0];
    result_t result = eval_expr(runtime, &arg);

    if (result.error.type != OK) {
        return result;
    }

    value_t *value = result.value;
    if (value->type != VALUE_TYPE_STRING) {
        return new_result(new_error(SCRIPT_ERROR, "Expected string value for print"), NULL);
    }

    return new_result(ok(), NULL);
}
