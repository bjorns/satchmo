#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "expr.h"

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

expr_t *expr_leaf(number_t value) {
    printf("Parsing immediate value %d\n", value);
    number_t* val = (number_t*)malloc(sizeof(number_t));
    *val = value;

    expr_t *ret = malloc(sizeof(expr_t));
    ret->type = LEAF;
    ret->expr = val;
    return ret;
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

funcall_t *create_funcall(char* name, arg_t *args) {
    funcall_t *ret = (funcall_t*)malloc(sizeof(funcall_t));
    ret->name = name;
    ret->args = args;
    return ret;
}
