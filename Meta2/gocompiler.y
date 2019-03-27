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
    ast_node *create_new_node(char name[], char id[]);
    ast_node *add_ast_node(ast_node *parent, ast_node *child);
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
%token <str> ID
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

%type <node> Expr Program Declarations DeclarationsRep VarDeclaration VarSpec VarSpecRep Type FuncDeclaration Parameters ParametersRep FuncBody
%type <node> VarsAndStatements Statement StatementRep ElseCond ParseArgs FuncInvocation FuncInvocationExpr

%union{
    char *str;
    struct ast_node *node;
}

%%

Program: PACKAGE ID SEMICOLON Declarations                       {root = add_ast_node(create_new_node("Program", NULL), $4);}
    ;

Declarations:                           {$$ = NULL;}
    | DeclarationsRep                   {$$ = $1;}                            
    ;

DeclarationsRep: DeclarationsRep VarDeclaration SEMICOLON    {$$ = add_ast_node(create_new_node("VarDecl", NULL), $1);}               
    | DeclarationsRep FuncDeclaration SEMICOLON              {$$ = add_ast_node(create_new_node("FuncDecl", NULL), $1);}               
    | VarDeclaration SEMICOLON                               {$$ = $1;}               
    | FuncDeclaration SEMICOLON                              {$$ = $1;}               
    ;

VarDeclaration: VAR VarSpec                                  {$$ = $2;}
    | VAR LPAR VarSpec SEMICOLON RPAR                        {$$ = $3;}
    ;

VarSpec: ID VarSpecRep Type                                {$$ = add_ast_node(create_new_node("ID", "test"), $2);}
    ;

VarSpecRep:                                                 {$$ = create_new_node("temp", NULL);}
    | VarSpecRep COMMA ID                                   {$$ = add_ast_node(create_new_node("ID", "another"), $1);}
    ; 

Type: INT
    | FLOAT32
    | BOOL
    | STRINGVAR
    ;

FuncDeclaration: FUNC ID LPAR RPAR Type FuncBody            { 
                                                                ast_node* new_node = create_new_node("FuncDecl", NULL); 
                                                                add_ast_node(new_node, add_ast_node(create_new_node("FuncHeader", NULL), create_new_node("ID", $2)));
                                                                add_ast_node(new_node, $6);
                                                                $$ = new_node;
                                                            }
    | FUNC ID LPAR Parameters RPAR FuncBody                 {$$ = add_ast_node(create_new_node("FuncDecl", NULL), $6);}
    | FUNC ID LPAR Parameters RPAR Type FuncBody            {$$ = add_ast_node(create_new_node("FuncDecl", NULL), $6);}
    | FUNC ID LPAR RPAR FuncBody                            { 
                                                                ast_node* new_node = create_new_node("FuncDecl", NULL);
                                                                ast_node* funcHeader =  create_new_node("FuncHeader", NULL);
                                                                add_ast_node(funcHeader, create_new_node("ID", $2));
                                                                add_ast_node(funcHeader, create_new_node("FuncParam", NULL));
                                                                add_ast_node(new_node, funcHeader);
                                                                add_ast_node(new_node, $5);
                                                                $$ = new_node;
                                                            }
    ;

Parameters: ID Type ParametersRep;

ParametersRep:
    | ParametersRep COMMA ID Type
    ;

FuncBody: LBRACE VarsAndStatements RBRACE                   {$$ = add_ast_node(create_new_node("FuncBody", NULL), $2);}
    | LBRACE RBRACE                                         {$$ = create_new_node("FuncBody", NULL);}
    ;

VarsAndStatements: VarDeclaration SEMICOLON                 {$$ = $1;}
    | Statement SEMICOLON                                   {$$ = $1;}
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
    | INTLIT                            
    | REALLIT                           
    | ID                                
    | FuncInvocation       
    | LPAR Expr RPAR                    
    | LPAR error RPAR                   
    ;

%%   

ast_node *create_new_node(char name[], char id[]){
    ast_node *new_node = malloc(sizeof(struct ast_node));
    new_node->num_children = 0;
    if (name == NULL) return NULL; //Name can't be empty
    strcpy(new_node->name, name);

    if (id != NULL) strcpy(new_node->id, id);
    else strcpy(new_node->id, "");

    return new_node;
}

//TODO: use different functions for different node types, perhaps
ast_node *add_ast_node(ast_node *parent, ast_node *child){
    if (child != NULL && parent != NULL){
        parent->children[parent->num_children] = child;
        parent->num_children += 1;

        return parent;
    }

    return NULL;
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
        yyparse();
        if (print_tree==1) print_ast_tree(root, 0);
        free_ast_tree(root);
    }
    return 0;
} 