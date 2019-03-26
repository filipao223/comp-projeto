%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <math.h>

    //#include "symtab.h"
    #define NSYMS 100
    #define YYDEBUG 1

    #define MAX_TEMP 1024

    #define MAX_AST_NODE_NAME 1024
    #define MAX_AST_NODE_ID 1024
    #define MAX_AST_NODE_CHILDREN 1024

    int yydebug=0;

    //symtab tab[NSYMS];

    //symtab *symlook(char *varname);

    //void var_list();

    int yylex(void);
    extern int print_tokens;
    extern void yyerror(const char *s);

    char temp[MAX_TEMP];

    //AST
    typedef struct ast_node{
        char name[MAX_AST_NODE_NAME];
        char id[MAX_AST_NODE_ID];
        struct ast_node *parent;
        struct ast_node *children[MAX_AST_NODE_CHILDREN];
        int num_children;
    } ast_node;

    //AST functions
    ast_node *create_new_node(char name[], char id[], ast_node *parent);
    void add_ast_node(ast_node *current, ast_node *new_node);
    void print_ast_tree(ast_node *root, int level);
    void free_ast_tree(ast_node* root);

    //AST root node
    ast_node *root = NULL;
    //AST current node
    ast_node *current = NULL;
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

%type <node> Expr Program Declarations DeclarationsRep VarDeclaration VarSpec VarSpecRep Type FuncDeclaration Parameters ParametersRep

%union{
    char *str;
    ast_node* node;
}

%%

Program: PACKAGE ID SEMICOLON Declarations                                  {add_ast_node(root, $4);}
    ;

Declarations: 
    | DeclarationsRep                                                       {$$ = $1;}
    ;

DeclarationsRep: DeclarationsRep VarDeclaration SEMICOLON                   {$$ = add_ast_node($$, $2);}
    | DeclarationsRep FuncDeclaration SEMICOLON                             {$$ = add_ast_node($$, $2);}
    | VarDeclaration SEMICOLON                                              {$$ = add_ast_node($$, $1);}
    | FuncDeclaration SEMICOLON                                             {$$ = add_ast_node($$, $1);}
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
    | MINUS Expr                        {$$}
    | INTLIT                            {$$ = create_new_node("INTLIT", "1", NULL);}
    | REALLIT                           {$$ = create_new_node("REALLIT", "1", NULL);}
    | ID                                {$$ = create_new_node("ID", "1", NULL);}
    | FuncInvocation
    | LPAR Expr RPAR                    {$$ = add_ast_node($$, $2);}
    | LPAR error RPAR                   {$$ = NULL;}
    ;

%%   

ast_node *create_new_node(char name[], char id[], ast_node *parent){
    ast_node *new_node = malloc(sizeof(struct ast_node));
    new_node->parent = parent;
    new_node->num_children = 0;
    if (name == NULL) return NULL; //Name can't be empty
    strcpy(new_node->name, name);

    if (id != NULL) strcpy(new_node->id, id);
    else strcpy(new_node->id, "");

    return new_node;
}

//TODO: use different functions for different node types, perhaps
void add_ast_node(ast_node *current, ast_node *new_node){
    if (new_node != NULL && current != NULL){
        current->children[current->num_children] = new_node;
        current->num_children += 1;
    }
}

void print_ast_tree(ast_node *root, int level){
    if (root==NULL) return;

    //Print dots (two for each level above 0)
    for (int i=0; i<level*2; i++) printf(".");

    //Print itself
    if (strcmp(root->id, "")==0){ //If id is empty
        printf("%s\n", root->name);
    }
    else{
        printf("%s(%s)\n", root->name, root->id);
    }

    //Print all its children recursively
    for (int i=0; i<root->num_children; i++){
        print_ast_tree(root->children[i], level+1);
    }
}

void free_ast_tree(ast_node* root){
    //Iterate over all children
    for (int i=0; i< root->num_children; i++){
        free_ast_tree(root->children[i]);
    }

    //Free memory
    free(root);
}

int main(int argc, char** argv) {
    int yydebug;
    #if YYDEBUG
        yydebug = 1;
    #endif

    int lex_only = 0;
    int print_tree = 0;

    if (argc!=1){
        if (strcmp(argv[1], "-l")==0) lex_only = 1;
        if (strcmp(argv[1], "-t")==0) print_tree = 1;
    }

    if (lex_only==1) while(yylex()){} //Print only lex output
    else{
        print_tokens=0; //Dont print lex output | Set lex file print_tokens flag as 0
        root = create_new_node("Program", NULL, NULL);
        yyparse();
        if (print_tree==1) print_ast_tree(root, 0);
        free_ast_tree(root);
    }
    return 0;
} 