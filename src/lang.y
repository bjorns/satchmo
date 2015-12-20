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
    number_t number;
}

%start  input

%token	<number> T_NUMBER
%token  <op> T_OP

%left T_OP
%type	<expr>	EXPR


%%

input:  /* empty */
	    | EXPR { printf("Result: %d\n", $1); }
		;

EXPR:   T_NUMBER { $$ = $1 }
        | EXPR T_OP EXPR { $$ = compound_expr($2, $1, $3) }
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
