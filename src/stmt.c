#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "log.h"
#include "expr.h"
#include "stmt.h"

static const uint16_t INIT_SIZE = 32;

stmt_t *new_stmt(expr_t *expr) {
    stmt_t *ret = (stmt_t*)calloc(1, sizeof(stmt_t));
    ret->type = EXPR;
    ret->data = (void*)expr;
    log("Expression statement created");
    return ret;
}

/**
 */
stmt_t *new_asignment_stmt(asign_t *asign) {
    stmt_t *ret = (stmt_t*)malloc(sizeof(stmt_t));
    ret->type = ASIGN;
    ret->data = (void*)asign;
    log("Assignment statement created");
    return ret;
}

asign_t *new_assignment(lval_t *lval, expr_t *rval) {
    asign_t *ret = (asign_t*)malloc(sizeof(asign_t));
    ret->lval = lval;
    ret->rval = rval;
    return ret;
}

stmt_list_t *new_stmt_list(stmt_t *stmt) {
    log("Creating statement list");
    stmt_t *data = (stmt_t*)calloc(INIT_SIZE, sizeof(stmt_t));
    stmt_list_t *ret = (stmt_list_t*)calloc(1, sizeof(stmt_list_t));
    ret->capacity = INIT_SIZE;
    ret->size = 0;
    ret->stmt_array = data;
    return append_stmt_list(ret, stmt);
}

void _double_capacity(stmt_list_t* list) {
    int new_capacity = 2*list->capacity;
    assert(new_capacity > list->capacity); // protect overflow
    stmt_t *data = (stmt_t*)calloc(new_capacity, sizeof(stmt_t));
    int num_bytes = sizeof(stmt_t)*list->size;
    assert(num_bytes > list->size);
    memcpy(data, list->stmt_array, num_bytes);
    free(list->stmt_array);
    list->stmt_array = data;
    list->capacity = new_capacity;
}

stmt_list_t *append_stmt_list(stmt_list_t *list, stmt_t *stmt) {
    const uint16_t size = list->size;
    if (size >= list->capacity) {
        _double_capacity(list);
    }
    list->stmt_array[size] = *stmt;
    ++(list->size);
    log("Adding statement to list of size %d", list->size);
    return list;
}
