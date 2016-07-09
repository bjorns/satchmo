#include <assert.h>

#include "core/log.h"
#include "func.h"

static int INIT_CAPACITY = 16;

stmt_t *new_funcdef_stmt(func_t *func) {
    stmt_t *ret = (stmt_t*)malloc(sizeof(stmt_t));
    ret->type = FUNC;
    ret->data = (void*)func;
    log("Function declaration statement created");
    return ret;
}

paramlist_t *new_paramlist(var_t *var) {
    paramlist_t *ret = (paramlist_t*)calloc(1, sizeof(paramlist_t));
    ret->capacity = INIT_CAPACITY;
    ret->args = (var_t*)calloc(ret->capacity, sizeof(var_t));
    ret->size = 0;
    return append_paramlist(ret, var); // Add arg as first item.
}

paramlist_t *append_paramlist(paramlist_t *list, var_t *arg) {
    assert(list->size < list->capacity);
    list->args[list->size] = *arg;
    list->size++;
    return list;
}

func_t *new_func(var_t *object, paramlist_t *params, stmt_list_t *block) {
    func_t *ret = (func_t*)calloc(1, sizeof(func_t));
    ret->name = object->name;
    ret->params = params;
    ret->block = block;
    return ret;
}
