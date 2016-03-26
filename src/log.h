#pragma once

#include <stdio.h>
#include <stdbool.h>

bool debug;

#define log(msg, ...) if (debug) fprintf(stderr, msg "\n", ##__VA_ARGS__)
#define error(msg, ...) fprintf(stderr, "error: " msg "\n", ##__VA_ARGS__)
