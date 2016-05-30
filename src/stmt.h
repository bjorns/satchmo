#ifndef STMT_H
#define STMT_H

#include <stdint.h>
#include "expr.h"

typedef enum {
    ASIGN,
    EXPR
} stmt_type_t;

typedef struct {
    stmt_type_t type;
    void*       data;
} stmt_t;

typedef struct {
    uint16_t capacity;
    uint16_t size;
    stmt_t *stmt_array;
} stmt_list_t;

stmt_t *new_stmt(expr_t *expr);

asign_t *new_assignment(lval_t *lval, expr_t *rval);
stmt_t *new_asignment_stmt(asign_t *asign);

stmt_list_t *new_stmt_list(stmt_t *stmt);
stmt_list_t *append_stmt_list(stmt_list_t *list, stmt_t *stmt);

#endif
