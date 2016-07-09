#include "runtime/error.h"

runtime_error_t last_error;

runtime_error_t new_error(error_type_t type) {
    runtime_error_t ret;
    ret.type = type;
    ret.message = str("Unknown error");
    
}
