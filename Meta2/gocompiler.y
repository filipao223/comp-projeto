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
        char type[MAX_AST_NODE_NAME];
        struct ast_node *parent;
        struct ast_node *children[MAX_AST_NODE_CHILDREN];
        int num_children;
    } ast_node;

    //AST functions
    ast_node *create_new_node(char name[], char id[]);
    ast_node *create_new_node_param(char name[], char id[], char type[]);
    ast_node *add_ast_node(ast_node *parent, ast_node *child);
    ast_node *add_ast_list(ast_node *parent, ast_node *head);
    ast_node *append_list(ast_node *parent, ast_node *root_node);
    void copy_ast_data(ast_node *dest, ast_node *src);
    void copy_ast_children(ast_node *dest, ast_node *src);
    void fix_indentation(ast_node *parent, ast_node *child);
    void print_ast_tree(ast_node *root, int level);
    void free_ast_tree(ast_node* root);

    //AST root node
    ast_node *root = NULL;
    //AST current node
    ast_node *current = NULL;
%}

//Tokens
%token <int_value> INTLIT
%token <float_value> REALLIT
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
%token <str> STRLIT

%left OR
%left AND
%right NOT
%left LT GT EQ NE LE GE 
%left FUNC VAR
%right PLUS MINUS
%left STAR DIV MOD
%left LPAR RPAR

%type <node> Expr Program Declarations DeclarationsRep VarDeclaration VarSpec VarSpecRep FuncDeclaration Parameters ParametersRep FuncBody
%type <node> VarsAndStatements Statement StatementRep ElseCond ParseArgs FuncInvocation FuncInvocationExpr
%type <str> Type

%union{
    char *str;
    int int_value;
    double float_value;
    struct ast_node *node;
}

%start Program

%%

Program: PACKAGE ID SEMICOLON Declarations                  {
                                                                root = append_list(create_new_node("Program", NULL), $4);
                                                                root = root==NULL ? create_new_node("Program", NULL):root;
                                                            }
    ;

Declarations:                                               {$$ = NULL;}
    | DeclarationsRep                                       {$$ = $1;}
    ;

DeclarationsRep: DeclarationsRep VarDeclaration SEMICOLON   {
                                                                
                                                                $$ = append_list($1, $2);

                                                            }
    | DeclarationsRep FuncDeclaration SEMICOLON             {
                                                                $$ = append_list($1, $2);
                                                            }
    | VarDeclaration SEMICOLON                              {$$ = $1;}
    | FuncDeclaration SEMICOLON                             {$$ = $1;}
    ;

VarDeclaration: VAR VarSpec                                 {   
                                                                //ast_node* temp_root = create_new_node("root", NULL);
                                                                //ast_node *linked_list = add_ast_node(temp_root, $2);
                                                                $$ = $2;
                                                                //$$ = linked_list;
                                                            }
    | VAR LPAR VarSpec SEMICOLON RPAR                       {$$ = $3;}
    ;

VarSpec: ID VarSpecRep Type                                 {
                                                                ast_node* id_node = create_new_node("Id", $1);
                                                                ast_node *type_node = create_new_node($3, NULL);
                                                                //Get list of vars
                                                                ast_node *list = $2;
                                                                ast_node *current;
                                                                ast_node *list_ids = create_new_node("root", NULL);
                                                                ast_node *vardecl = create_new_node("VarDecl", NULL);
                                                                add_ast_node(vardecl, type_node); add_ast_node(vardecl, id_node);
                                                                add_ast_node(list_ids, vardecl);
                                                                for (current = list; current != NULL; current = current->children[0]){
                                                                    if (strcmp(current->name, "empty")==0) continue;
                                                                    //Create VarDecl node
                                                                    vardecl = create_new_node("VarDecl", NULL);
                                                                    //Add id and type
                                                                    add_ast_node(vardecl, create_new_node($3, NULL));
                                                                    vardecl->children[vardecl->num_children] = create_new_node("empty", NULL);
                                                                    copy_ast_data(vardecl->children[vardecl->num_children], current);
                                                                    vardecl->num_children += 1;
                                                                    //Add to the list
                                                                    list_ids->children[list_ids->num_children] = vardecl;
                                                                    list_ids->num_children+=1;
                                                                }
                                                                $$ = list_ids;
                                                            }
    ;

VarSpecRep:                                                 {$$ = NULL;}
    | VarSpecRep COMMA ID                                   {$$ = add_ast_node(create_new_node("Id", $3), $1);}
    ; 

