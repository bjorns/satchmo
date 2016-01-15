#include <stdlib.h>

#include "module.h"

module_t *new_module(stmt_list_t *stmt_list) {
    module_t *ret = (module_t*)calloc(1, sizeof(module_t));
    return ret;
}
