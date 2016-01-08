%{
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "token.h"
#include "expr.h"
#include "stmt.h"

extern FILE *yyin;

int yyerror(char *s);
int yylex();

%}

%union {
    op_t op;
    var_t *var;
    lval_t *lval;
    number_t number;

    arglist_t *arglist;
    funcall_t *funcall;
    expr_t *expr;

    asign_t *asign;
    stmt_t *stmt;
}

%start  input

%token	<number> T_NUMBER
%token  <op> T_OP
%token  T_EQ
%token <var> T_VAR
%token T_NEWLINE
%token T_LPAREN
%token T_RPAREN
%token T_COMMA
%token T_COMMENT

%left T_OP

%type <lval>    left_val
%type <expr>	expression
%type <arglist> argument_list
%type <asign>	assignment
%type <funcall> function_call

%%

input:  module
        ;

module: statement_list
        ;

statement_list: /* empty */
        | statement
        | statement statement_list
        | comment statement_list
        ;

statement: expression T_NEWLINE { printf("End statement.\n"); }
        | assignment T_NEWLINE { printf("Assignment statement.\n"); }
        ;

assignment: left_val T_EQ expression { $$ = new_assignment($1, $3); }
        ;

left_val:   T_VAR { $$ = new_lval($1); }
        ;

expression: T_NUMBER { $$ = new_immediate_expr($1) }
        | T_VAR { $$ = new_direct_expr($1) }
        | expression T_OP expression { $$ = compound_expr($2, $1, $3) }
        | function_call              { $$ = new_funcall_expr($1); }
        ;

function_call: T_VAR T_LPAREN argument_list T_RPAREN { $$ = new_funcall($1, $3); }
        ;

argument_list: /* empty */
        | expression { $$ = new_arglist($1); }
        | argument_list T_COMMA expression { $$ = compound_arglist($1, $3); }
        ;

comment: T_COMMENT T_NEWLINE
        ;

%%

extern int yylineno;
extern char *yytext;


int yyerror(char *s) {
    printf("ERROR: %s at symbol \"%s\" on line %d\n", s, yytext, yylineno);
    exit(1);
}

void parse(FILE* file) {
    yyin = file;
    yyparse();
}
