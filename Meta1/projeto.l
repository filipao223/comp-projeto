ID                                      ([A-Z]*|[a-z]*)+
RESERVED                                (break|default|func|interface|select|case|defer|go|map|struct|chan|else|goto|package|switch|const|fallthrough|if|range|type|continue|for|import|return|var|"++"|"--")
OCTAL                                   (0)[0-7]+
HEXA                                    (0x|0X)([0-9]*|[a-f|A-F]*)+
REALLIT                                 ([1-9]*"."?[0-9]*((e|E)("-"|"+")?[0-9]+)?)
STRLIT                                  (\"([A-Z|a-z]*|"\f|\n|\r|\t|\\|\""*|[0-9]*)*\")                            
%%

" "                                     ;
"\n"                                    ;
";"                                     printf("SEMICOLON\n");
"_"                                     printf("BLANKID\n");
"package"                               printf("PACKAGE\n");
"return"                                printf("RETURN\n");
"&&"                                    printf("AND\n");
"="                                     printf("ASSIGN\n");
"*"                                     printf("STAR\n");
","                                     printf("COMMA\n");
"/"                                     printf("DIV\n");
"=="                                    printf("EQ\n");
">="                                    printf("GE\n");
">"                                     printf("GT\n");
"{"                                     printf("LBRACE\n");
"<="                                    printf("LE\n");
"("                                     printf("LPAR\n");
"["                                     printf("LSQ\n");
"<"                                     printf("LT\n");
"-"                                     printf("MINUS\n");
"%"                                     printf("MOD\n");
"!="                                    printf("NE\n");
"!"                                     printf("NOT\n");
"||"                                    printf("OR\n");
"+"                                     printf("PLUS\n");
"}"                                     printf("RBRACE\n");
")"                                     printf("RPAR\n");
"]"                                     printf("RSQ\n");
"else"                                  printf("ELSE\n");
"for"                                   printf("FOR\n");
"if"                                    printf("IF\n");
"var"                                   printf("VAR\n");
"int"                                   printf("INT\n");
"float32"                               printf("FLOAT32\n");
"bool"                                  printf("BOOL\n");
"string"                                printf("STRING\n");
"fmt.Println"                           printf("PRINT\n");
"strconv.Atoi"                          printf("PARSEINT\n");
"func"                                  printf("FUNC\n");
"os.Args"                               printf("CMDARGS\n");
{STRLIT}                                printf("STRLIT\n");
{OCTAL}|{HEXA}                          printf("INTLIT\n");
{REALLIT}                               printf("REALLIT\n");
{RESERVED}                              printf("RESERVED\n");
_*{ID}                                  printf("ID\n");

%%
int main()
{
yylex();
return 0;
}

int yywrap()
{
return 1;
}   