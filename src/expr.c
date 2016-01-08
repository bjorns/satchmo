#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>

#include "expr.h"

lval_t *new_lval(var_t *var) {
    printf("Creating lval\n");
    lval_t *ret = (lval_t*)malloc(sizeof(lval_t));
    ret->var = var;
    return ret;
}

number_t parse_number(const char* str) {
    return (number_t)atoi(str);
}

op_t parse_operator(const char* str) {
    if (0 == strcmp("+", str)) {
        return ADD;
    }
    printf("error: Unknown operator %s\n", str);
    return ADD;
}

expr_t *compound_expr(op_t op, expr_t *left, expr_t *right) {
    printf("Parsing compound expression...\n");
    comp_expr_t *expr = (comp_expr_t*)malloc(sizeof(comp_expr_t));
    expr->operator = op;
    expr->left = (struct expr *)left;
    expr->right = (struct expr *)right;

    expr_t *ret = (expr_t*)malloc(sizeof(expr_t));
    ret->type = COMP;
    ret->expr = expr;

    return ret;
}

funcall_t *new_funcall(var_t* var, arglist_t *args) {
    printf("New funcall %s()\n", var->name);
    funcall_t *ret = (funcall_t*)malloc(sizeof(funcall_t));
    ret->id = var;
    ret->args = args;
    return ret;
}


expr_t  *new_immediate_expr(number_t number) {
    expr_t *ret = (expr_t*)malloc(sizeof(expr_t));
    ret->type = IMMEDIATE;
    ret->expr = (void*)&number;
    return ret;
}

expr_t  *new_direct_expr(var_t *var) {
    expr_t *ret = (expr_t*)malloc(sizeof(expr_t));
    ret->type = DIRECT;
    ret->expr = (void*)&var;
    return ret;

}

expr_t  *new_funcall_expr(funcall_t *funcall) {
    expr_t *ret = (expr_t*)malloc(sizeof(expr_t));
    ret->type = FUNCALL;
    ret->expr = (void*)funcall;
    return ret;
}

static const int INIT_CAPACITY = 10;

arglist_t *new_arglist(expr_t *arg) {
    arglist_t *ret = (arglist_t*)calloc(1, sizeof(arglist_t));
    ret->capacity = INIT_CAPACITY;
    ret->args = (expr_t*)calloc(ret->capacity, sizeof(expr_t));
    ret->size = 0;
    return compound_arglist(ret, arg); // Add arg as first item.
}

arglist_t* compound_arglist(arglist_t *arglist, expr_t *arg) {
    assert(arglist->size < arglist->capacity);
    arglist->args[arglist->size] = *arg;
    arglist->size++;
    return arglist;
}
