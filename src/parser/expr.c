#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>

#include "core/log.h"
#include "expr.h"

lval_t *new_lval(var_t *var) {
    parselog("Creating lval");
    lval_t *ret = (lval_t*)malloc(sizeof(lval_t));
    ret->var = var;
    return ret;
}

number_t *parse_number(const char* str) {
    number_t val = (number_t)atoi(str);
    parselog("Parsed number %d", val);
    number_t *ret = (number_t*)malloc(sizeof(number_t));
    *ret = val;
    return ret;
}

op_t parse_operator(const char* str) {
    if (0 == strcmp("+", str)) {
        return ADD;
    }
    parselog("error: Unknown operator %s", str);
    return ADD;
}

expr_t *compound_expr(op_t op, expr_t *left, expr_t *right) {
    parselog("Parsing compound expression...");
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
    parselog("New funcall %s()", var->name.data);
    funcall_t *ret = (funcall_t*)malloc(sizeof(funcall_t));
    ret->id = var;
    ret->args = args;
    return ret;
}


expr_t  *new_immediate_num(number_t *number) {
    expr_t *ret = (expr_t*)malloc(sizeof(expr_t));
    ret->type = IMMEDIATE_NUM;
    ret->expr = (void*)number;

    ret->debug.data = (char*)calloc(256, sizeof(char));
    sprintf(ret->debug.data, "number<%d()>", *number);
    ret->debug.length = strlen(ret->debug.data);

    parselog("expr: %s", ret->debug.data);
    return ret;
}

expr_t  *new_immediate_str(str_t str) {
    expr_t *ret = (expr_t*)malloc(sizeof(expr_t));
    ret->type = IMMEDIATE_STR;
    ret->expr = (void*)&str;
    ret->debug.data = (char*)calloc(256, sizeof(char));
    sprintf(ret->debug.data, "string<%s>", str.data);
    ret->debug.length = strlen(ret->debug.data);
    parselog("expr: %s", ret->debug.data);
    return ret;
}

expr_t  *new_direct_expr(var_t *var) {
    expr_t *ret = (expr_t*)malloc(sizeof(expr_t));
    ret->type = DIRECT;
    ret->expr = (void*)var;
    ret->debug.data = (char*)calloc(256, sizeof(char));
    sprintf(ret->debug.data, "variable<%s>", var->name.data);
    ret->debug.length = strlen(ret->debug.data);
    parselog("expr: %s", ret->debug.data);
    return ret;

}

expr_t  *new_funcall_expr(funcall_t *funcall) {
    expr_t *ret = (expr_t*)malloc(sizeof(expr_t));
    ret->type = FUNCALL;
    ret->expr = (void*)funcall;

    ret->debug.data = (char*)calloc(256, sizeof(char));
    sprintf(ret->debug.data, "funcall<%s()>", funcall->id->name.data);
    ret->debug.length = strlen(ret->debug.data);
    parselog("expr: %s", ret->debug.data);
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
