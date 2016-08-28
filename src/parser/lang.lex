%option nounput

%{
    #include "core/str.h"
    #include "core/log.h"
    #include "parser/token.h"
    #include "parser/expr.h"
    #include "stmt.h"
    #include "module.h"
    #include "func.h"

    #include "parser/parser.h"

%}

T_FUNC func
T_OP [+\-]
T_EQ =
T_NEWLINE \n
T_LPAREN \(
T_RPAREN \)
T_COMMA ,
T_COMMENT #[^\n]+
T_BLOCK_START \{
T_BLOCK_END \}
T_NUMBER [0-9]+\.?[0-9]*
T_TOKEN [a-z][a-z0-9_]*
T_STR \"([^\"]|\\\")*\"

%%

{T_FUNC} {
    log("Found func");
    return T_FUNC;
}



{T_NUMBER}    {
    log("number %s at %d", yytext, yylineno);
    yylval.number = parse_number(yytext);
    return T_NUMBER;
}

{T_TOKEN}    {
    log("id %s at %d", yytext, yylineno);
    yylval.token = new_str(yytext, yyleng);
    return T_TOKEN;
}

{T_STR}     {
    log("str %s at %d", yytext, yylineno);
    yylval.token = new_str(yytext+1, yyleng-2);
    return T_STR;
}

{T_OP}    {
    log("Parsed op token %s at %d", yytext, yylineno);
    yylval.op = parse_operator(yytext);
    return T_OP;
}

{T_EQ}    {
    log("Parsed assignment at %d", yylineno);
    return T_EQ;
}

{T_NEWLINE} {
    log("New line...");
    return T_NEWLINE;
}

{T_COMMENT} {
    log("Comment \"%s\" at line %d", yytext, yylineno);
    return T_COMMENT;
}

{T_LPAREN} {
    log("Found left paren");
    return T_LPAREN;
}

{T_RPAREN} {
    log("Found right paren");
    return T_RPAREN;
}

{T_COMMA} {
    log("Found comma");
    return T_COMMA;
}

{T_BLOCK_START} {
    log("Found block start");
    return T_BLOCK_START;
}

{T_BLOCK_END} {
    log("Found block end");
    return T_BLOCK_END;
}

[ \t]+


%%

int yywrap() {
    (void)input; // Suppress warning of unused function

    log("End of program");
    return 1;
}
