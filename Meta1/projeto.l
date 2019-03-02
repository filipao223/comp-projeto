%{
    //If argument -1 is received, set as 1
    int print_tokens;

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

" "                                     ;
"\n"                                    ;
"/*"                                    {comment = 1;BEGIN COMMENT;};
<COMMENT>[^[*|/]]*                      ;
<COMMENT>"*/"                           {comment = 0; BEGIN 0;};
";"                                     {if (print_tokens==1) printf("SEMICOLON\n");};
"_"                                     {if (print_tokens==1) printf("BLANKID\n");};
"package"                               {if (print_tokens==1) printf("PACKAGE\n");};
"return"                                {if (print_tokens==1) printf("RETURN\n");};
"&&"                                    {if (print_tokens==1) printf("AND\n");};
"="                                     {if (print_tokens==1) printf("ASSIGN\n");};
"*"                                     {if (print_tokens==1) printf("STAR\n");};
","                                     {if (print_tokens==1) printf("COMMA\n");};
"/"                                     {if (print_tokens==1) printf("DIV\n");};
"=="                                    {if (print_tokens==1) printf("EQ\n");};
">="                                    {if (print_tokens==1) printf("GE\n");};
">"                                     {if (print_tokens==1) printf("GT\n");};
"{"                                     {if (print_tokens==1) printf("LBRACE\n");};
"<="                                    {if (print_tokens==1) printf("LE\n");};
"("                                     {if (print_tokens==1) printf("LPAR\n");};
"["                                     {if (print_tokens==1) printf("LSQ\n");};
"<"                                     {if (print_tokens==1) printf("LT\n");};
"-"                                     {if (print_tokens==1) printf("MINUS\n");};
"%"                                     {if (print_tokens==1) printf("MOD\n");};
"!="                                    {if (print_tokens==1) printf("NE\n");};
"!"                                     {if (print_tokens==1) printf("NOT\n");};
"||"                                    {if (print_tokens==1) printf("OR\n");};
"+"                                     {if (print_tokens==1) printf("PLUS\n");};
"}"                                     {if (print_tokens==1) printf("RBRACE\n");};
")"                                     {if (print_tokens==1) printf("RPAR\n");};
"]"                                     {if (print_tokens==1) printf("RSQ\n");};
"else"                                  {if (print_tokens==1) printf("ELSE\n");};
"for"                                   {if (print_tokens==1) printf("FOR\n");};
"if"                                    {if (print_tokens==1) printf("IF\n");};
"var"                                   {if (print_tokens==1) printf("VAR\n");};
"int"                                   {if (print_tokens==1) printf("INT\n");};
"float32"                               {if (print_tokens==1) printf("FLOAT32\n");};
"bool"                                  {if (print_tokens==1) printf("BOOL\n");};
"string"                                {if (print_tokens==1) printf("STRING\n");};
"fmt.Println"                           {if (print_tokens==1) printf("PRINT\n");};
"strconv.Atoi"                          {if (print_tokens==1) printf("PARSEINT\n");};
"func"                                  {if (print_tokens==1) printf("FUNC\n");};
"os.Args"                               {if (print_tokens==1) printf("CMDARGS\n");};
{STRLIT}                                {if (print_tokens==1) printf("STRLIT\n");};
{INT}                                   {if (print_tokens==1) printf("INT\n");};
{OCTAL}|{HEXA}                          {if (print_tokens==1) printf("INTLIT(%s)\n", yytext);};
{REALLIT}                               {if (print_tokens==1) printf("REALLIT\n");};
{RESERVED}                              {if (print_tokens==1) printf("RESERVED\n");};
_*{ID}                                  {if (print_tokens==1) printf("ID(%s)\n", yytext);};
.                                       ;
%%
int main(int argc, char **argv)
{
if (argc > 1){
    if (strcmp(argv[1], "-l")==0) print_tokens = 1;
}
else print_tokens = 0;
yylex();
//if (comment == 1) printf("Missing /*");
return 0;
}

int yywrap()
{
return 1;
}   