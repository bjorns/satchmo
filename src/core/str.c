#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "str.h"

/**
 * Create a new string object.
 */
str_t new_str(const char *data, uint16_t len) {
    str_t ret;
    ret.data = (char*)calloc(len, sizeof(char));
    memcpy(ret.data, data, len * sizeof(char));
    ret.length = len;
    return ret;
}

str_t str(const char *value) {
    return new_str(value, strlen(value));
}

str_t str_copy(str_t str) {
    str_t ret;
    ret.data = strdup(str.data);
    assert(ret.data != NULL);
    ret.length = str.length;
    return ret;
}

bool str_eq(str_t x, str_t y) {
    if (x.length != y.length) {
        return false;
    }
    return 0 == strncmp(x.data, y.data, x.length);
}

/**
 * Returns a subtring of x in the interval [start:end[
 *
 * e.g. substr("foobar", 0, 3) == "foo"
 */
str_t substr(str_t str, uint16_t start, uint16_t end) {
    str_t ret;

    ret.data = str.data + start;
    ret.length = end - start;
    return ret;
}
