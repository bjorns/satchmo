%{
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "expr.h"


extern FILE *yyin;

int yyerror(char *s);
int yylex();

%}

%union{
    expr_t *expr;

    op_t op;
    var_t id;
    number_t number;
}

%start  input

%token	<number> T_NUMBER
%token  <op> T_OP
%token  T_EQ
%token <id> T_ID
%token T_NEWLINE
%token T_LPAREN
%token T_RPAREN
%token T_COMMA
%token T_COMMENT

%left T_OP
%type <expr>	expression


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
        | assignment T_NEWLINE
        ;

assignment: lval T_EQ expression T_NEWLINE
        ;

lval:   T_ID
        ;

expression:   T_NUMBER { $$ = $1 }
        | expression T_OP expression { $$ = compound_expr($2, $1, $3) }
        | funcall
        ;

funcall: T_ID T_LPAREN arg_list T_RPAREN
        ;

arg_list: /* empty */
        | argument
        | argument T_COMMA arg_list
        ;

argument:   expression

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
