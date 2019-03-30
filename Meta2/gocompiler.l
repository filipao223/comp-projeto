/* João Filipe Sequeira Montenegro Nº2016228672 | Flávio Amaral Fernandes Nº2016240139*/
%{
    #include "y.tab.h"

    #define MAX_STR 1024
    //If argument -1 is received, set as 1
    int print_tokens=1;

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

ID                                      ([A-Za-z_][0-9A-Za-z_]*)
RESERVED                                (break|default|func|interface|select|case|defer|go|map|struct|chan|else|goto|package|switch|const|fallthrough|if|range|type|continue|for|import|return|var|"++"|"--")
OCTAL                                   (0)[0-9]+
HEXA                                    (0x|0X)[a-fA-F0-9]+
INT                                     0|[1-9][0-9]*
REALLIT                                 (([0-9]*\.[0-9]+)|([0-9]+\.)|([1-9]\.)|[1-9]+)((e|E)(\-|\+)?[0-9]+)?

%X COMMENT
%X STRING
%X ILLEGAL_ESC

%%

" "                                     total_columns += strlen(yytext);
"\t"                                    total_columns+=strlen(yytext);
"\n"                                    {  ++total_lines; total_columns=1; if (semicolon==1 && print_tokens==1){printf("SEMICOLON\n"); semicolon=0;} else if (semicolon==1){ semicolon=0; return SEMICOLON;}};
"/*"                                    {  error_line_number = total_lines; error_column_number = total_columns; total_columns+= 2;comment = 1;BEGIN COMMENT;};
<COMMENT>"\n"                           ++total_lines; total_columns=1;
<COMMENT>[^["*/"]]*                       total_columns += strlen(yytext);
<COMMENT>"*/"                           { total_columns += 2; comment = 0; BEGIN 0;};
<COMMENT><<EOF>>                        { printf("Line %d, column %d: unterminated comment\n", error_line_number, error_column_number);semicolon=0; BEGIN 0;}
<COMMENT>.                              { total_columns += strlen(yytext);};
";"                                     { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("SEMICOLON\n"); return SEMICOLON;};
"_"                                     { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("BLANKID\n"); return BLANKID;};
"package"                               { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("PACKAGE\n"); return PACKAGE;};
"return"                                { semicolon=1; total_columns += strlen(yytext); if (print_tokens==1) printf("RETURN\n"); return RETURN;};
"&&"                                    { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("AND\n"); return AND;};
"="                                     { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("ASSIGN\n"); return ASSIGN;};
"*"                                     { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("STAR\n");return STAR;};
","                                     { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("COMMA\n");return COMMA;};
"//".*                                  ;
"/"                                     { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("DIV\n");return DIV;};
"=="                                    { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("EQ\n");return EQ;};
">="                                    { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("GE\n");return GE;};
">"                                     { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("GT\n");return GT;};
"{"                                     { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("LBRACE\n");return LBRACE;};
"<="                                    { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("LE\n");return LE;};
"("                                     { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("LPAR\n"); return LPAR;};
"["                                     { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("LSQ\n");return LSQ;};
"<"                                     { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("LT\n");return LT;};
"-"                                     { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("MINUS\n");return MINUS;};
"%"                                     { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("MOD\n");return MOD;};
"!="                                    { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("NE\n");return NE;};
"!"                                     { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("NOT\n");return NOT;};
"||"                                    { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("OR\n"); return OR;};
"+"                                     { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("PLUS\n");return PLUS;};
"}"                                     { semicolon=1; total_columns += strlen(yytext); if (print_tokens==1) printf("RBRACE\n");return RBRACE;};
")"                                     { semicolon=1; total_columns += strlen(yytext); if (print_tokens==1) printf("RPAR\n"); return RPAR;};
"]"                                     { semicolon=1; total_columns += strlen(yytext); if (print_tokens==1) printf("RSQ\n");return RSQ;};
"else"                                  { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("ELSE\n");return ELSE;};
"for"                                   { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("FOR\n");return FOR;};
"if"                                    { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("IF\n");return IF;};
"var"                                   { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("VAR\n");return VAR;};
"int"                                   { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("INT\n");return INT;};
"float32"                               { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("FLOAT32\n");return FLOAT32;};
"bool"                                  { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("BOOL\n");return BOOL;};
"string"                                { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("STRING\n");return STRINGVAR;};
"fmt.Println"                           { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("PRINT\n");return PRINT;};
"strconv.Atoi"                          { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("PARSEINT\n");return PARSEINT;};
"func"                                  { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("FUNC\n");return FUNC;};
"os.Args"                               { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("CMDARGS\n");return CMDARGS;};
\"                                      { error_column_number = total_columns; semicolon=0; ++total_columns; current_string[0] = '\0'; BEGIN STRING;};
<STRING>\\(\\|n|f|r|t|(\"))             { semicolon=0; total_columns+= strlen(yytext); strcat(current_string, yytext);};
<STRING>\"                              { semicolon=1; ++total_columns; if (print_tokens==1) printf("STRLIT(\"%s\")\n", current_string); BEGIN 0; yylval.str = strdup(yytext); return STRLIT;};
<STRING>\\"\t"+|\\" "+                  {printf("Line %d, column %d: invalid escape sequence (%c)\n", total_lines, total_columns, yytext[0]); total_columns += strlen(yytext); BEGIN ILLEGAL_ESC;};
<STRING>\\[^"\n"]|\\                    { semicolon=0; printf("Line %d, column %d: invalid escape sequence (%s)\n", total_lines, total_columns, yytext); total_columns += strlen(yytext); BEGIN ILLEGAL_ESC;};
<STRING>"\n"|"\r"|"\r\n"                { semicolon=0; printf("Line %d, column %d: unterminated string literal\n", total_lines, error_column_number); total_columns=1; ++total_lines; BEGIN 0;};
<STRING>.                               { semicolon=0; total_columns += strlen(yytext); strcat(current_string, yytext);};
<STRING><<EOF>>                         { semicolon=0; printf("Line %d, column %d: unterminated string literal\n", total_lines, error_column_number); ++total_lines; BEGIN 0;};
<ILLEGAL_ESC>\"                         { semicolon=0; BEGIN 0;};
<ILLEGAL_ESC>\\"\t"+|\\" "+             {printf("Line %d, column %d: invalid escape sequence (%c)\n", total_lines, total_columns, yytext[0]); total_columns += strlen(yytext);};
<ILLEGAL_ESC>\\[^"\n"]|\\               {printf("Line %d, column %d: invalid escape sequence (%s)\n", total_lines, total_columns, yytext); total_columns += strlen(yytext);};
<ILLEGAL_ESC>"\n"                       { semicolon=0; printf("Line %d, column %d: unterminated string literal\n", total_lines, error_column_number); total_columns=1; ++total_lines; BEGIN 0;};
<ILLEGAL_ESC>.                          total_columns+=strlen(yytext);
<ILLEGAL_ESC><<EOF>>                    { semicolon=0; printf("Line %d, column %d: unterminated string literal\n", total_lines, error_column_number); ++total_lines; BEGIN 0;};
{INT}|{OCTAL}|{HEXA}                    { semicolon=1; total_columns += strlen(yytext); if (print_tokens==1) printf("INTLIT(%s)\n", yytext); yylval.int_value = atoi(yytext); return INTLIT;};
{REALLIT}                               { semicolon=1; total_columns += strlen(yytext); if (print_tokens==1) printf("REALLIT(%s)\n", yytext); yylval.float_value = atof(yytext); return REALLIT;};
{RESERVED}                              { semicolon=0; total_columns += strlen(yytext); if (print_tokens==1) printf("RESERVED(%s)\n", yytext); yylval.str = strdup(yytext); return RESERVED;};
{ID}                                    { semicolon=1; total_columns += strlen(yytext); if (print_tokens==1) printf("ID(%s)\n", yytext); yylval.str = strdup(yytext); return ID;};
<<EOF>>                                 { if (semicolon==1 && print_tokens==1) printf("SEMICOLON\n"); return 0;}
.                                       printf("Line %d, column %d: illegal character (%s)\n", total_lines, total_columns, yytext); total_columns += strlen(yytext);

%%
/*int main(int argc, char **argv)
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
}*/

int yywrap()
{
return 1;
}   

void yyerror(const char *s){
    if (strcmp("\n", yytext)==0){
        printf("Line %d, column %d: %s: %s\n",  error_line_number, error_column_number, s, yytext);
    }
    printf("Line %d, column %d: %s: %s\n",  total_lines, (int)(total_columns-strlen(yytext)), s, yytext);
}
