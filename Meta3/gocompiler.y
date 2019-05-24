%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <math.h>

    #include "structs.h"
    #include "semantic.h"
    #include "ast.h"


    #define NSYMS 100
    #define YYDEBUG 0

    #define _id_ "Id"
    #define _func_params_ "FuncParams"

    int yydebug=1;
    int i;


    int yylex(void);
    extern int print_tokens;
    extern void yyerror(const char *s);
    extern int total_lines, total_columns;
    extern char *yytext;

    char temp[MAX_TEMP];

    //AST root node
    ast_node *root = NULL;
    //AST current node
    ast_node *current = NULL;

    //Helper list (to store params, ...)
    List *util_list = NULL;
    //Char* to hold current VarDecl type (to use a similar function as ParamDecl append)
    char *current_vardecl_type;

    //Symbol table head node
    Symbol_table *head = NULL;
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
%left ADD SUB
%left STAR DIV MOD MUL
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
                                                                root = append_list(create_new_node("Program", NULL, total_lines, total_columns-strlen(yytext)), $4);
                                                                root = root==NULL ? create_new_node("Program", NULL, total_lines, total_columns-strlen(yytext)):root;
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
                                                                $$ = $2;
                                                            }
    | VAR LPAR VarSpec SEMICOLON RPAR                       {$$ = $3;}
    ;

VarSpec: ID VarSpecRep Type                                 {
                                                                //Build first parameter
                                                                ast_node *first = create_new_node("VarDecl", NULL, total_lines, total_columns-strlen(yytext));
                                                                add_ast_node(first, create_new_node($3, NULL, total_lines, total_columns-strlen(yytext)));
                                                                add_ast_node(first, create_new_node("Id", $1, total_lines, total_columns-strlen(yytext)));

                                                                //Store current vardecl type
                                                                strcpy(current_vardecl_type, $3);

                                                                //Append the other parameters
                                                                ast_node *root = create_new_node("root", NULL, total_lines, total_columns-strlen(yytext));
                                                                add_ast_node(root, first);
                                                                for (List* current = util_list->next; current !=NULL; current = current->next){
                                                                    ast_node *new_node = create_new_node("VarDecl", NULL, total_lines, total_columns-strlen(yytext));
                                                                    add_ast_node(new_node, create_new_node($3, NULL, total_lines, total_columns-strlen(yytext)));
                                                                    add_ast_node(new_node, create_new_node("Id", current->name, total_lines, total_columns-strlen(yytext)));
                                                                    add_ast_node(root, new_node);
                                                                }

                                                                /*Free the list*/
                                                                List *next = util_list->next;
                                                                for (List *current = util_list->next; current != NULL; current = next){
                                                                    next = current->next;
                                                                    free(current);
                                                                }

                                                                /*Reinit, for next FuncDecl (or VarDecl inside function)*/
                                                                util_list = malloc(sizeof(struct list));
                                                                util_list->next = NULL;

                                                                $$ = root;
                                                            }
    ;

VarSpecRep:                                                 {$$ = NULL;}
    | VarSpecRep COMMA ID                                   {
                                                                /*Same method as paramdecl*/
                                                                insert_paramdecl(util_list, $3, "nothing");
                                                            }
    ; 

Type: INT                                                   {$$ = "Int";}
    | FLOAT32                                               {$$ = "Float32";}
    | BOOL                                                  {$$ = "Bool";}
    | STRINGVAR                                             {$$ = "String";}
    ;

