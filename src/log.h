#pragma once

#include <stdio.h>

#define log(msg, ...) fprintf(stderr, msg "\n", ##__VA_ARGS__)
#define error(msg, ...) fprintf(stderr, "error: " msg "\n", ##__VA_ARGS__)
