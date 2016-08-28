#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "str.h"

/**
 * Create new string object
 */
str_t str(const char *value) {
    return new_str(value, strlen(value));
}

/**
 * Create a new string object.
 */
str_t new_str(const char *data, size_t len) {
    str_t ret;
    ret.data = (char*)calloc(len + 1, sizeof(char));
    strlcpy(ret.data, data, len + 1);
    ret.length = len;
    return ret;
}

/**
 * TODO: return result_t
 */
void str_copy(str_t *dst, str_t *src) {
    if (src->length <= 0) {
        return;
    }
    dst->data = (char*)calloc(src->length + 1, sizeof(char));
    strlcpy(dst->data, src->data, src->length + 1);
    assert(dst->data != NULL);
    dst->length = src->length;
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

void validate_str(str_t *str) {
    assert(str->length >= 0);
    assert(str->data != NULL);
}
