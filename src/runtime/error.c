#include "runtime/error.h"


runtime_error_t new_error(error_type_t type, const char *message) {
    runtime_error_t ret;
    ret.type = type;
    ret.message = str(message);
    return ret;
}

runtime_error_t ok() {
    runtime_error_t ret;
    ret.type = OK;
    return ret;
}