FuncDeclaration: FUNC ID LPAR RPAR Type FuncBody            { 
                                                                ast_node* new_node = create_new_node("FuncDecl", NULL, total_lines, total_columns-strlen(yytext));
                                                                ast_node *funcheader = create_new_node("FuncHeader", NULL, total_lines, total_columns-strlen(yytext));
                                                                ast_node* funcParams = create_new_node("FuncParams", NULL, total_lines, total_columns-strlen(yytext));
                                                                add_ast_node(funcheader, create_new_node("Id", $2, total_lines, total_columns-strlen(yytext)));
                                                                add_ast_node(funcheader, create_new_node($5, NULL, total_lines, total_columns-strlen(yytext)));
                                                                add_ast_node(funcheader, funcParams);
                                                                add_ast_node(new_node, funcheader);
                                                                add_ast_node(new_node, $6);
                                                                $$ = add_ast_node(create_new_node("root", NULL, total_lines, total_columns-strlen(yytext)), new_node);
                                                            }
    | FUNC ID LPAR Parameters RPAR FuncBody                 {
                                                                ast_node* new_node = create_new_node("FuncDecl", NULL, total_lines, total_columns-strlen(yytext));
                                                                ast_node* funcHeader =  create_new_node("FuncHeader", NULL, total_lines, total_columns-strlen(yytext));
                                                                ast_node* funcParams = create_new_node("FuncParams", NULL, total_lines, total_columns-strlen(yytext));

                                                                add_ast_node(funcHeader, create_new_node("Id", $2, total_lines, total_columns-strlen(yytext)));
                                                                append_list(funcParams, $4);
                                                                add_ast_node(funcHeader, funcParams);
                                                                add_ast_node(new_node, funcHeader);
                                                                add_ast_node(new_node, $6);
                                                                $$ = add_ast_node(create_new_node("root", NULL, total_lines, total_columns-strlen(yytext)), new_node);
                                                            }
    | FUNC ID LPAR Parameters RPAR Type FuncBody            {
                                                                ast_node* new_node = create_new_node("FuncDecl", NULL, total_lines, total_columns-strlen(yytext));
                                                                ast_node* funcHeader =  create_new_node("FuncHeader", NULL, total_lines, total_columns-strlen(yytext));
                                                                ast_node* funcParams = create_new_node("FuncParams", NULL, total_lines, total_columns-strlen(yytext));

                                                                add_ast_node(funcHeader, create_new_node("Id", $2, total_lines, total_columns-strlen(yytext)));
                                                                add_ast_node(funcHeader, create_new_node($6, NULL, total_lines, total_columns-strlen(yytext)));
                                                                append_list(funcParams, $4);
                                                                add_ast_node(funcHeader, funcParams);
                                                                add_ast_node(new_node, funcHeader);
                                                                add_ast_node(new_node, $7);
                                                                $$ = add_ast_node(create_new_node("root", NULL, total_lines, total_columns-strlen(yytext)), new_node);
                                                            }
    | FUNC ID LPAR RPAR FuncBody                            { 
                                                                ast_node* new_node = create_new_node("FuncDecl", NULL, total_lines, total_columns-strlen(yytext));
                                                                ast_node* funcHeader =  create_new_node("FuncHeader", NULL, total_lines, total_columns-strlen(yytext));
                                                                add_ast_node(funcHeader, create_new_node("Id", $2, total_lines, total_columns-strlen(yytext)));
                                                                add_ast_node(funcHeader, create_new_node("FuncParams", NULL, total_lines, total_columns-strlen(yytext)));
                                                                add_ast_node(new_node, funcHeader);
                                                                add_ast_node(new_node, $5);
                                                                $$ = add_ast_node(create_new_node("root", NULL, total_lines, total_columns-strlen(yytext)), new_node);
                                                            }
    ;

Parameters: ID Type ParametersRep                          {
                                                                //Build first parameter
                                                                ast_node *first = create_new_node("ParamDecl", NULL, total_lines, total_columns-strlen(yytext));
                                                                add_ast_node(first, create_new_node($2, NULL, total_lines, total_columns-strlen(yytext)));
                                                                add_ast_node(first, create_new_node("Id", $1, total_lines, total_columns-strlen(yytext)));

                                                                //Append the other parameters
                                                                ast_node *root = create_new_node("root", NULL, total_lines, total_columns-strlen(yytext));
                                                                add_ast_node(root, first);
                                                                for (List* current = util_list->next; current !=NULL; current = current->next){
                                                                    ast_node *new_node = create_new_node("ParamDecl", NULL, total_lines, total_columns-strlen(yytext));
                                                                    add_ast_node(new_node, create_new_node(current->type, NULL, total_lines, total_columns-strlen(yytext)));
                                                                    add_ast_node(new_node, create_new_node("Id", current->name, total_lines, total_columns-strlen(yytext)));
                                                                    add_ast_node(root, new_node);
                                                                }

                                                                /*Free the list*/
                                                                List *next = util_list->next;
                                                                for (List *current = util_list->next; current != NULL; current = next){
                                                                    next = current->next;
                                                                    free(current);
                                                                }

                                                                /*Reinit, for next FuncDecl (or VarDecl inside function)*/
                                                                util_list = malloc(sizeof(struct list));
                                                                util_list->next = NULL;

                                                                $$ = root;
                                                            }
    ;

ParametersRep:                                              {$$ = NULL;}
    | ParametersRep COMMA ID Type                           {
                                                                //Store this param's name and type
                                                                insert_paramdecl(util_list, $3, $4);
                                                            }
    ;

