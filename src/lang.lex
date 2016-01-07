%{
    #include "expr.h"
    #include "parser.h"
%}

T_NUMBER [0-9]+\.?[0-9]*
T_ID [a-z][a-z0-9_]*
T_OP [+\-]
T_EQ \=
T_NEWLINE \n
T_LPAREN (
T_RPAREN )
T_COMMA ,
T_COMMENT #[^\n]+

%%


{T_NUMBER}    {
    printf("Parsed number %s at %d\n", yytext, yylineno);
    yylval.number = parse_number(yytext);
    return T_NUMBER;
}

{T_ID}    {
    printf("Parsed token %s at %d\n", yytext, yylineno);
    //$$ = yytext;
}

{T_OP}    {
    printf("Parsed op token %s at %d\n", yytext, yylineno);
    yylval.op = parse_operator(yytext);
    return T_OP;
}

{T_NEWLINE}  {
    printf("New line...\n");
    return T_NEWLINE;
}

{T_COMMENT} {
    printf("Comment \"%s\" at line %d\n", yytext, yylineno);
    return T_COMMENT;
}

[ \t]+
%%

int yywrap() {
    printf("End of program\n");
    return 1;
}