Type: INT                                                   {$$ = "Int";}
    | FLOAT32                                               {$$ = "Float32";}
    | BOOL                                                  {$$ = "Bool";}
    | STRINGVAR                                             {$$ = "String";}
    ;

FuncDeclaration: FUNC ID LPAR RPAR Type FuncBody            { 
                                                                ast_node* new_node = create_new_node("FuncDecl", NULL);
                                                                ast_node *funcheader = create_new_node("FuncHeader", NULL);
                                                                add_ast_node(funcheader, create_new_node("ID", $2));
                                                                add_ast_node(funcheader, create_new_node($5, NULL));
                                                                add_ast_node(new_node, funcheader);
                                                                add_ast_node(new_node, $6);
                                                                /*Check if funcbody has children*/
                                                                /*if (new_node->children[1] != NULL && new_node->children[1]->num_children != 0){
                                                                    add_ast_node(new_node, create_new_node("FuncBody", NULL));
                                                                }*/
                                                                $$ = add_ast_node(create_new_node("root", NULL), new_node);
                                                                //$$ = new_node;
                                                            }
    | FUNC ID LPAR Parameters RPAR FuncBody                 {
                                                                ast_node* new_node = create_new_node("FuncDecl", NULL);
                                                                ast_node* funcHeader =  create_new_node("FuncHeader", NULL);
                                                                ast_node* funcParams = create_new_node("FuncParams", NULL);

                                                                add_ast_node(funcHeader, create_new_node("Id", $2));
                                                                //add_ast_node(funcHeader, create_new_node("FuncParams", NULL));
                                                                append_list(funcParams, $4);
                                                                add_ast_node(funcHeader, funcParams);
                                                                add_ast_node(new_node, funcHeader);
                                                                add_ast_node(new_node, $6);
                                                                /*Check if funcbody has children*/
                                                                /*if (new_node->children[1] != NULL && new_node->children[1]->num_children != 0){
                                                                    add_ast_node(new_node, create_new_node("FuncBody", NULL));
                                                                }*/
                                                                $$ = add_ast_node(create_new_node("root", NULL), new_node);
                                                            }
    | FUNC ID LPAR Parameters RPAR Type FuncBody            {
                                                                ast_node* new_node = create_new_node("FuncDecl", NULL);
                                                                ast_node* funcHeader =  create_new_node("FuncHeader", NULL);
                                                                ast_node* funcParams = create_new_node("FuncParams", NULL);

                                                                add_ast_node(funcHeader, create_new_node("Id", $2));
                                                                add_ast_node(funcHeader, create_new_node($6, NULL));
                                                                //add_ast_node(funcHeader, create_new_node("FuncParams", NULL));
                                                                append_list(funcParams, $4);
                                                                add_ast_node(funcHeader, funcParams);
                                                                add_ast_node(new_node, funcHeader);
                                                                add_ast_node(new_node, $7);
                                                                /*Check if funcbody has children*/
                                                                /*if (new_node->children[1] != NULL && new_node->children[1]->num_children != 0){
                                                                    add_ast_node(new_node, create_new_node("FuncBody", NULL));
                                                                }*/
                                                                $$ = add_ast_node(create_new_node("root", NULL), new_node);
                                                            }
    | FUNC ID LPAR RPAR FuncBody                            { 
                                                                ast_node* new_node = create_new_node("FuncDecl", NULL);
                                                                ast_node* funcHeader =  create_new_node("FuncHeader", NULL);
                                                                add_ast_node(funcHeader, create_new_node("Id", $2));
                                                                add_ast_node(funcHeader, create_new_node("FuncParams", NULL));
                                                                add_ast_node(new_node, funcHeader);
                                                                add_ast_node(new_node, $5);
                                                                /*Check if funcbody has children*/
                                                                /*if (new_node->children[1] != NULL && new_node->children[1]->num_children != 0){
                                                                    add_ast_node(new_node, create_new_node("FuncBody", NULL));
                                                                }*/
                                                                $$ = add_ast_node(create_new_node("root", NULL), new_node);
                                                                //$$ = new_node;
                                                            }
    ;

