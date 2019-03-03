%{
    #define MAX_STR 1024
    //If argument -1 is received, set as 1
    int print_tokens;

    //Line and column counter
    int total_lines = 1;
    int total_columns = 1;

    //Save first line and column where a possible error might occur
    int error_line_number;
    int error_column_number;

    // /*...*/ like comments. to detect if analysis ended and it wasnt closed
    int comment = 0;

    //In case a \n is found and either an ID, INTLIT, REALIT, STRLIT RETURN or braces were last
    int semicolon = 0;

    //Hold current strlit
    char current_string[MAX_STR];
%}

ID                                      ([A-Z|a-z]+([0-9])*_?[0-9|A-Z|a-z]*)*
RESERVED                                (break|default|func|interface|select|case|defer|go|map|struct|chan|else|goto|package|switch|const|fallthrough|if|range|type|continue|for|import|return|var|"++"|"--")
OCTAL                                   (0)[0-7]+
HEXA                                    (0x|0X)([0-9]+|[a-f|A-F]+)+
INT                                     ([1-9]*|0)
REALLIT                                 (([1-9]*\.[0-9]+)*|([1-9]\.?)*)+((e|E)(\-|\+)?[0-9]+)?

%X COMMENT
%X STRING
%X ILLEGAL_ESC

%%

" "                                     total_columns += strlen(yytext);
"\t"                                    ;
"\n"                                    { ++total_lines; total_columns=1; if (semicolon==1 && print_tokens==1){printf("SEMICOLON\n"); semicolon=0;}};
"/*"                                    {  error_line_number = total_lines; error_column_number = total_columns; total_columns+= 2;comment = 1;BEGIN COMMENT;};
<COMMENT>"\n"                           ++total_lines; total_columns=1;
<COMMENT>[^["*/"]]*                       total_columns += strlen(yytext);
<COMMENT>"*/"                           { total_columns += 2; comment = 0; BEGIN 0;};
<COMMENT>.                              { total_columns += strlen(yytext);};
";"                                     { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("SEMICOLON\n");};
"_"                                     { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("BLANKID\n");};
"package"                               { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("PACKAGE\n");};
"return"                                { semicolon=1; total_columns += strlen(yytext); if (print_tokens==1) printf("RETURN\n");};
"&&"                                    { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("AND\n");};
"="                                     { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("ASSIGN\n");};
"*"                                     { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("STAR\n");};
","                                     { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("COMMA\n");};
"//".*                                  ;
"/"                                     { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("DIV\n");};
"=="                                    { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("EQ\n");};
">="                                    { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("GE\n");};
">"                                     { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("GT\n");};
"{"                                     { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("LBRACE\n");};
"<="                                    { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("LE\n");};
"("                                     { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("LPAR\n");};
"["                                     { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("LSQ\n");};
"<"                                     { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("LT\n");};
"-"                                     { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("MINUS\n");};
"%"                                     { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("MOD\n");};
"!="                                    { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("NE\n");};
"!"                                     { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("NOT\n");};
"||"                                    { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("OR\n");};
"+"                                     { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("PLUS\n");};
"}"                                     { semicolon=1; total_columns += strlen(yytext); if (print_tokens==1) printf("RBRACE\n");};
")"                                     { semicolon=1; total_columns += strlen(yytext); if (print_tokens==1) printf("RPAR\n");};
"]"                                     { semicolon=1; total_columns += strlen(yytext); if (print_tokens==1) printf("RSQ\n");};
"else"                                  { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("ELSE\n");};
"for"                                   { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("FOR\n");};
"if"                                    { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("IF\n");};
"var"                                   { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("VAR\n");};
"int"                                   { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("INT\n");};
"float32"                               { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("FLOAT32\n");};
"bool"                                  { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("BOOL\n");};
"string"                                { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("STRING\n");};
"fmt.Println"                           { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("PRINT\n");};
"strconv.Atoi"                          { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("PARSEINT\n");};
"func"                                  { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("FUNC\n");};
"os.Args"                               { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("CMDARGS\n");};
\"                                      { error_column_number = total_columns; semicolon=0; ++total_columns; current_string[0] = '\0'; BEGIN STRING;};
<STRING>\\((\\)|n|f|r|t|(\"))           { semicolon=0; total_columns+= strlen(yytext); strcat(current_string, yytext);};
<STRING>\"                              { semicolon=1; ++total_columns; if (print_tokens==1) printf("STRLIT(\"%s\")\n", current_string); BEGIN 0;};
<STRING>\\[^n]                          { printf("Line %d, column %d: invalid escape sequence (%s)\n", total_lines, total_columns, yytext); total_columns += strlen(yytext); BEGIN ILLEGAL_ESC;};
<STRING>"\n"                            { semicolon=0; printf("Line %d, column %d: unterminated string literal\n", total_lines, error_column_number); total_columns=1; ++total_lines; BEGIN 0;};
<STRING>.                               { semicolon=0; total_columns += strlen(yytext); strcat(current_string, yytext);};
<ILLEGAL_ESC>\"                         { semicolon = 1; BEGIN 0;};
<ILLEGAL_ESC>"\n"                       { ++total_lines; BEGIN 0;};
<ILLEGAL_ESC>.                          ;
{INT}|{OCTAL}|{HEXA}                    { semicolon=1; total_columns += strlen(yytext); if (print_tokens==1) printf("INTLIT(%s)\n", yytext);};
{REALLIT}                               { semicolon=1; total_columns += strlen(yytext); if (print_tokens==1) printf("REALLIT(%s)\n", yytext);};
{RESERVED}                              { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("RESERVED(%s)\n", yytext);};
{ID}                                    { semicolon=1; total_columns += strlen(yytext); if (print_tokens==1) printf("ID(%s)\n", yytext);};
.                                       printf("Line %d, column %d: illegal character (%s)\n", total_lines, total_columns, yytext); total_columns += strlen(yytext);
%%
int main(int argc, char **argv)
{
if (argc > 1){
    if (strcmp(argv[1], "-l")==0) print_tokens = 1;
}
else print_tokens = 0;
yylex();
//Check if a semicolon should be printed
    if (semicolon==1 && print_tokens==1) printf("SEMICOLON\n");
if (comment == 1){
    printf("Line %d, column %d: unterminated comment\n", error_line_number, error_column_number);
}
return 0;
}

int yywrap()
{
return 1;
}   