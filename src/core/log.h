#pragma once

#include <stdio.h>
#include <stdbool.h>

bool debug;

FILE *_logfile;

void init_log(const char* filename);

#define log(msg, ...) if (debug) fprintf(_logfile, msg "\n", ##__VA_ARGS__)
#define error(msg, ...) fprintf(stderr, "error: " msg "\n", ##__VA_ARGS__)

#define parselog(msg, ...) log("parser: " msg, ##__VA_ARGS__)

#define execlog(msg, ...) log("exec: " msg, ##__VA_ARGS__)