FuncBody: LBRACE VarsAndStatements RBRACE                   {
                                                                ast_node* vars_stmt = $2;
                                                                ast_node* node;
                                                                /*Check if list starts with a statement or vardecl node*/
                                                                if (vars_stmt != NULL
                                                                    && (strcmp(vars_stmt->name, "If")==0
                                                                        || strcmp(vars_stmt->name, "For")==0
                                                                        || strcmp(vars_stmt->name, "Return")==0
                                                                        || strcmp(vars_stmt->name, "Id")==0
                                                                        || strcmp(vars_stmt->name, "Call")==0
                                                                        || strcmp(vars_stmt->name, "ParseArgs")==0
                                                                        || strcmp(vars_stmt->name, "Print")==0
                                                                        || strcmp(vars_stmt->name, "Assign")==0
                                                                        || strcmp(vars_stmt->name, "Block")==0
                                                                        || strcmp(vars_stmt->name,"VarDecl")==0
                                                                        )
                                                                    )
                                                                {
                                                                    //printf("Not a list\n");
                                                                    node = add_ast_node(create_new_node("FuncBody", NULL, total_lines, total_columns-strlen(yytext)), $2);
                                                                }
                                                                else{
                                                                    //printf("It's a list\n");
                                                                    //printf("List contains:\n");
                                                                    //print_ast_tree($2, 0);
                                                                    node = append_list(create_new_node("FuncBody", NULL, total_lines, total_columns-strlen(yytext)), $2);
                                                                }
                                                                $$ = node;}
    | LBRACE RBRACE                                         {$$ = create_new_node("FuncBody", NULL, total_lines, total_columns-strlen(yytext));}
    ;

VarsAndStatements: VarDeclaration SEMICOLON                 {$$ = $1;}
    | Statement SEMICOLON                                   {$$ = $1;}
    | VarsAndStatements SEMICOLON                           {$$ = $1;}
    | VarsAndStatements VarDeclaration SEMICOLON            {
                                                                //ast_node *root = add_ast_node(create_new_node("root", NULL, total_lines, total_columns-strlen(yytext)), $2);
                                                                append_list($2, $1);
                                                                $$ = $2;
                                                            }
    | VarsAndStatements Statement SEMICOLON                 {
                                                                ast_node *root = create_new_node("root", NULL, total_lines, total_columns-strlen(yytext));
                                                                ast_node* list = $1;
                                                                if (list != NULL && strcmp(list->name, "root")==0){
                                                                    append_list(root, $1);
                                                                }
                                                                else add_ast_node(root, list);
                                                                if ($2 == NULL) $$ = NULL;
                                                                else $$ = add_ast_node(root, $2);
                                                                
                                                                //$$ = root;
                                                            }
    | SEMICOLON                                             {$$ = NULL;}
    ;

