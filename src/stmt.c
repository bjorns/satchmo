#include <stdlib.h>

#include "expr.h"
#include "stmt.h"


/**
 */
stmt_t *new_asign_stmt(asign_t *asign) {
    stmt_t *ret = (stmt_t*)malloc(sizeof(stmt_t));
    ret->type = ASIGN;
    ret->stmt = (void*)asign;
    return ret;
}

asign_t *new_assignment(lval_t *lval, expr_t *rval) {
    asign_t *ret = (asign_t*)malloc(sizeof(asign_t));
    ret->lval = lval;
    ret->rval = rval;
    return ret;
}
