#include <stdlib.h>

#include "value.h"


value_t *new_value(value_type_t type, void *data) {
    value_t *ret = (value_t*)calloc(1, sizeof(value_t));
    ret->type = type;
    ret->data = data;
    ret->refcount = 0;
    return ret;
}