Statement: ID ASSIGN Expr                                   {
                                                                ast_node *node = create_new_node("Assign", NULL, total_lines, total_columns-strlen(yytext));
                                                                add_ast_node(node, create_new_node("Id", $1, total_lines, total_columns-strlen(yytext)));
                                                                $$ = add_ast_node(node, $3);
                                                            }
    | LBRACE StatementRep RBRACE                            {
                                                                ast_node *list = add_ast_node(create_new_node("root", NULL, total_lines, total_columns-strlen(yytext)), $2);
                                                                if ($2!=NULL){
                                                                    /*List is in format: child1
                                                                                     ..child1_child1
                                                                                     ..next
                                                                                     ..child2
                                                                                     ....chiild2_child1
                                                                                     ..child3
                                                                                     ....child3_child1
                                                                    Fix this, set children after 'next' as children of parent node*/
                                                                    ast_node* new_list = create_new_node("root", NULL, total_lines, total_columns-strlen(yytext));
                                                                    ast_node *current = list->children[0]->children[0];
                                                                    i=0;

                                                                    //Copy first children of the list
                                                                    ast_node *first_child = create_new_node("new", NULL, total_lines, total_columns-strlen(yytext));
                                                                    copy_ast_data(first_child, list->children[0]);

                                                                    /*Find 'next' node*/
                                                                    for (i=0; current!=NULL ;){
                                                                        if (strcmp(current->name, "next")==0){
                                                                            break;
                                                                        }

                                                                        ast_node *new_node = create_new_node("new", NULL, total_lines, total_columns-strlen(yytext));
                                                                        copy_ast_data(new_node, current); copy_ast_children(new_node, current);
                                                                        add_ast_node(first_child, new_node);

                                                                        i+=1;
                                                                        current = list->children[0]->children[i];
                                                                    }

                                                                    add_ast_node(new_list, first_child);

                                                                    /*If next was found*/
                                                                    if (current!=NULL && strcmp(current->name, "next")==0){
                                                                        current = list->children[0]->children[i+1]; //Node after 'next'
                                                                        for (; current!=NULL; ){

                                                                            ast_node *new_node = create_new_node("new", NULL, total_lines, total_columns-strlen(yytext));
                                                                            copy_ast_data(new_node, current); copy_ast_children(new_node, current);
                                                                            add_ast_node(new_list, new_node);

                                                                            i+=1;
                                                                            current=list->children[0]->children[i+1];
                                                                        }

                                                                        if (new_list->children[0] != NULL && new_list->num_children>1){
                                                                            ast_node* block = append_list(create_new_node("Block", NULL, total_lines, total_columns-strlen(yytext)), new_list);
                                                                            $$ = block;
                                                                        }
                                                                        else $$ = new_list;
                                                                    }
                                                                    else{
                                                                        if (list->children[0] != NULL && list->children[0]->num_children>1){
                                                                            ast_node* block = append_list(create_new_node("Block", NULL, total_lines, total_columns-strlen(yytext)), list);
                                                                            $$ = block;
                                                                        }
                                                                        else $$ = list;
                                                                    }
                                                                }
                                                                else $$ = NULL;
                                                                
                                                            }
    | IF Expr LBRACE StatementRep RBRACE ElseCond           {
                                                                ast_node *if_node = create_new_node("If", NULL, total_lines, total_columns-strlen(yytext));
                                                                add_ast_node(if_node, $2);
                                                                
                                                                ast_node *block = NULL;
                                                                ast_node *list = add_ast_node(create_new_node("root", NULL, total_lines, total_columns-strlen(yytext)), $4);
                                                                
                                                                if ($4!=NULL){
                                                                    /*List is in format: child1
                                                                                     ..child1_child1
                                                                                     ..next
                                                                                     ..child2
                                                                                     ....chiild2_child1
                                                                                     ..child3
                                                                                     ....child3_child1
                                                                    Fix this, set children after 'next' as children of parent node*/
                                                                    ast_node* new_list = create_new_node("root", NULL, total_lines, total_columns-strlen(yytext));
                                                                    ast_node *current = list->children[0]->children[0];
                                                                    i=0;

                                                                    //Copy first children of the list
                                                                    ast_node *first_child = create_new_node("new", NULL, total_lines, total_columns-strlen(yytext));
                                                                    copy_ast_data(first_child, list->children[0]);

                                                                    /*Find 'next' node*/
                                                                    for (i=0; current!=NULL ;){
                                                                        if (strcmp(current->name, "next")==0){
                                                                            break;
                                                                        }

                                                                        ast_node *new_node = create_new_node("new", NULL, total_lines, total_columns-strlen(yytext));
                                                                        copy_ast_data(new_node, current); copy_ast_children(new_node, current);
                                                                        add_ast_node(first_child, new_node);

                                                                        i+=1;
                                                                        current = list->children[0]->children[i];
                                                                    }

                                                                    add_ast_node(new_list, first_child);

                                                                    /*If next was found*/
                                                                    if (current!=NULL && strcmp(current->name, "next")==0){
                                                                        current = list->children[0]->children[i+1]; //Node after 'next'
                                                                        for (; current!=NULL; ){

                                                                            ast_node *new_node = create_new_node("new", NULL, total_lines, total_columns-strlen(yytext));
                                                                            copy_ast_data(new_node, current); copy_ast_children(new_node, current);
                                                                            add_ast_node(new_list, new_node);

                                                                            i+=1;
                                                                            current=list->children[0]->children[i+1];
                                                                        }

                                                                        block = append_list(create_new_node("Block", NULL, total_lines, total_columns-strlen(yytext)), new_list);

                                                                    }
                                                                    else {
                                                                        block = append_list(create_new_node("Block", NULL, total_lines, total_columns-strlen(yytext)), add_ast_node(create_new_node("root", NULL, total_lines, total_columns-strlen(yytext)), $4));
                                                                    }
                                                                }

                                                                if (block==NULL) block = append_list(create_new_node("Block", NULL, total_lines, total_columns-strlen(yytext)), add_ast_node(create_new_node("root", NULL, total_lines, total_columns-strlen(yytext)), $4));
                                                                add_ast_node(if_node, block);
                                                                add_ast_node(if_node, $6);
                                                                $$ = if_node;
                                                            }
    | FOR LBRACE StatementRep RBRACE                        {   
                                                                ast_node *for_node = create_new_node("For", NULL, total_lines, total_columns-strlen(yytext));

                                                                ast_node *block = NULL;
                                                                ast_node *list = add_ast_node(create_new_node("root", NULL, total_lines, total_columns-strlen(yytext)), $3);
                                                                //printf("Reached 2\n");
                                                                
                                                                if ($3!=NULL){
                                                                    /*List is in format: child1
                                                                                     ..child1_child1
                                                                                     ..next
                                                                                     ..child2
                                                                                     ....chiild2_child1
                                                                                     ..child3
                                                                                     ....child3_child1
                                                                    Fix this, set children after 'next' as children of parent node*/
                                                                    ast_node* new_list = create_new_node("root", NULL, total_lines, total_columns-strlen(yytext));
                                                                    ast_node *current = list->children[0]->children[0];
                                                                    i=0;

                                                                    //Copy first children of the list
                                                                    ast_node *first_child = create_new_node("new", NULL, total_lines, total_columns-strlen(yytext));
                                                                    copy_ast_data(first_child, list->children[0]);

                                                                    /*Find 'next' node*/
                                                                    for (i=0; current!=NULL ;){
                                                                        if (strcmp(current->name, "next")==0){
                                                                            break;
                                                                        }

                                                                        ast_node *new_node = create_new_node("new", NULL, total_lines, total_columns-strlen(yytext));
                                                                        copy_ast_data(new_node, current); copy_ast_children(new_node, current);
                                                                        add_ast_node(first_child, new_node);

                                                                        i+=1;
                                                                        current = list->children[0]->children[i];
                                                                    }

                                                                    add_ast_node(new_list, first_child);

                                                                    /*If next was found*/
                                                                    if (current!=NULL && strcmp(current->name, "next")==0){
                                                                        current = list->children[0]->children[i+1]; //Node after 'next'
                                                                        for (; current!=NULL; ){

                                                                            ast_node *new_node = create_new_node("new", NULL, total_lines, total_columns-strlen(yytext));
                                                                            copy_ast_data(new_node, current); copy_ast_children(new_node, current);
                                                                            add_ast_node(new_list, new_node);

                                                                            i+=1;
                                                                            current=list->children[0]->children[i+1];
                                                                        }

                                                                        block = append_list(create_new_node("Block", NULL, total_lines, total_columns-strlen(yytext)), new_list);

                                                                    }
                                                                    else {
                                                                        block = append_list(create_new_node("Block", NULL, total_lines, total_columns-strlen(yytext)), add_ast_node(create_new_node("root", NULL, total_lines, total_columns-strlen(yytext)), $3));
                                                                    }
                                                                }

                                                                if (block==NULL) block = append_list(create_new_node("Block", NULL, total_lines, total_columns-strlen(yytext)), add_ast_node(create_new_node("root", NULL, total_lines, total_columns-strlen(yytext)), $3));
                                                                add_ast_node(for_node, block);
                                                                $$ = for_node;
                                                            }
    | FOR Expr LBRACE StatementRep RBRACE                   {   ast_node *for_node = create_new_node("For", NULL, total_lines, total_columns-strlen(yytext));
                                                                add_ast_node(for_node, $2);
                                                                
                                                                ast_node *block = NULL;
                                                                ast_node *list = add_ast_node(create_new_node("root", NULL, total_lines, total_columns-strlen(yytext)), $4);
                                                                //printf("Reached 2\n");
                                                                
                                                                if ($4!=NULL){
                                                                    /*List is in format: child1
                                                                                     ..child1_child1
                                                                                     ..next
                                                                                     ..child2
                                                                                     ....chiild2_child1
                                                                                     ..child3
                                                                                     ....child3_child1
                                                                    Fix this, set children after 'next' as children of parent node*/
                                                                    ast_node* new_list = create_new_node("root", NULL, total_lines, total_columns-strlen(yytext));
                                                                    ast_node *current = list->children[0]->children[0];
                                                                    i=0;

                                                                    //Copy first children of the list
                                                                    ast_node *first_child = create_new_node("new", NULL, total_lines, total_columns-strlen(yytext));
                                                                    copy_ast_data(first_child, list->children[0]);

                                                                    /*Find 'next' node*/
                                                                    for (i=0; current!=NULL ;){
                                                                        if (strcmp(current->name, "next")==0){
                                                                            break;
                                                                        }

                                                                        ast_node *new_node = create_new_node("new", NULL, total_lines, total_columns-strlen(yytext));
                                                                        copy_ast_data(new_node, current); copy_ast_children(new_node, current);
                                                                        add_ast_node(first_child, new_node);

                                                                        i+=1;
                                                                        current = list->children[0]->children[i];
                                                                    }

                                                                    add_ast_node(new_list, first_child);

                                                                    /*If next was found*/
                                                                    if (current!=NULL && strcmp(current->name, "next")==0){
                                                                        current = list->children[0]->children[i+1]; //Node after 'next'
                                                                        for (; current!=NULL; ){

                                                                            ast_node *new_node = create_new_node("new", NULL, total_lines, total_columns-strlen(yytext));
                                                                            copy_ast_data(new_node, current); copy_ast_children(new_node, current);
                                                                            add_ast_node(new_list, new_node);

                                                                            i+=1;
                                                                            current=list->children[0]->children[i+1];
                                                                        }

                                                                        block = append_list(create_new_node("Block", NULL, total_lines, total_columns-strlen(yytext)), new_list);

                                                                    }
                                                                    else {
                                                                        block = append_list(create_new_node("Block", NULL, total_lines, total_columns-strlen(yytext)), add_ast_node(create_new_node("root", NULL, total_lines, total_columns-strlen(yytext)), $4));
                                                                    }
                                                                }

                                                                if (block==NULL) block = append_list(create_new_node("Block", NULL, total_lines, total_columns-strlen(yytext)), add_ast_node(create_new_node("root", NULL, total_lines, total_columns-strlen(yytext)), $4));

                                                                add_ast_node(for_node, block);
                                                                $$ = for_node;
                                                            }
    | RETURN Expr                                           {$$ = add_ast_node(create_new_node("Return", NULL, total_lines, total_columns-strlen(yytext)), $2);}
    | RETURN                                                {$$ = create_new_node("Return", NULL, total_lines, total_columns-strlen(yytext));}
    | FuncInvocation                                        {
                                                                ast_node *list = $1;
                                                                ast_node* node;
                                                                if (list != NULL && strcmp(list->name, "root")==0){
                                                                    node = append_list(create_new_node("Call", NULL, total_lines, total_columns-strlen(yytext)), list);
                                                                }
                                                                else node = add_ast_node(create_new_node("Call", NULL, total_lines, total_columns-strlen(yytext)), list);
                                                                $$ = node;
                                                            }
    | ParseArgs                                             {$$ = add_ast_list(create_new_node("ParseArgs", NULL, total_lines, total_columns-strlen(yytext)), $1);}
    | PRINT LPAR Expr RPAR                                  {$$ = add_ast_node(create_new_node("Print", NULL, total_lines, total_columns-strlen(yytext)), $3);}
    | PRINT LPAR STRLIT RPAR                                {$$ = add_ast_node(create_new_node("Print", NULL, total_lines, total_columns-strlen(yytext)), create_new_node("StrLit", $3, total_lines, total_columns-strlen(yytext)));}
    | error                                                 {$$ = create_new_node("error", NULL, total_lines, total_columns-strlen(yytext));}
    ;

