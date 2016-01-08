#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "token.h"

var_t *new_var(const char* token, int32_t len) {
    assert(len > 0);
    assert(len <= MAX_ID_LEN); // Prevent overflow in mult
    char *name = (char*)calloc(len + 1, sizeof(char));

    var_t *ret = (var_t*)malloc(sizeof(var_t));
    ret->name = name;
    strlcpy(name, token, len+1);
    printf("Created variable %s\n", ret->name);
    return ret;
}
