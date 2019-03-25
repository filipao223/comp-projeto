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
%token FUNC
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
%token STRINGVAR
%token PRINT
%token PARSEINT
%token CMDARGS
%token RESERVED
%token LSQ
%token LBRACE

%left AND OR LT GT EQ NE LE GE
%left LPAR
%right RPAR

%%

compiler: start
    | compiler start;
    ;

start: Expr
    | FuncInvocation
    | Statement
    ;

Statement: ID ASSIGN Expr
    | LBRACE Statement SEMICOLON RBRACE
    | IF Expr LBRACE RBRACE StatementOpen
    | IF Expr LBRACE Statement SEMICOLON RBRACE StatementOpen
    | FOR Expr LBRACE Statement SEMICOLON RBRACE
    | FOR Expr LBRACE RBRACE
    | FOR LBRACE Statement SEMICOLON RBRACE
    | FOR LBRACE RBRACE
    | FuncInvocation | ParseArgs
    | PRINT LPAR Expr RPAR
    | RETURN Expr
    | RETURN
    | 
    ;

StatementOpen: ELSE LBRACE ELSE LBRACE Statement SEMICOLON RBRACE Statement
    ;

ParseArgs: ID COMMA BLANKID ASSIGN PARSEINT LPAR CMDARGS LSQ Expr RSQ RPAR
    ;

FuncInvocation: ID LPAR Expr FuncInvocationExpr
    | ID LPAR RPAR
    ;

FuncInvocationExpr: Expr COMMA FuncInvocationExpr
    | RPAR
    ;

Expr: Expr OR Expr      
    | Expr AND Expr
    | LPAR Expr RPAR
    | Expr LT Expr
    | Expr GT Expr
    | Expr EQ Expr
    | Expr NE Expr
    | Expr LE Expr
    | Expr GE Expr
    | INTLIT | REALLIT | ID | FuncInvocation
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