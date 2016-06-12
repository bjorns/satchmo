#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "log.h"

FILE *_logfile = NULL;

static const char* APPEND_MODE = "a";

void init_log(const char* filename) {
    _logfile = fopen(filename, APPEND_MODE);
}