StatementRep:                                               {$$ = NULL;}
    | StatementRep Statement SEMICOLON                      {
                                                                if ($1==NULL) $$ = $2;
                                                                else{
                                                                    /*If node doesn't yet have a 'next' node*/
                                                                    if ($1->has_next_node!=1){
                                                                        add_ast_node($1, create_new_node("next", NULL, total_lines, total_columns-strlen(yytext)));
                                                                        $1->has_next_node=1;
                                                                    }
                                                                    $$ = add_ast_node($1, $2);
                                                                }
                                                                
                                                            }
    ;

ElseCond:                                                   {$$ = create_new_node("Block", NULL, total_lines, total_columns-strlen(yytext));}
    | ELSE LBRACE StatementRep RBRACE                       {
                                                                ast_node *block = NULL;
                                                                ast_node *list = add_ast_node(create_new_node("root", NULL, total_lines, total_columns-strlen(yytext)), $3);
                                                                //printf("Reached 2\n");
                                                                
                                                                if ($3!=NULL){
                                                                    /*List is in format: child1
                                                                                     ..child1_child1
                                                                                     ..next
                                                                                     ..child2
                                                                                     ....chiild2_child1
                                                                                     ..child3
                                                                                     ....child3_child1
                                                                    Fix this, set children after 'next' as children of parent node*/
                                                                    ast_node* new_list = create_new_node("root", NULL, total_lines, total_columns-strlen(yytext));
                                                                    ast_node *current = list->children[0]->children[0];
                                                                    i=0;

                                                                    //Copy first children of the list
                                                                    ast_node *first_child = create_new_node("new", NULL, total_lines, total_columns-strlen(yytext));
                                                                    copy_ast_data(first_child, list->children[0]);

                                                                    /*Find 'next' node*/
                                                                    for (i=0; current!=NULL ;){
                                                                        if (strcmp(current->name, "next")==0){
                                                                            break;
                                                                        }

                                                                        ast_node *new_node = create_new_node("new", NULL, total_lines, total_columns-strlen(yytext));
                                                                        copy_ast_data(new_node, current); copy_ast_children(new_node, current);
                                                                        add_ast_node(first_child, new_node);

                                                                        i+=1;
                                                                        current = list->children[0]->children[i];
                                                                    }

                                                                    add_ast_node(new_list, first_child);

                                                                    /*If next was found*/
                                                                    if (current!=NULL && strcmp(current->name, "next")==0){
                                                                        current = list->children[0]->children[i+1]; //Node after 'next'
                                                                        for (; current!=NULL; ){

                                                                            ast_node *new_node = create_new_node("new", NULL, total_lines, total_columns-strlen(yytext));
                                                                            copy_ast_data(new_node, current); copy_ast_children(new_node, current);
                                                                            add_ast_node(new_list, new_node);

                                                                            i+=1;
                                                                            current=list->children[0]->children[i+1];
                                                                        }

                                                                        block = append_list(create_new_node("Block", NULL, total_lines, total_columns-strlen(yytext)), new_list);

                                                                    }
                                                                    else {
                                                                        block = append_list(create_new_node("Block", NULL, total_lines, total_columns-strlen(yytext)), add_ast_node(create_new_node("root", NULL, total_lines, total_columns-strlen(yytext)), $3));
                                                                    }
                                                                }

                                                                if (block==NULL) block = append_list(create_new_node("Block", NULL, total_lines, total_columns-strlen(yytext)), add_ast_node(create_new_node("root", NULL, total_lines, total_columns-strlen(yytext)), $3));
                                                                $$ = block;
                                                            }
    ;

