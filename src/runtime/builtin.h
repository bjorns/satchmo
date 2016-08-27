#pragma once

#include <stdbool.h>

#include "runtime/exec.h"

bool is_builtin_funcall(funcall_t *funcall);

result_t exec_builtin_funcall(runtime_t *runtime, funcall_t *funcall);

result_t builtin_print(runtime_t *runtime, arglist_t *arglist);
