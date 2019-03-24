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
%token LT
%token GT
%token EQ
%token NE
%token LE
%token GE
%token SEMICOLON
%token BLANKID
%token PACKAGE
%token RETURN
%token ASSIGN
%token STAR
%token COMMA
%token DIV
%token MINUS
%token MOD
%token NOT
%token PLUS
%token RBRACE
%token RSQ
%token ELSE
%token FOR
%token IF
%token VAR
%token INT
%token FLOAT32
%token BOOL
%token STRING
%token PRINT
%token PARSEINT
%token FUNC
%token CMDARGS
%token RESERVED
%token ID
%token LSQ
%token LBRACE

%left OR
%right AND

%%

compiler: start
    | compiler start;
    ;

start: Expr
    |
    ;

Expr: Expr OR Expr      
    | Expr AND Expr
    | LPAR Expr RPAR
    | INTLIT | REALLIT | ID | FuncInvocation
    | Expr LT Expr
    | Expr GT Expr
    | Expr EQ Expr
    | Expr NE Expr
    | Expr LE Expr
    | Expr GE Expr
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