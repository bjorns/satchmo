#include <stdlib.h>

#include "value.h"


value_t *new_value(value_type_t type, void *data) {
    value_t *ret = (value_t*)calloc(1, sizeof(value_t));
    ret->type = type;
    ret->data = data;
    ret->refcount = 0;
    return ret;
}

value_t *new_str_value(str_t *str) {
    value_t *ret = (value_t*)calloc(1, sizeof(value_t));
    ret->type = VALUE_TYPE_STRING;
    str_t *strcopy = (str_t*)calloc(1, sizeof(str_t));
    str_copy(strcopy, str);
    ret->data = (void*)strcopy;
    ret->refcount = 0;
    return ret;
}
