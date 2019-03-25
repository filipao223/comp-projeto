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
%token STRLIT

%left AND OR LT GT EQ NE LE GE LPAR RPAR

%%

Program: PACKAGE ID SEMICOLON Declarations;

Declarations: DeclarationsRep; 

DeclarationsRep:
    | DeclarationsRep VarDeclaration SEMICOLON
    | DeclarationsRep FuncDeclaration SEMICOLON
    ;

VarDeclaration: VAR VarSpec
    | VAR LPAR VarSpec SEMICOLON RPAR
    ;

VarSpec: ID VarSpecRep Type;

VarSpecRep: 
    | VarSpecRep ID COMMA
    ;

Type: INT
    | FLOAT32
    | BOOL
    | string
    ;

FuncDeclaration: FUNC ID LPAR RPAR Type FuncBody
    | FUNC ID LPAR Parameters RPAR FuncBody
    | FUNC ID LPAR Parameters RPAR Type FuncBody
    | FUNC ID LPAR RPAR FuncBody
    ;

Parameters: ID Type ParametersRep;

ParametersRep:
    | ParametersRep COMMA ID Type
    ;

FuncBody: LBRACE VarsAndStatements RBRACE
    | LBRACE RBRACE
    ;

VarsAndStatements: VarsAndStatements SEMICOLON
    | VarsAndStatements VarDeclaration SEMICOLON
    | VarsAndStatements Statement SEMICOLON
    ;

Statement: ID ASSIGN Expr
    | LBRACE StatementRep RBRACE
    | IF Expr LBRACE StatementRep RBRACE ElseCond
    | FOR LBRACE StatementRep RBRACE
    | FOR Expr LBRACE StatementRep RBRACE
    | RETURN Expr
    | RETURN
    | FuncInvocation
    | ParseArgs
    | PRINT LPAR Expr RPAR
    | PRINT LPAR STRLIT RPAR
    ;

StatementRep:
    | StatementRep Statement SEMICOLON;

ElseCond:
    | ELSE LBRACE StatementRep RBRACE
    ;

ParseArgs: ID COMMA BLANKID ASSIGN PARSEINT LPAR CMDARGS LSQ Expr RSQ RPAR;

FuncInvocation: ID LPAR RPAR
    | ID LPAR FuncInvocationExpr RPAR
    ;

FuncInvocationExpr: Expr
    | Expr COMMA FuncInvocationExpr
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