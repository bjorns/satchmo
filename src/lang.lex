NUMBER [0-9]+.?[0-9]*
ID [a-z][a-z0-9_]*
OP [+\-]

%%


{NUMBER}    {
    printf("Parsed number %s at %d\n", yytext, yylineno);
}

{ID}    {
    printf("Parsed token %s at %d\n", yytext, yylineno);
}

{OP}    {
    printf("Parsed op token %s at %d\n", yytext, yylineno);
}

\n  {
    printf("New line...\n");
}


%%

int yywrap() {
    printf("Wrapping!\n");
}

void parse(FILE* file) {
    yy_create_buffer(file, YY_BUF_SIZE);
    yyin = file;
    yylex();
}
