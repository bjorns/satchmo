%{
    #include "expr.h"
    #include "parser.h"
%}

T_NUMBER [0-9]+\.?[0-9]*
T_ID [a-z][a-z0-9_]*
T_OP [+\-]
T_NEWLINE \n
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
}

[ \t]+
%%

int yywrap() {
    printf("Wrapping!\n");
}
