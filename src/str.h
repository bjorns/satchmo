#pragma once

#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    char *data;
    uint16_t length;
} str_t;

str_t new_str(const char *data, uint16_t len);
str_t copy_str(str_t str);

bool str_eq(str_t x, str_t y);

str_t substr(str_t str, uint16_t start, uint16_t end);

str_t str(const char* value);