ParseArgs: ID COMMA BLANKID ASSIGN PARSEINT LPAR CMDARGS LSQ Expr RSQ RPAR  {
                                                                                ast_node *id = create_new_node("Id", $1, total_lines, total_columns-strlen(yytext));                                                                                
                                                                                $$ = add_ast_node(id, $9);
                                                                            }
    | ID COMMA BLANKID ASSIGN PARSEINT LPAR error RPAR                      {$$ = create_new_node("error", NULL, total_lines, total_columns-strlen(yytext));}
    ;

FuncInvocation: ID LPAR RPAR                                {$$ = create_new_node("Id", $1, total_lines, total_columns-strlen(yytext));}
    | ID LPAR FuncInvocationExpr RPAR                       {
                                                                ast_node *id = create_new_node("Id", $1, total_lines, total_columns-strlen(yytext));
                                                                ast_node *root = create_new_node("root", NULL, total_lines, total_columns-strlen(yytext));
                                                                add_ast_node(root, id);
                                                                add_ast_node(root, $3);

                                                                $$ = root;
                                                            }
    | ID LPAR error RPAR                                    {$$ = create_new_node("error", NULL, total_lines, total_columns-strlen(yytext));}
    ;

FuncInvocationExpr: Expr                                    {$$ = $1;}
    | Expr COMMA FuncInvocationExpr                         {
                                                                $$ = add_ast_node($1, $3);
                                                            }
    ;

