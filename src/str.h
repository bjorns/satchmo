#pragma once
#include <stdbool.h>

typedef struct {
    char *data;
    uint16_t length;
} str_t;

str_t new_str(char *data, uint16_t len);
bool str_eq(str_t x, str_t y);

str_t substr(str_t str, uint16_t start, uint16_t end);
