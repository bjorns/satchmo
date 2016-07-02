#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "core/log.h"
#include "token.h"

var_t *new_var(str_t token) {
    assert(token.length > 0);
    assert(token.length <= MAX_ID_LEN); // Prevent overflow in mult


    var_t *ret = (var_t*)malloc(sizeof(var_t));
    ret->name = token;

    log("Created variable %s", ret->name.data);
    return ret;
}