Parameters: ID Type ParametersRep                          {
                                                                //Get list of vars
                                                                ast_node* id_node = create_new_node("Id", $1);
                                                                ast_node* type_node = create_new_node($2, NULL);
                                                                ast_node *list = $3;
                                                                ast_node *current;
                                                                ast_node *list_ids = create_new_node("root", NULL);
                                                                /*First parameter*/
                                                                ast_node *paramdecl = create_new_node("ParamDecl", NULL);
                                                                add_ast_node(paramdecl, type_node); add_ast_node(paramdecl, id_node);
                                                                add_ast_node(list_ids, paramdecl);
                                                                for (current = list; current != NULL; current = current->children[0]){
                                                                    if (strcmp(current->name, "empty")==0) continue;
                                                                    //Create ParamDecl node
                                                                    paramdecl = create_new_node("ParamDecl", NULL);
                                                                    //Add id and type
                                                                    add_ast_node(paramdecl, create_new_node(current->type, NULL)); //Add var type
                                                                    paramdecl->children[paramdecl->num_children] = create_new_node("empty", NULL);
                                                                    copy_ast_data(paramdecl->children[paramdecl->num_children], current);
                                                                    paramdecl->num_children += 1;
                                                                    //Add to the list
                                                                    list_ids->children[list_ids->num_children] = paramdecl;
                                                                    list_ids->num_children+=1;
                                                                }
                                                                $$ = list_ids;
                                                            }
    ;

ParametersRep:                                              {$$ = NULL;}
    | ParametersRep COMMA ID Type                           {$$ = add_ast_node($1, create_new_node_param("Id", $3, $4));}
    ;

FuncBody: LBRACE VarsAndStatements RBRACE                   {
                                                                //printf("came out\n");
                                                                //print_ast_tree($2,0);
                                                                ast_node* vars_stmt = $2;
                                                                ast_node* node;
                                                                /*Check if list starts with 'root' node*/
                                                                if (vars_stmt != NULL && strcmp(vars_stmt->name, "If")==0){
                                                                    node = add_ast_node(create_new_node("FuncBody", NULL), $2);
                                                                }
                                                                else{
                                                                    node = append_list(create_new_node("FuncBody", NULL), $2);
                                                                }
                                                                //fix_indentation(node, $2);
                                                                $$ = node;}
    | LBRACE RBRACE                                         {$$ = create_new_node("FuncBody", NULL);}
    ;

VarsAndStatements: VarDeclaration SEMICOLON                 {$$ = $1;}
    | Statement SEMICOLON                                   {$$ = $1;}
    | VarsAndStatements SEMICOLON                           {$$ = $1;}
    | VarsAndStatements VarDeclaration SEMICOLON            {
                                                                ast_node *root = create_new_node("VarDecl", NULL);
                                                                //add_ast_node(root, create_new_node("VarDecl", NULL));
                                                                add_ast_node(root, $1);
                                                                $$ = root;
                                                            }
    | VarsAndStatements Statement SEMICOLON                 {
                                                                //ast_node *root = create_new_node("root", NULL);
                                                                //add_ast_node(root, $2);
                                                                //add_ast_node($1, $2);
                                                                $$ = add_ast_node($1, $2);
                                                            }
    | SEMICOLON                                             {$$ = NULL;}
    ;

Statement: ID ASSIGN Expr                                   {
                                                                ast_node *node = create_new_node("Assign", NULL);
                                                                add_ast_node(node, create_new_node("Id", $1));
                                                                $$ = add_ast_node(node, $3);
                                                            }
    | LBRACE StatementRep RBRACE                            {
                                                                
                                                                
                                                                
                                                                $$ = $2;
                                                            }
    | IF Expr LBRACE StatementRep RBRACE ElseCond           {
                                                                ast_node *if_node = create_new_node("If", NULL);
                                                                add_ast_node(if_node, $2);
                                                                //ast_node *list = $3;
                                                                ast_node *block = append_list(create_new_node("Block", NULL), add_ast_node(create_new_node("root", NULL), $4));
                                                                add_ast_node(if_node, block);
                                                                $$ = if_node;
                                                                //$$ = create_new_node("empty", NULL);
                                                            }
    | FOR LBRACE StatementRep RBRACE                        {$$ = create_new_node("empty", NULL);;}
    | FOR Expr LBRACE StatementRep RBRACE                   {$$ = create_new_node("empty", NULL);;}
    | RETURN Expr                                           {$$ = add_ast_node(create_new_node("Return", NULL), $2);}
    | RETURN                                                {$$ = create_new_node("Return", NULL);}
    | FuncInvocation                                        {$$ = add_ast_list(create_new_node("Call", NULL), $1);}
    | ParseArgs                                             {$$ = add_ast_list(create_new_node("ParseArgs", NULL), $1);}
    | PRINT LPAR Expr RPAR                                  {$$ = add_ast_node(create_new_node("Print", NULL), $3);}
    | PRINT LPAR STRLIT RPAR                                {$$ = add_ast_node(create_new_node("Print", NULL), create_new_node("StrLit", $3));}
    | error                                                 {$$ = create_new_node("error", NULL);}
    ;