Expr: Expr OR Expr                                          {
                                                                ast_node *node = create_new_node("Or", NULL, total_lines, total_columns-strlen(yytext));
                                                                add_ast_node(node, $1);
                                                                add_ast_node(node, $3);
                                                                $$ = node;
                                                            }
    | Expr AND Expr                                         {
                                                                ast_node *node = create_new_node("And", NULL, total_lines, total_columns-strlen(yytext));
                                                                add_ast_node(node, $1);
                                                                add_ast_node(node, $3);
                                                                $$ = node;
                                                            }
    | NOT Expr                                              {$$ = add_ast_node(create_new_node("Not", NULL, total_lines, total_columns-strlen(yytext)), $2);}
    | Expr LT Expr                                          {
                                                                ast_node *node = create_new_node("Lt", NULL, total_lines, total_columns-strlen(yytext));
                                                                add_ast_node(node, $1);
                                                                add_ast_node(node, $3);
                                                                $$ = node;
                                                            }
    | Expr GT Expr                                          {
                                                                ast_node *node = create_new_node("Gt", NULL, total_lines, total_columns-strlen(yytext));
                                                                add_ast_node(node, $1);
                                                                add_ast_node(node, $3);
                                                                $$ = node;
                                                            }
    | Expr EQ Expr                                          {
                                                                ast_node *node = create_new_node("Eq", NULL, total_lines, total_columns-strlen(yytext));
                                                                add_ast_node(node, $1);
                                                                add_ast_node(node, $3);
                                                                $$ = node;
                                                            }
    | Expr NE Expr                                          {
                                                                ast_node *node = create_new_node("Ne", NULL, total_lines, total_columns-strlen(yytext));
                                                                add_ast_node(node, $1);
                                                                add_ast_node(node, $3);
                                                                $$ = node;
                                                            }
    | Expr LE Expr                                          {
                                                                ast_node *node = create_new_node("Le", NULL, total_lines, total_columns-strlen(yytext));
                                                                add_ast_node(node, $1);
                                                                add_ast_node(node, $3);
                                                                $$ = node;
                                                            }
    | Expr GE Expr                                          {
                                                                ast_node *node = create_new_node("Ge", NULL, total_lines, total_columns-strlen(yytext));
                                                                add_ast_node(node, $1);
                                                                add_ast_node(node, $3);
                                                                $$ = node;
                                                            }
    | Expr PLUS Expr                                        {
                                                                ast_node *node = create_new_node("Add", NULL, total_lines, total_columns-strlen(yytext));
                                                                add_ast_node(node, $1);
                                                                add_ast_node(node, $3);
                                                                $$ = node;
                                                            }
    | Expr MINUS Expr                                       {
                                                                ast_node *node = create_new_node("Sub", NULL, total_lines, total_columns-strlen(yytext));
                                                                add_ast_node(node, $1);
                                                                add_ast_node(node, $3);
                                                                $$ = node;
                                                            }
    | Expr STAR Expr                                        {
                                                                ast_node *node = create_new_node("Mul", NULL, total_lines, total_columns-strlen(yytext));
                                                                add_ast_node(node, $1);
                                                                add_ast_node(node, $3);
                                                                $$ = node;
                                                            }
    | Expr DIV Expr                                         {
                                                                ast_node *node = create_new_node("Div", NULL, total_lines, total_columns-strlen(yytext));
                                                                add_ast_node(node, $1);
                                                                add_ast_node(node, $3);
                                                                $$ = node;
                                                            }
    | Expr MOD Expr                                         {
                                                                ast_node *node = create_new_node("Mod", NULL, total_lines, total_columns-strlen(yytext));
                                                                add_ast_node(node, $1);
                                                                add_ast_node(node, $3);
                                                                $$ = node;
                                                            }
    | PLUS Expr                                             {$$ = add_ast_node(create_new_node("Plus", NULL, total_lines, total_columns-strlen(yytext)), $2);}
    | MINUS Expr                                            {$$ = add_ast_node(create_new_node("Minus", NULL, total_lines, total_columns-strlen(yytext)), $2);}
    | INTLIT                                                {sprintf(temp, "%d", $1); $$ = create_new_node("IntLit", temp, total_lines, total_columns-strlen(yytext));}
    | REALLIT                                               {sprintf(temp, "%f", $1); $$ = create_new_node("RealLit", temp, total_lines, total_columns-strlen(yytext));}
    | ID                                                    {$$ = create_new_node("Id", $1, total_lines, total_columns-strlen(yytext));}
    | FuncInvocation                                        {
                                                                ast_node *list = $1;
                                                                ast_node* node;
                                                                if (list != NULL && strcmp(list->name, "root")==0){
                                                                    node = append_list(create_new_node("Call", NULL, total_lines, total_columns-strlen(yytext)), list);
                                                                }
                                                                else node = add_ast_node(create_new_node("Call", NULL, total_lines, total_columns-strlen(yytext)), list);
                                                                $$ = node;
                                                            }
    | LPAR Expr RPAR                                        {$$ = $2;}
    | LPAR error RPAR                                       {$$ = create_new_node("error", NULL, total_lines, total_columns-strlen(yytext));}
    ;

