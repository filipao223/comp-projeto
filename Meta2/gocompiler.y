%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <math.h>

    //#include "symtab.h"
    #define NSYMS 100
    #define YYDEBUG 0

    #define _id_ "Id"
    #define _func_params_ "FuncParams"

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
    ast_node *add_ast_list(ast_node *parent, ast_node *head);
    void copy_ast_data(ast_node *dest, ast_node *src);
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

Program: PACKAGE ID SEMICOLON Declarations                  {
                                                                root = add_ast_node(create_new_node("Program", NULL), $4);
                                                                root = root==NULL ? create_new_node("Program", NULL):root;
                                                            }
    ;

Declarations:                                               {$$ = create_new_node("empty", NULL);}
    | DeclarationsRep                                       {$$ = $1;}
    ;

DeclarationsRep: DeclarationsRep VarDeclaration SEMICOLON   {
                                                                $$ = add_ast_list(create_new_node("VarDecl", NULL), $1);

                                                            }
    | DeclarationsRep FuncDeclaration SEMICOLON             {
                                                                $$ = add_ast_list(create_new_node("FuncDecl", NULL), $1);
                                                            }
    | VarDeclaration SEMICOLON                              {$$ = $1;}
    | FuncDeclaration SEMICOLON                             {$$ = $1;}
    ;

VarDeclaration: VAR VarSpec                                 {   
                                                                ast_node* temp_root = create_new_node("root", NULL);
                                                                ast_node *linked_list = add_ast_node(temp_root, $2);
                                                                $$ = linked_list;
                                                            }
    | VAR LPAR VarSpec SEMICOLON RPAR                       {$$ = $3;}
    ;

VarSpec: ID VarSpecRep Type                                 {
                                                                ast_node* id_node = create_new_node(_id_, $1);
                                                                //ast_node* temp_root = create_new_node("root", NULL);
                                                                //ast_node* linked_list = add_ast_node(id_node, $2);
                                                                $$ = add_ast_node(id_node, $3);
                                                            }
    ;

VarSpecRep:                                                 {$$ = create_new_node("empty", NULL);}
    | VarSpecRep COMMA ID                                   {$$ = add_ast_node(create_new_node(_id_, $3), $1);}
    ; 

Type: INT                                                   {$$ = create_new_node("Int", NULL);}
    | FLOAT32                                               {$$ = create_new_node("Float32", NULL);}
    | BOOL                                                  {$$ = create_new_node("Bool", NULL);}
    | STRINGVAR                                             {$$ = create_new_node("String", NULL);}
    ;

FuncDeclaration: FUNC ID LPAR RPAR Type FuncBody            { 
                                                                ast_node* new_node = create_new_node("FuncDecl", NULL); 
                                                                add_ast_node(new_node, add_ast_node(create_new_node("FuncHeader", NULL), create_new_node("ID", $2)));
                                                                add_ast_node(new_node, $6);
                                                                add_ast_node(new_node, create_new_node("FuncBody", NULL));
                                                                $$ = new_node;
                                                            }
    | FUNC ID LPAR Parameters RPAR FuncBody                 {$$ = add_ast_node(create_new_node("FuncDecl", NULL), $6);}
    | FUNC ID LPAR Parameters RPAR Type FuncBody            {$$ = add_ast_node(create_new_node("FuncDecl", NULL), $6);}
    | FUNC ID LPAR RPAR FuncBody                            { 
                                                                ast_node* new_node = create_new_node("FuncDecl", NULL);
                                                                ast_node* funcHeader =  create_new_node("FuncHeader", NULL);
                                                                add_ast_node(funcHeader, create_new_node(_id_, $2));
                                                                add_ast_node(funcHeader, create_new_node(_func_params_, NULL));
                                                                add_ast_node(new_node, funcHeader);
                                                                add_ast_node(new_node, $5);
                                                                $$ = new_node;
                                                            }
    ;

Parameters: ID Type ParametersRep                          {$$ = NULL;}
    ;

ParametersRep:                                              {$$ = NULL;}
    | ParametersRep COMMA ID Type                           {$$ = NULL;}
    ;

FuncBody: LBRACE VarsAndStatements RBRACE                   {$$ = add_ast_list(create_new_node("FuncBody", NULL), $2);}
    | LBRACE RBRACE                                         {$$ = create_new_node("FuncBody", NULL);}
    ;

VarsAndStatements: VarDeclaration SEMICOLON                 {$$ = $1;}
    | Statement SEMICOLON                                   {$$ = $1;}
    | VarsAndStatements SEMICOLON                           {$$ = NULL;}
    | VarsAndStatements VarDeclaration SEMICOLON            {$$ = NULL;}
    | VarsAndStatements Statement SEMICOLON                 {$$ = NULL;}
    ;

