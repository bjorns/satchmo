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

    #define lexlog(msg, ...) log("lexer:%d\n  " msg, yylineno, ##__VA_ARGS__)

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
    lexlog("token: Function token (func) at %d", yylineno);
    return T_FUNC;
}



{T_NUMBER}    {
    lexlog("token: Number %s", yytext);
    yylval.number = parse_number(yytext);
    return T_NUMBER;
}

{T_TOKEN}    {
    lexlog("token: id %s", yytext);
    yylval.token = new_str(yytext, yyleng);
    return T_TOKEN;
}

{T_STR}     {
    lexlog("token: string %s", yytext);
    yylval.token = new_str(yytext+1, yyleng-2);
    return T_STR;
}

{T_OP}    {
    lexlog("token: operator %s", yytext);
    yylval.op = parse_operator(yytext);
    return T_OP;
}

{T_EQ}    {
    lexlog("token: assignment (=)");
    return T_EQ;
}

{T_NEWLINE} {
    //lexlog("New line...");
    return T_NEWLINE;
}

{T_COMMENT} {
    lexlog("comment: \"%s\"", yytext);
    return T_COMMENT;
}

{T_LPAREN} {
    lexlog("token: left paren");
    return T_LPAREN;
}

{T_RPAREN} {
    lexlog("token: right paren");
    return T_RPAREN;
}

{T_COMMA} {
    lexlog("token: comma");
    return T_COMMA;
}

{T_BLOCK_START} {
    lexlog("token: block start");
    return T_BLOCK_START;
}

{T_BLOCK_END} {
    lexlog("token: block end");
    return T_BLOCK_END;
}

[ \t]+


%%

int yywrap() {
    (void)input; // Suppress warning of unused function

    lexlog("End of program");
    return 1;
}
