#include <stdlib.h>

#include "core/log.h"
#include "module.h"

module_t *new_module(const char *name, stmt_list_t *stmt_list) {

    module_t *ret = (module_t*)calloc(1, sizeof(module_t));
    ret->name = name;
    ret->stmt_list = stmt_list;
    log("Created module of size %d", ret->stmt_list->size);
    return ret;
}
