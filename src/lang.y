%{
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>

#include "log.h"
#include "str.h"
#include "token.h"
#include "expr.h"
#include "stmt.h"
#include "module.h"
#include "func.h"

extern FILE *yyin;

int yyerror(char *s);
int yylex();

static module_t *mod;

%}

%union {
    str_t token;
    str_t str;

    op_t op;
    var_t *var;
    lval_t *lval;
    number_t *number;

    arglist_t *arglist;
    funcall_t *funcall;
    expr_t *expr;

    asign_t *asign;
    stmt_t *stmt;
    stmt_list_t *stmt_list;

    func_t *func;
    paramlist_t *paramlist;

    module_t *module;
}

%start  input

%token <number> T_NUMBER
%token <op> T_OP
%token T_EQ
%token <token> T_TOKEN
%token <str> T_STR
%token T_NEWLINE
%token T_LPAREN
%token T_RPAREN
%token T_COMMA
%token T_COMMENT
%token T_BLOCK_START
%token T_BLOCK_END
%token T_FUNC

%left T_OP

%type <var>       variable
%type <lval>      left_val
%type <expr>	  expression
%type <arglist>   argument_list
%type <asign>	  assignment
%type <funcall>   function_call
%type <stmt>      statement
%type <stmt_list> statement_list
%type <stmt_list> block
%type <module>    input

%type <func>      function
%type <paramlist> parameter_list

%%

input:  statement_list { mod = new_module("foobar", $1); }
        ;

statement_list:     { $$ = empty_stmt_list() }
        | statement_list statement { $$ = append_stmt_list($1, $2); }
        | statement_list T_NEWLINE { $$ = $1; }
        | comment statement_list { $$ = $2; }
        ;

statement: expression T_NEWLINE { $$ = new_stmt($1); }
        | assignment T_NEWLINE { $$ = new_asignment_stmt($1); }
        | function T_NEWLINE { $$ = new_func_decl_stmt($1); }
        ;

assignment: left_val T_EQ expression { $$ = new_assignment($1, $3); }
        ;

left_val:   variable { $$ = new_lval($1); }
        ;

expression: T_NUMBER { $$ = new_immediate_num($1); }
        | T_STR      { $$ = new_immediate_str($1); }
        | variable   { $$ = new_direct_expr($1); }
        | expression T_OP expression { $$ = compound_expr($2, $1, $3) }
        | function_call              { $$ = new_funcall_expr($1); }
        ;

function: T_FUNC variable T_LPAREN parameter_list T_RPAREN block { $$ = new_func($2, $4, $6); }
        ;

parameter_list: /* empty */
        | variable { $$ = new_paramlist($1); }
        | parameter_list T_COMMA variable { $$ = append_paramlist($1, $3); }
        ;

block: T_BLOCK_START statement_list T_BLOCK_END { $$ = $2; }
        ;


function_call: variable T_LPAREN argument_list T_RPAREN { $$ = new_funcall($1, $3); }
        ;

argument_list: /* empty */
        | expression { $$ = new_arglist($1); }
        | argument_list T_COMMA expression { $$ = compound_arglist($1, $3); }
        ;

variable: T_TOKEN { $$ = new_var($1); }
        ;

comment: T_COMMENT T_NEWLINE
        ;

%%

extern int yylineno;
extern char *yytext;


int yyerror(char *s) {
    error("%s at symbol \"%s\" on line %d\n", s, yytext, yylineno);
    exit(1);
}

module_t *parse(const char* filename, FILE* file) {
    yyin = file;
    int status = yyparse();
    assert(status == 0);
    return mod;
}
