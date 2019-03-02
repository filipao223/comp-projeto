%{
    //If argument -1 is received, set as 1
    int print_tokens;
    int total_lines = 1;
    int total_columns = 1;
    int error_line_number;
    int error_column_number;
    int comment = 0;  
%}

ID                                      ([A-Z]*|[a-z]*)+
RESERVED                                (break|default|func|interface|select|case|defer|go|map|struct|chan|else|goto|package|switch|const|fallthrough|if|range|type|continue|for|import|return|var|"++"|"--")
OCTAL                                   (0)[0-7]+
HEXA                                    (0x|0X)([0-9]*|[a-f|A-F]*)+
INT                                     ([0]|[1-9]+)
REALLIT                                 ([1-9]*"."?[0-9]*((e|E)("-"|"+")?[0-9]+)?)
STRLIT                                  \".*\"         

%X COMMENT

%%

" "                                     total_columns += strlen(yytext);
"\n"                                    ++total_lines; total_columns=1;
"/*"                                    { error_line_number = total_lines; error_column_number = total_columns;comment = 1;BEGIN COMMENT;};
<COMMENT>"\n"                           ++total_lines; total_columns=1;
<COMMENT>[^[*|/]]*                      total_columns += strlen(yytext);
<COMMENT>"*/"                           { total_columns += strlen(yytext); comment = 0; BEGIN 0;};
";"                                     { total_columns += strlen(yytext); if (print_tokens==1) printf("SEMICOLON\n");};
"_"                                     { total_columns += strlen(yytext); if (print_tokens==1) printf("BLANKID\n");};
"package"                               { total_columns += strlen(yytext); if (print_tokens==1) printf("PACKAGE\n");};
"return"                                { total_columns += strlen(yytext); if (print_tokens==1) printf("RETURN\n");};
"&&"                                    { total_columns += strlen(yytext); if (print_tokens==1) printf("AND\n");};
"="                                     { total_columns += strlen(yytext); if (print_tokens==1) printf("ASSIGN\n");};
"*"                                     { total_columns += strlen(yytext); if (print_tokens==1) printf("STAR\n");};
","                                     { total_columns += strlen(yytext); if (print_tokens==1) printf("COMMA\n");};
"/"                                     { total_columns += strlen(yytext); if (print_tokens==1) printf("DIV\n");};
"=="                                    { total_columns += strlen(yytext); if (print_tokens==1) printf("EQ\n");};
">="                                    { total_columns += strlen(yytext); if (print_tokens==1) printf("GE\n");};
">"                                     { total_columns += strlen(yytext); if (print_tokens==1) printf("GT\n");};
"{"                                     { total_columns += strlen(yytext); if (print_tokens==1) printf("LBRACE\n");};
"<="                                    { total_columns += strlen(yytext); if (print_tokens==1) printf("LE\n");};
"("                                     { total_columns += strlen(yytext); if (print_tokens==1) printf("LPAR\n");};
"["                                     { total_columns += strlen(yytext); if (print_tokens==1) printf("LSQ\n");};
"<"                                     { total_columns += strlen(yytext); if (print_tokens==1) printf("LT\n");};
"-"                                     { total_columns += strlen(yytext); if (print_tokens==1) printf("MINUS\n");};
"%"                                     { total_columns += strlen(yytext); if (print_tokens==1) printf("MOD\n");};
"!="                                    { total_columns += strlen(yytext); if (print_tokens==1) printf("NE\n");};
"!"                                     { total_columns += strlen(yytext); if (print_tokens==1) printf("NOT\n");};
"||"                                    { total_columns += strlen(yytext); if (print_tokens==1) printf("OR\n");};
"+"                                     { total_columns += strlen(yytext); if (print_tokens==1) printf("PLUS\n");};
"}"                                     { total_columns += strlen(yytext); if (print_tokens==1) printf("RBRACE\n");};
")"                                     { total_columns += strlen(yytext); if (print_tokens==1) printf("RPAR\n");};
"]"                                     { total_columns += strlen(yytext); if (print_tokens==1) printf("RSQ\n");};
"else"                                  { total_columns += strlen(yytext); if (print_tokens==1) printf("ELSE\n");};
"for"                                   { total_columns += strlen(yytext); if (print_tokens==1) printf("FOR\n");};
"if"                                    { total_columns += strlen(yytext); if (print_tokens==1) printf("IF\n");};
"var"                                   { total_columns += strlen(yytext); if (print_tokens==1) printf("VAR\n");};
"int"                                   { total_columns += strlen(yytext); if (print_tokens==1) printf("INT\n");};
"float32"                               { total_columns += strlen(yytext); if (print_tokens==1) printf("FLOAT32\n");};
"bool"                                  { total_columns += strlen(yytext); if (print_tokens==1) printf("BOOL\n");};
"string"                                { total_columns += strlen(yytext); if (print_tokens==1) printf("STRING\n");};
"fmt.Println"                           { total_columns += strlen(yytext); if (print_tokens==1) printf("PRINT\n");};
"strconv.Atoi"                          { total_columns += strlen(yytext); if (print_tokens==1) printf("PARSEINT\n");};
"func"                                  { total_columns += strlen(yytext); if (print_tokens==1) printf("FUNC\n");};
"os.Args"                               { total_columns += strlen(yytext); if (print_tokens==1) printf("CMDARGS\n");};
{STRLIT}                                { total_columns += strlen(yytext); if (print_tokens==1) printf("STRLIT\n");};
{INT}                                   { total_columns += strlen(yytext); if (print_tokens==1) printf("INT\n");};
{OCTAL}|{HEXA}                          { total_columns += strlen(yytext); if (print_tokens==1) printf("INTLIT(%s)\n", yytext);};
{REALLIT}                               { total_columns += strlen(yytext); if (print_tokens==1) printf("REALLIT\n");};
{RESERVED}                              { total_columns += strlen(yytext); if (print_tokens==1) printf("RESERVED\n");};
_+{ID}                                  { total_columns += strlen(yytext); if (print_tokens==1) printf("ID(%s)\n", yytext);};
.                                       printf("Line %d, column %d: illegal character (%s)\n", total_lines, total_columns, yytext); total_columns += strlen(yytext);
%%
int main(int argc, char **argv)
{
if (argc > 1){
    if (strcmp(argv[1], "-l")==0) print_tokens = 1;
}
else print_tokens = 0;
yylex();
if (comment == 1){
    printf("Line %d, column %d: unterminated comment\n", error_line_number, error_column_number);
}
return 0;
}

int yywrap()
{
return 1;
}   