Statement: ID ASSIGN Expr                                   {$$ = NULL;}
    | LBRACE StatementRep RBRACE                            {$$ = NULL;}
    | IF Expr LBRACE StatementRep RBRACE ElseCond           {$$ = NULL;}
    | FOR LBRACE StatementRep RBRACE                        {$$ = NULL;}
    | FOR LBRACE StatementRep RESERVED SEMICOLON RBRACE     {$$ = NULL;}
    | FOR Expr LBRACE StatementRep RBRACE                   {$$ = NULL;}
    | FOR Expr LBRACE StatementRep RESERVED SEMICOLON RBRACE {$$ = NULL;}
    | RETURN Expr                                           {$$ = NULL;}
    | RETURN                                                {$$ = NULL;}
    | FuncInvocation                                        {$$ = NULL;}
    | ParseArgs                                             {$$ = NULL;}
    | PRINT LPAR Expr RPAR                                  {$$ = NULL;}
    | PRINT LPAR STRLIT RPAR                                {$$ = NULL;}
    | error                                                 {$$ = NULL;}
    ;

StatementRep:                                               {$$ = NULL;}
    | StatementRep Statement SEMICOLON                     {$$ = NULL;}
    ;

ElseCond:                                                   {$$ = NULL;}
    | ELSE LBRACE StatementRep RBRACE                       {$$ = NULL;}
    ;

ParseArgs: ID COMMA BLANKID ASSIGN PARSEINT LPAR CMDARGS LSQ Expr RSQ RPAR  {$$ = NULL;}
    | ID COMMA BLANKID ASSIGN PARSEINT LPAR error RPAR                      {$$ = NULL;}
    ;

FuncInvocation: ID LPAR RPAR                                {$$ = NULL;}
    | ID LPAR FuncInvocationExpr RPAR                       {$$ = NULL;}
    | ID LPAR error RPAR                                    {$$ = NULL;}
    ;

FuncInvocationExpr: Expr                                    {$$ = NULL;}
    | Expr COMMA FuncInvocationExpr                         {$$ = NULL;}
    ;

Expr: Expr OR Expr                                          {$$ = NULL;}
    | Expr AND Expr                                         {$$ = NULL;}
    | NOT Expr                                              {$$ = NULL;}
    | Expr LT Expr                                          {$$ = NULL;}
    | Expr GT Expr                                          {$$ = NULL;}
    | Expr EQ Expr                                          {$$ = NULL;}
    | Expr NE Expr                                          {$$ = NULL;}
    | Expr LE Expr                                          {$$ = NULL;}
    | Expr GE Expr                                          {$$ = NULL;}
    | Expr PLUS Expr                                        {$$ = NULL;}
    | Expr MINUS Expr                                       {$$ = NULL;}
    | Expr STAR Expr                                        {$$ = NULL;}
    | Expr DIV Expr                                         {$$ = NULL;}
    | Expr MOD Expr                                         {$$ = NULL;}
    | PLUS Expr                                             {$$ = NULL;}
    | MINUS Expr                                            {$$ = NULL;}
    | INTLIT                                                {$$ = NULL;}
    | REALLIT                                               {$$ = NULL;}
    | ID                                                    {$$ = NULL;}
    | FuncInvocation                                        {$$ = NULL;}
    | LPAR Expr RPAR                                        {$$ = NULL;}
    | LPAR error RPAR                                       {$$ = NULL;}
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
        //printf("Parent: %s | Child: %s\n", parent->id, child->id);
        parent->children[parent->num_children] = child;
        parent->num_children += 1;

        return parent;
    }

    return NULL;
}

ast_node *add_ast_list(ast_node *parent, ast_node *head){
    if (parent != NULL && head!=NULL){
        ast_node *current = head;
        /*Assuming head is head node of a linked list (always one child as children[0])*/
        for (; current->children[0] != NULL; current = current->children[0]){
            if (strcmp("empty", current->name)!=0 && strcmp("root", current->name)!=0){ //If node name is not "empty" and not "root"
                parent->children[parent->num_children] = malloc(sizeof(struct ast_node));
                copy_ast_data(parent->children[parent->num_children], current);
                parent->num_children += 1;
            }
        }

        /*Free children's childs*/
        free_ast_tree(head);

        return parent;
    }

    return NULL;
}

void copy_ast_data(ast_node *dest, ast_node *src){
    if (dest != NULL && src != NULL){
        strcpy(dest->name, src->name);
        if (strcmp(src->id, "")!=0) strcpy(dest->id, src->id);
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
    if (root==NULL) return;
    //Iterate over all children
    for (int i=0; i< root->num_children; i++){
        free_ast_tree(root->children[i]);
    }

    //Free memory
    free(root);
}

int main(int argc, char** argv) {
    //int yydebug;
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