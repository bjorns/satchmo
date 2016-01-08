#ifndef STMT_H
#define STMT_H


typedef enum {
    ASIGN,
    EXPR
} stmt_type_t;

typedef struct {
    stmt_type_t type;
    void*       stmt;
} stmt_t;

asign_t *new_assignment(lval_t *lval, expr_t *rval);

#endif
