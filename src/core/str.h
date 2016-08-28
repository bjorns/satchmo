#pragma once

#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    char *data;
    uint16_t length;
} str_t;

/**
 * Create new string
 */
str_t new_str(const char *data, uint16_t len);

/**
 * New string, implicity length
 */
str_t str(const char* value);

/**
 * Copy string, including char buffer
 */
void str_copy(str_t *dst, str_t *src);



/**
 * Returns true if string buffers are equal
 */
bool str_eq(str_t x, str_t y);

/**
 * Returns substring including start but not end character
 */
str_t substr(str_t str, uint16_t start, uint16_t end);
