%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <math.h>

    //#include "symtab.h"
    #define NSYMS 100
    #define YYDEBUG 1

    //symtab tab[NSYMS];

    //symtab *symlook(char *varname);

    //void var_list();

    int yylex(void);
    void yyerror (const char *s);
%}

//Tokens
%token INTLIT
%token REALLIT
%token ID
%token FuncInvocation
%token LPAR
%token RPAR
%token OR
%token AND

%%

compiler: start
    | compiler start;
    ;

start: Expr
    |
    ;

Expr: Expr OR Expr      
    | Expr AND Expr
    | INTLIT
    ;

%%   

int main(int argc, char** argv) {
    yydebug=0;
    if (argc!=1){
        if (strcmp(argv[1], "-d")==0) yydebug = 1;
    }
    yyparse();
    return 0;
} 