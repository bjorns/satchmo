%{
    #include "token.h"
    #include "expr.h"
    #include "stmt.h"
    #include "parser.h"
%}

T_NUMBER [0-9]+\.?[0-9]*
T_VAR [a-z][a-z0-9_]*
T_OP [+\-]
T_EQ =
T_NEWLINE \n
T_LPAREN \(
T_RPAREN \)
T_COMMA ,
T_COMMENT #[^\n]+

%%


{T_NUMBER}    {
    printf("Parsed number %s at %d\n", yytext, yylineno);
    yylval.number = parse_number(yytext);
    return T_NUMBER;
}

{T_VAR}    {
    printf("Parsed id %s at %d\n", yytext, yylineno);
    yylval.var = new_var(yytext, yyleng);
    return T_VAR;
}

{T_OP}    {
    printf("Parsed op token %s at %d\n", yytext, yylineno);
    yylval.op = parse_operator(yytext);
    return T_OP;
}

{T_EQ}    {
    printf("Parsed assignment at %d\n", yylineno);
    return T_EQ;
}

{T_NEWLINE}  {
    printf("New line...\n");
    return T_NEWLINE;
}

{T_COMMENT} {
    printf("Comment \"%s\" at line %d\n", yytext, yylineno);
    return T_COMMENT;
}

{T_LPAREN} {
    printf("Found left paren\n");
    return T_LPAREN;
}

{T_RPAREN} {
    printf("Found right paren\n");
    return T_RPAREN;
}

{T_COMMA} {
    printf("Found comma\n");
    return T_COMMA;
}

[ \t]+


%%

int yywrap() {
    printf("End of program\n");
    return 1;
}
