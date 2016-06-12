#pragma once

#include <stdio.h>
#include <stdbool.h>

bool debug;

FILE *_logfile;

void init_log(const char* filename);

#define log(msg, ...) if (debug) fprintf(_logfile, msg "\n", ##__VA_ARGS__)
#define error(msg, ...) fprintf(_logfile, "error: " msg "\n", ##__VA_ARGS__)
