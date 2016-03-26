#ifndef EXPR_H
#define EXPR_H

#include <stdint.h>
#include "token.h"

typedef int number_t;

typedef struct {
    var_t *var;
} lval_t;

struct comp_expr {
    struct expr *left;
    op_t operator;
    struct expr *right;
};
typedef struct comp_expr comp_expr_t;

typedef enum {
    IMMEDIATE_NUM, // constant
    IMMEDIATE_STR,
    DIRECT,    // variable
    FUNCALL,   // function call
    COMP       // compound
} expr_type_t;

typedef struct {
    expr_type_t type;
    void* expr;
} expr_t;

typedef struct {
    int capacity;
    int size;
    expr_t *args;
} arglist_t;

typedef struct {
    var_t *id;
    arglist_t *args;
} funcall_t;

typedef struct {
    lval_t  *lval;
    expr_t *rval;
} asign_t;

lval_t *new_lval(var_t *var);

number_t parse_number(const char*);
op_t     parse_operator(const char*);

arglist_t* new_arglist(expr_t* arg);
arglist_t* compound_arglist(arglist_t *arglist, expr_t *arg);
funcall_t *new_funcall(var_t* var, arglist_t *args);

expr_t  *new_immediate_num(number_t number);
expr_t  *new_immediate_str(str_t str);
expr_t  *new_direct_expr(var_t *var);
expr_t  *compound_expr(op_t op, expr_t *left, expr_t *right);
expr_t  *new_funcall_expr(funcall_t *funcall);

#endif
