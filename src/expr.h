#ifndef EXPR_H
#define EXPR_H

typedef int number_t;

typedef enum {
    ADD,
    SUB,
    MULT,
    DIV
} op_t;

typedef struct {
    char* name;
} var_t;

struct comp_expr {
    struct expr *left;
    op_t operator;
    struct expr *right;
};
typedef struct comp_expr comp_expr_t;

typedef enum {
    LEAF,
    COMP
} expr_type_t;

typedef struct {
    expr_type_t type;
    void* expr;
} expr_t;

number_t parse_number(const char*);
op_t     parse_operator(const char*);
expr_t  *expr_leaf(number_t value);
expr_t  *compound_expr(op_t op, expr_t *left, expr_t *right);

#endif