%%   


int main(int argc, char** argv) {
    //int yydebug;
    #if YYDEBUG
        yydebug = 1;
    #endif

    int lex_only = 0;
    int print_tree = 0;
    int print_symbols = 0;

    int error_count=0;

    if (argc!=1){
        if (strcmp(argv[1], "-l")==0) lex_only = 1;
        if (strcmp(argv[1], "-t")==0) print_tree = 1;
        if (strcmp(argv[1], "-s")==0) print_symbols = 1;
        if (argc == 3 && strcmp(argv[2], "-d")==0) print_tokens=0; //For debugging only
    }

    if (lex_only==1){
        while(yylex()){} //Print only lex output
    }
    else{
        print_tokens=0; //Dont print lex output | Set lex file print_tokens flag as 0
        /*Create a new symbol table*/
        head = malloc(sizeof (struct symbol_table));
        strcpy(head->name, "global");
        head->next_table = NULL; head->child = NULL;

        /*Initialize list to hold ParamDecl*/
        util_list = malloc(sizeof(struct list));
        util_list->next = NULL;

        //Malloc string to hold VarDecl type name
        current_vardecl_type = malloc(MAX_AST_NODE_NAME);
        strcpy(current_vardecl_type, "nothing");

        /*Parse*/
        yyparse();

        /*Semantic analysis*/
        if (print_tree==0 && lex_only==0) error_count += check_program_symbols(head, root);

        if (print_tree==1) print_ast_tree(root, 0);
        if (print_symbols==1 && error_count==0){
            print_symbol_table(head);
            print_ast_tree(root, 0);
        }

        free(current_vardecl_type);
        free_ast_tree(root);
        free_symbol_table(head);
    }
    return 0;
} 