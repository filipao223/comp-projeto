%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <math.h>

    //#include "symtab.h"
    #define NSYMS 100
    #define YYDEBUG 1

    int yydebug=0;

    //symtab tab[NSYMS];

    //symtab *symlook(char *varname);

    //void var_list();

    int yylex(void);
    extern int print_tokens;
    extern void yyerror(const char *s);
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
%token <str> RESERVED
%token LSQ
%token LBRACE
%token STRLIT

%left OR
%left AND
%right NOT
%left LT GT EQ NE LE GE 
%left FUNC VAR
%right PLUS MINUS
%left STAR DIV MOD
%left LPAR RPAR

%union{
    char *str;
}

%%

Program: PACKAGE ID SEMICOLON Declarations;

Declarations: 
    | DeclarationsRep; 

DeclarationsRep: DeclarationsRep VarDeclaration SEMICOLON
    | DeclarationsRep FuncDeclaration SEMICOLON
    | VarDeclaration SEMICOLON
    | FuncDeclaration SEMICOLON
    ;

VarDeclaration: VAR VarSpec
    | VAR LPAR VarSpec SEMICOLON RPAR
    ;

VarSpec: ID VarSpecRep Type;

VarSpecRep: 
    | VarSpecRep COMMA ID
    ;

Type: INT
    | FLOAT32
    | BOOL
    | STRINGVAR
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

VarsAndStatements: VarDeclaration SEMICOLON
    | Statement SEMICOLON
    | VarsAndStatements SEMICOLON
    | VarsAndStatements VarDeclaration SEMICOLON
    | VarsAndStatements Statement SEMICOLON
    ;

Statement: ID ASSIGN Expr
    | LBRACE StatementRep RBRACE
    | IF Expr LBRACE StatementRep RBRACE ElseCond
    | FOR LBRACE StatementRep RBRACE
    | FOR LBRACE StatementRep RESERVED SEMICOLON RBRACE
    | FOR Expr LBRACE StatementRep RBRACE
    | FOR Expr LBRACE StatementRep RESERVED SEMICOLON RBRACE
    | RETURN Expr
    | RETURN
    | FuncInvocation
    | ParseArgs
    | PRINT LPAR Expr RPAR
    | PRINT LPAR STRLIT RPAR
    | error
    ;

StatementRep:
    | StatementRep Statement SEMICOLON;

ElseCond:
    | ELSE LBRACE StatementRep RBRACE
    ;

ParseArgs: ID COMMA BLANKID ASSIGN PARSEINT LPAR CMDARGS LSQ Expr RSQ RPAR
    | ID COMMA BLANKID ASSIGN PARSEINT LPAR error RPAR
    ;

FuncInvocation: ID LPAR RPAR
    | ID LPAR FuncInvocationExpr RPAR
    | ID LPAR error RPAR
    ;

FuncInvocationExpr: Expr
    | Expr COMMA FuncInvocationExpr
    ;

Expr: Expr OR Expr      
    | Expr AND Expr
    | NOT Expr
    | Expr LT Expr
    | Expr GT Expr
    | Expr EQ Expr
    | Expr NE Expr
    | Expr LE Expr
    | Expr GE Expr
    | Expr PLUS Expr
    | Expr MINUS Expr
    | Expr STAR Expr
    | Expr DIV Expr
    | Expr MOD Expr
    | PLUS Expr
    | MINUS Expr
    | INTLIT | REALLIT | ID | FuncInvocation
    | LPAR Expr RPAR
    | LPAR error RPAR
    ;

%%   




int main(int argc, char** argv) {
    int yydebug;
    #if YYDEBUG
        yydebug = 1;
    #endif
    int lex_only = 0;
    if (argc!=1){
        if (strcmp(argv[1], "-l")==0) lex_only = 1;
    }
    if (lex_only==1) while(yylex()){} //Print only lex output
    else{
        print_tokens=0; //Dont print lex output | Set lex file print_tokens flag as 0
        yyparse();
    }
    return 0;
} 