StatementRep:                                               {$$ = NULL;}
    | StatementRep Statement SEMICOLON                     {$$ = add_ast_node($2, $1);}
    ;

ElseCond:                                                   {$$ = create_new_node("Block", NULL);}
    | ELSE LBRACE StatementRep RBRACE                       {$$ = append_list(create_new_node("Block", NULL), add_ast_node(create_new_node("root", NULL), $3));}
    ;

ParseArgs: ID COMMA BLANKID ASSIGN PARSEINT LPAR CMDARGS LSQ Expr RSQ RPAR  {
                                                                                //ast_node *root = create_new_node("root", NULL);
                                                                                ast_node *id = create_new_node("Id", $1);
                                                                                //add_ast_node(id, $9);
                                                                                //add_ast_node(root, id);
                                                                                $$ = add_ast_node(id, $9);
                                                                            }
    | ID COMMA BLANKID ASSIGN PARSEINT LPAR error RPAR                      {$$ = create_new_node("error", NULL);}
    ;

FuncInvocation: ID LPAR RPAR                                {$$ = create_new_node("Id", $1);}
    | ID LPAR FuncInvocationExpr RPAR                       {
                                                                ast_node *id = create_new_node("Id", $1);
                                                                //ast_node *root = create_new_node("root", NULL);
                                                                //add_ast_node(id, $3);
                                                                //$$ = add_ast_node(create_new_node("root", NULL), id);
                                                                $$ = add_ast_node(id, $3);
                                                            }
    | ID LPAR error RPAR                                    {$$ = create_new_node("error", NULL);}
    ;

FuncInvocationExpr: Expr                                    {$$ = $1;}
    | Expr COMMA FuncInvocationExpr                         {
                                                                //ast_node *expr_list = add_ast_node(create_new_node("root", NULL), $1);
                                                                //add_ast_node($1, $3);
                                                                $$ = add_ast_node($1, $3);
                                                            }
    ;

Expr: Expr OR Expr                                          {
                                                                ast_node *node = create_new_node("Or", NULL);
                                                                add_ast_node(node, $1);
                                                                add_ast_node(node, $3);
                                                                $$ = node;
                                                            }
    | Expr AND Expr                                         {
                                                                ast_node *node = create_new_node("And", NULL);
                                                                add_ast_node(node, $1);
                                                                add_ast_node(node, $3);
                                                                $$ = node;
                                                            }
    | NOT Expr                                              {$$ = add_ast_node(create_new_node("Not", NULL), $2);}
    | Expr LT Expr                                          {
                                                                ast_node *node = create_new_node("Lt", NULL);
                                                                add_ast_node(node, $1);
                                                                add_ast_node(node, $3);
                                                                $$ = node;
                                                            }
    | Expr GT Expr                                          {
                                                                ast_node *node = create_new_node("Gt", NULL);
                                                                add_ast_node(node, $1);
                                                                add_ast_node(node, $3);
                                                                $$ = node;
                                                            }
    | Expr EQ Expr                                          {
                                                                ast_node *node = create_new_node("Eq", NULL);
                                                                add_ast_node(node, $1);
                                                                add_ast_node(node, $3);
                                                                $$ = node;
                                                            }
    | Expr NE Expr                                          {
                                                                ast_node *node = create_new_node("Ne", NULL);
                                                                add_ast_node(node, $1);
                                                                add_ast_node(node, $3);
                                                                $$ = node;
                                                            }
    | Expr LE Expr                                          {
                                                                ast_node *node = create_new_node("Le", NULL);
                                                                add_ast_node(node, $1);
                                                                add_ast_node(node, $3);
                                                                $$ = node;
                                                            }
    | Expr GE Expr                                          {
                                                                ast_node *node = create_new_node("Ge", NULL);
                                                                add_ast_node(node, $1);
                                                                add_ast_node(node, $3);
                                                                $$ = node;
                                                            }
    | Expr PLUS Expr                                        {
                                                                ast_node *node = create_new_node("Add", NULL);
                                                                add_ast_node(node, $1);
                                                                add_ast_node(node, $3);
                                                                $$ = node;
                                                            }
    | Expr MINUS Expr                                       {
                                                                ast_node *node = create_new_node("Sub", NULL);
                                                                add_ast_node(node, $1);
                                                                add_ast_node(node, $3);
                                                                $$ = node;
                                                            }
    | Expr STAR Expr                                        {
                                                                ast_node *node = create_new_node("Mul", NULL);
                                                                add_ast_node(node, $1);
                                                                add_ast_node(node, $3);
                                                                $$ = node;
                                                            }
    | Expr DIV Expr                                         {
                                                                ast_node *node = create_new_node("Div", NULL);
                                                                add_ast_node(node, $1);
                                                                add_ast_node(node, $3);
                                                                $$ = node;
                                                            }
    | Expr MOD Expr                                         {
                                                                ast_node *node = create_new_node("Mod", NULL);
                                                                add_ast_node(node, $1);
                                                                add_ast_node(node, $3);
                                                                $$ = node;
                                                            }
    | PLUS Expr                                             {$$ = add_ast_node(create_new_node("Plus", NULL), $2);}
    | MINUS Expr                                            {$$ = add_ast_node(create_new_node("Minus", NULL), $2);}
    | INTLIT                                                {sprintf(temp, "%d", $1); $$ = create_new_node("IntLit", temp);}
    | REALLIT                                               {sprintf(temp, "%f", $1); $$ = create_new_node("RealLit", temp);}
    | ID                                                    {$$ = create_new_node("Id", $1);}
    | FuncInvocation                                        {$$ = add_ast_list(create_new_node("Call", NULL), $1);}
    | LPAR Expr RPAR                                        {$$ = $2;}
    | LPAR error RPAR                                       {$$ = create_new_node("error", NULL);}
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



