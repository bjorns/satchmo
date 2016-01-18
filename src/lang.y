%{
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "str.h"
#include "token.h"
#include "expr.h"
#include "stmt.h"
#include "module.h"

extern FILE *yyin;

int yyerror(char *s);
int yylex();

%}

%union {
    str_t token;

    op_t op;
    var_t *var;
    lval_t *lval;
    number_t number;

    arglist_t *arglist;
    funcall_t *funcall;
    expr_t *expr;

    asign_t *asign;
    stmt_t *stmt;
    stmt_list_t *stmt_list;
    module_t *module;
}

%start  input

%token <number> T_NUMBER
%token <op> T_OP
%token T_EQ
%token <token> T_TOKEN
%token T_NEWLINE
%token T_LPAREN
%token T_RPAREN
%token T_COMMA
%token T_COMMENT

%left T_OP

%type <var>       variable
%type <lval>      left_val
%type <expr>	  expression
%type <arglist>   argument_list
%type <asign>	  assignment
%type <funcall>   function_call
%type <stmt>      statement
%type <stmt_list> statement_list
%type <module>    input

%%

input:  statement_list { $$ = new_module($1); }
        ;

statement_list: /* empty */
        | statement { $$ = new_statement_list($1); }
        | statement_list statement { $$ = append_stmt_list($1, $2); }
        | comment statement_list { $$ = $2; }
        ;

statement: expression T_NEWLINE { $$ = new_statement($1); }
        | assignment T_NEWLINE { $$ = new_asignment_stmt($1); }
        ;

assignment: left_val T_EQ expression { $$ = new_assignment($1, $3); }
        ;

left_val:   variable { $$ = new_lval($1); }
        ;

expression: T_NUMBER { $$ = new_immediate_expr($1); }
        | variable { $$ = new_direct_expr($1); }
        | expression T_OP expression { $$ = compound_expr($2, $1, $3) }
        | function_call              { $$ = new_funcall_expr($1); }
        ;

function_call: variable T_LPAREN argument_list T_RPAREN { $$ = new_funcall($1, $3); }
        ;

argument_list: /* empty */
        | expression { $$ = new_arglist($1); }
        | argument_list T_COMMA expression { $$ = compound_arglist($1, $3); }
        ;

variable: T_TOKEN { $$ = new_var($1); }

comment: T_COMMENT T_NEWLINE
        ;

%%

extern int yylineno;
extern char *yytext;


int yyerror(char *s) {
    printf("ERROR: %s at symbol \"%s\" on line %d\n", s, yytext, yylineno);
    exit(1);
}

module_t *parse(const char* filename, FILE* file) {
    yyin = file;
    yyparse();
    module_t *ret = yylval.module;
    return ret;
}