ast_node *create_new_node_param(char name[], char id[], char type[]){
    ast_node *new_node = malloc(sizeof(struct ast_node));
    new_node->num_children = 0;
    if (name == NULL) return NULL; //Name can't be empty
    strcpy(new_node->name, name);

    if (id != NULL) strcpy(new_node->id, id);
    else strcpy(new_node->id, "");

    if (type != NULL) strcpy(new_node->type, type);
    else strcpy(new_node->type, "");

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
    else if(parent != NULL && child == NULL) return parent;

    return NULL;
}





ast_node *add_ast_list(ast_node *parent, ast_node *head){
    if (parent != NULL && head!=NULL){
        ast_node *current = head;
        /*Assuming head is head node of a linked list (always one child as children[0])*/
        for (; current != NULL; current = current->children[0]){
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



ast_node *append_list(ast_node *parent, ast_node *root_node){
    if (parent != NULL && root_node != NULL){
        for(int i=0; i<root_node->num_children; i++){
            ast_node *current = root_node->children[i];
            parent->children[parent->num_children] = create_new_node("empty", NULL);
            copy_ast_data(parent->children[parent->num_children], current);
            copy_ast_children(parent->children[parent->num_children], current);
            parent->num_children += 1;
        }

        return parent;
    }

    return NULL;
}




void fix_indentation(ast_node *parent, ast_node *child){
    if (parent != NULL && child != NULL){
        ast_node *current = child->children[0];

        parent->children[parent->num_children] = current;
        parent->num_children += 1;

        int flag = 0;
        for(int i=0; i<child->num_children; i++){

            if (flag == 1){
                ast_node *node = malloc(sizeof(struct ast_node));
                copy_ast_data(node, current->children[i]);
                copy_ast_children(node, current->children[i]);
                add_ast_node(parent, node);
                flag = 0;
            }
            else if (current->children[i]->num_children == 0 && flag == 0) continue;
            else if(current->children[i]->num_children>0) flag = 1;
            
        }
    }
}




void copy_ast_data(ast_node *dest, ast_node *src){
    if (dest != NULL && src != NULL){
        strcpy(dest->name, src->name);
        if (strcmp(src->id, "")!=0) strcpy(dest->id, src->id);
    }
}




void copy_ast_children(ast_node *dest, ast_node *src){
    if (dest != NULL && src != NULL){
        for (int i=0; i<src->num_children; i++){
            dest->children[dest->num_children] = src->children[i];
            dest->num_children += 1;
        }
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
        if (argc == 3 && strcmp(argv[2], "-d")==0) print_tokens=0;
    }

    if (lex_only==1){
        while(yylex()){} //Print only lex output
    }
    else{
        print_tokens=0; //Dont print lex output | Set lex file print_tokens flag as 0
        yyparse();
        if (print_tree==1) print_ast_tree(root, 0);
        free_ast_tree(root);
    }
    return 0;
} 