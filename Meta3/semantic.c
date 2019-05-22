#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "structs.h"
#include "semantic.h"
#include "y.tab.h"





/*********************************************************************
 * Inserts a new symbol table at the end of the list
 * 
 * Parameters:
 *      *head: Head of the limked list;
 *      name[]: The name of the new table.
 * 
 * Returns:
 *      1 if the table was created, 0 if it already exists.
 * 
 *********************************************************************/
int insert_new_table(Symbol_table* head, char name[], List *param_list){
    /*Find last table*/
    Symbol_table* current = head;
    for (; current->next_table != NULL; current = current->next_table){
        /*Check if the table already exists*/
        if (strcmp(current->name, name)==0) return 0;
    }

    /*Check if the last table already exists*/
    if (strcmp(current->name, name)==0) return 0;

    /*Insert new table*/
    Symbol_table *new_table = malloc(sizeof (struct symbol_table));
    new_table->next_table = NULL; new_table->child = NULL; 
    new_table->param_list = param_list;
    strcpy(new_table->name, name);
    current->next_table = new_table;

    return 1;
}






/******************************************************************************************
 * Inserts a new child on the specified table.
 * 
 * Parameters:
 *      *head: Head of the linked list;
 *      table[]: Name of the table where the symbol will be appended;
 *      name[]: Name of the symbol;
 *      rtype[]: Return type of the symbol;
 *      ptype[]: Parameter type of the symbol;
 *      is_param: If this symbol is a function parameter.
 * 
 * Returns:
 *      -1 if the table wasn't found, 1 if the symbol was appended and 0 if the symbol
 *          was already appended.
 * 
 ******************************************************************************************/
int insert_new_child(Symbol_table *head, char table[], char name[], char ptype[], char rtype[], int is_param){
    /*Find correct table*/
    Symbol_table* current = head;
    for (; current != NULL; current = current->next_table){
        if (strcmp(current->name, table)==0) break;
    }

    /*Check if we found the table*/
    if (current == NULL) return -1; //No table was found

    /*Find the last child*/
    Symbol_node* curr_child = current->child;
    if (curr_child != NULL){
        for (; curr_child->next != NULL; curr_child = curr_child->next){
            /*Check if the symbol already exists*/
            if (strcmp(curr_child->name, name)==0) return 0;
        }

        /*Check if the last symbol already exists*/
        if (strcmp(curr_child->name, name)==0) return 0;
    }

    /*Insert new symbol node*/
    Symbol_node* new_node = malloc(sizeof (struct symbol_node));
    strcpy(new_node->name, name); strcpy(new_node->rtype, rtype); strcpy(new_node->ptype, ptype);
    new_node->is_param = is_param;
    new_node->next = NULL;
    
    if (curr_child != NULL) curr_child->next = new_node;
    else current->child = new_node; 

    return 1;
}






/*********************************************************************
 * Searches the symbol table for a given table name.
 * 
 * Parameters:
 *      *head: Head of the linked list containing the table;
 *      *name: Name of the table to search.
 * 
 * Returns:
 *      The node containing the table if found, NULL if not found.
 * 
 *********************************************************************/
Symbol_table* search_table(Symbol_table *head, char *name){
    Symbol_table *current;
    for (current = head; current != NULL; current = current->next_table){
        if (strcmp(name, current->name)==0) return current;
    }

    return NULL;
}




/*********************************************************************
 * Searches the symbol table for a given symbol name.
 * 
 * Parameters:
 *      *head: Head of the linked list containing the table;
 *      *table: Name of the table that contains the symbol;
 *      *name: Name of the symbol to search.
 * 
 * Returns:
 *      The node containing the symbol if found, NULL if not found.
 * 
 *********************************************************************/
Symbol_node* search_symbol(Symbol_table *head, char *table, char *name){
    Symbol_table *ctable;
    Symbol_node *cnode;

    /*Search table*/
    for(ctable = head; ctable != NULL; ctable = ctable->next_table){
        if (strcmp(table, ctable->name)==0){
            /*Search symbol*/
            for (cnode = ctable->child; cnode != NULL; cnode = cnode->next){
                if (strcmp(name, cnode->name)==0) return cnode;
            }
        }
    }

    return NULL;
}






/*******************************************************************************************
 * Stores a function's parameters, name and type, as a linked list.
 * 
 * Parameters:
 *      *head: The head of the linked list;
 *      *params: 'FuncParams' node of the AST.
 * 
 *******************************************************************************************/
void store_func_params(List *head, ast_node *params){
    ast_node *current;
    List *next_param, *new_param = NULL;

    //printf("Passed node is: %s %s", params->name, params->id);
    //printf("Has %d param\n", params->num_children);

    for (int i=0; i<params->num_children; i++){
        current = params->children[i];

        new_param = malloc( sizeof(struct list));

        /*Store name and type of the parameter*/
        strcpy(new_param->name, current->children[1]->id); strcpy(new_param->type, current->children[0]->name);
        new_param->type[0] = tolower(new_param->type[0]); //Int -> int, Float32 -> float32, ...
        new_param->next = NULL;

        /*Add the parameter to the end of the list*/
        for (next_param = head; next_param->next != NULL; next_param = next_param->next); //Find the last node
        next_param->next = new_param;
    }
}






/*****************************************************************************************************************
 * Checks a single function for any var declarations, to build symbol table.
 * 
 * Parameters:
 *      *head: The head of the linked list where the table will be stored;
 *      *funcdecl: The root node of this function declaration (FuncDecl);
 *      *param_list: Linked list containing parsed function parameters;
 *      rtype[]: Return type of the function;
 *      table_name[]: Name of the function (to use in the symbol table).
 * 
 * Returns:
 *      Number of found semantic errors.
 * 
 *****************************************************************************************************************/
int check_func_symbols(Symbol_table *head, ast_node *funcdecl, List *param_list, char rtype[], char table_name[]){
    List *next_param;
    char type[MAX_AST_NODE_NAME], name[MAX_AST_NODE_NAME];
    int error_count = 0;

    /*Insert return type and parameters in the function table*/
    insert_new_child(head, table_name, "return", "", rtype, 0);
    for (next_param = param_list->next; next_param != NULL; next_param = next_param->next){
        if (insert_new_child(head, table_name, next_param->name, "", next_param->type, 1)==0){
            int line = funcdecl->children[0]->children[0]->line;
            int col = funcdecl->children[0]->children[0]->col;
            semantic_error(SYM_ALREADY_DEFINED, line, col, next_param->name, NULL, NULL);
            error_count++;
        }
    }

    /*Check for variable declarations*/
    ast_node *funcbody = funcdecl->children[1];
    ast_node *current;
    for (int i=0; i<funcbody->num_children; i++){
        current = funcbody->children[i];

        /*Check for VarDecl*/
        if (strcmp(current->name, "VarDecl")==0){
            /*Store type and name*/
            strcpy(type, current->children[0]->name); strcpy(name, current->children[1]->id);
            type[0] = tolower(type[0]); //Int -> int, Float32 -> float32, ...
            if (insert_new_child(head, table_name, name, "", type, 0)==0){
                semantic_error(SYM_ALREADY_DEFINED, current->children[1]->line, current->children[1]->col, name, NULL, NULL);
                error_count++;
            }
        }
    }

    return error_count;
}







/*******************************************************************************************
 * Starts symbol table build.
 * Checks for any var declaration and function declaration, and then checks the functions for
 *  any var declaration.
 * 
 * Parameters:
 *      *head: The head of the linked list where the table will be stored;
 *      *root: Root node of the AST.
 * 
 * Returns:
 *      The number of found semantic errors.
 * 
 *******************************************************************************************/
int check_program_symbols(Symbol_table *head, ast_node *root){
    /*Check if a tree was actually created*/
    if (root==NULL) return -1;

    ast_node *current;
    List *param_list = NULL;
    List *next_param;
    int error_count = 0;
    int index;      //index of children[] of FuncDecl that contains parameters

    char type[MAX_AST_NODE_NAME], name[MAX_AST_NODE_NAME], params[MAX_AST_NODE_NAME*MAX_PARAMS];
    char table_name[MAX_AST_NODE_NAME*MAX_PARAMS];

    /*Check for any variable declarations or functions*/
    for (int i=0; i< root->num_children; i++){
        current = root->children[i];

        /*Check for VarDecl*/
        if (strcmp(current->name,"VarDecl")==0){
            /*Store type and name*/
            strcpy(type, current->children[0]->name); strcpy(name, current->children[1]->id);
            type[0] = tolower(type[0]); //Int -> int, Float32 -> float32, ...
            if (insert_new_child(head, "global", name, "", type, 0)==0){
                semantic_error(SYM_ALREADY_DEFINED, current->children[1]->line, current->children[1]->col, name, NULL, NULL);
                error_count++;
            }
        }

        /*Check for FuncDecl*/
        if (strcmp(current->name, "FuncDecl")==0){
            /*Store type and name*/
            strcpy(type, current->children[0]->children[1]->name); strcpy(name, current->children[0]->children[0]->id);

            /*If type is 'FuncParams', then it has no return type, and FuncParams has index 1*/
            if (strcmp(type, "FuncParams")==0){
                strcpy(type, "none");
                index = 1;
            }
            else index = 2;

            type[0] = tolower(type[0]); //Int -> int, Float32 -> float32, ...

            /*Store function parameters*/
            param_list = malloc( sizeof(struct list)); param_list->next = NULL;
            store_func_params(param_list, current->children[0]->children[index]);


            /*Build parameter type string*/
            strcpy(params, "(");
            if (param_list != NULL){
                //printf("For function %s:\n", name);
                for (next_param = param_list->next; next_param != NULL; next_param = next_param->next){
                    //printf("Param %s\n", next_param->type);
                    strcat(params, next_param->type);
                    if (next_param->next != NULL) strcat(params, ","); //Add ',' if it's not last parameter
                }
            }
            strcat(params, ")");

            /*Insert the function in the global table*/
            if (insert_new_child(head, "global", name, params, type, 0)==0){
                int line = current->children[0]->children[0]->line;
                int col = current->children[0]->children[0]->col;
                semantic_error(SYM_ALREADY_DEFINED, line, col, name, NULL, NULL);
                error_count++;
            }

            /*Also add the new table*/
            strcpy(table_name, name);
            if (insert_new_table(head, table_name, param_list)==0){
                int line = current->children[0]->children[0]->line;
                int col = current->children[0]->children[0]->col;
                semantic_error(SYM_ALREADY_DEFINED, line, col, name, NULL, NULL);
            }

            /*Verify the function body*/
            check_func_symbols(head, current, param_list, type, table_name);
        }
    }

    /*Annotate the AST*/
    annotate_ast(head, root);

    return error_count;
}





/****************************************************************************
 * Travels entire AST and annotates nodes that can be annotated.
 * When a possible node is found, recursive function annotate_node() is called
 *  to annotate any children nodes.
 * 
 * Parameters:
 *      *head: The head of the linked list where the table will be stored;
 *      *root: Root node of the AST (Program).
 * 
 ****************************************************************************/
void annotate_ast(Symbol_table *head, ast_node *root){
    ast_node *current;

    /*Look for function declarations*/
    for (int i=0; i<root->num_children; i++){
        current = root->children[i];

        /*If it's a FuncDecl*/
        if (strcmp(current->name, "FuncDecl")==0){
            /*Get its name*/
            ast_node *func_id = current->children[0]->children[0];

            /*Travel FuncBody*/
            ast_node *funcbody = current->children[1];
            for (int j=0; j<funcbody->num_children; j++){
                current = funcbody->children[j];

                /*Ignore VarDecl*/
                if (strcmp(current->name, "VarDecl")!=0){
                    annotate_node(head, current, func_id->id);
                }
            }
        }
    }
}






/***********************************************************************************************
 * Recursive.
 * Annotates a node, and any chldren nodes it might possess.
 * 
 * Parameters:
 *      *head: The head of the linked list where the table will be stored;
 *      *expr: Node where to start annotating;
 *      *function: Name of the current function.
 * 
 ***********************************************************************************************/
void annotate_node(Symbol_table *head, ast_node *expr, char *function){
    /*While there are children, annotate them*/
    if (expr->num_children>0){
        for (int i=0; i<expr->num_children; i++) annotate_node(head, expr->children[i], function);
    }

    /*Function Call*/
    if (strcmp(expr->name, "Call")==0){
        /*Search the function in the symbol table*/
        Symbol_node *symbol = search_symbol(head, "global", expr->children[0]->id);
        if (symbol==NULL){
            semantic_error(SYM_NOT_FOUND, expr->line, expr->col, expr->children[0]->id, NULL, NULL);
        }
        else{
            /*Annotate with the type*/
            strcpy(expr->note, symbol->rtype);
        }
    }

    /*Id*/
    else if (strcmp(expr->name, "Id")==0){
        /*Search the symbol first as a function*/
        Symbol_table *table = search_table(head, expr->id);
        Symbol_node *symbol = NULL;
        if (table==NULL){
            /*If the table wasnt found, search it in its table*/
            symbol = search_symbol(head, function, expr->id);

            if (symbol==NULL){
                /*If it wasnt found as a local variable, try the global table*/
                symbol = search_symbol(head, "global", expr->id);
            }
        }

        if (table!=NULL){
            /*Annotate with the parameters of the function*/
            /*Build parameter type string*/
            char params[MAX_AST_NODE_NAME*MAX_PARAMS];
            strcpy(params, "(");
            if (table->param_list != NULL){
                for (List* next_param = table->param_list->next; next_param != NULL; next_param = next_param->next){
                    strcat(params, next_param->type);
                    if (next_param->next != NULL) strcat(params, ","); //Add ',' if it's not last parameter
                }
            }
            strcat(params, ")");

            strcpy(expr->note, params);
        }
        else if (symbol!=NULL){
            /*Annotate with symbol type*/
            strcpy(expr->note, symbol->rtype);
        }
        else{
            semantic_error(SYM_NOT_FOUND, expr->line, expr->col, expr->id, NULL, NULL);
        }
    }

    /*Check if is Assign, Add, Sub, Mul or Div*/
    if (strcmp(expr->name, "Assign")==0 || strcmp(expr->name, "Add")==0 || strcmp(expr->name, "Sub")==0
        || strcmp(expr->name, "Mul")==0 || strcmp(expr->name, "Div")==0){
        /*Note is type of first operand*/
        strcpy(expr->note, expr->children[0]->note);
    }
    /*Check if it's GE, GT, LE, LT or EQ*/
    else if (is_expr_bool(expr->name)){
        /*Note is a bool*/
        strcpy(expr->note, "bool");
    }
    /*Check if IntLit, RealLit or StrLit*/
    else if (strcmp(expr->name, "IntLit")==0) strcpy(expr->note, "int");
    else if (strcmp(expr->name, "RealLit")==0) strcpy(expr->note, "float32");
    else if (strcmp(expr->name, "StrLit")==0) strcpy(expr->note, "string");
}






/*********************************************************************************************
 * Checks if the given node name is of a node type that has the boolean type.
 * 
 * Parameters:
 *      *name: Name of the AST node (Ge, Eq, ...).
 * 
 * Returns:
 *      1 if the node has a boolean type, 0 otherwise.
 * 
 *********************************************************************************************/
int is_expr_bool(char *name){
    if ( strcmp(name, "Gt")==0 || strcmp(name, "Ge")==0 || strcmp(name, "Lt")==0
        || strcmp(name, "Le")==0 || strcmp(name, "Eq")==0 || strcmp(name, "Not")==0) return 1;

    return 0;
}







/******************************************************************************
 * Print the symbol table.
 * 
 * Parameters:
 *      *head: Head of the linked list.
 * 
 ******************************************************************************/
void print_symbol_table(Symbol_table *head){
    Symbol_table* current;
    Symbol_node* curr_child;
    List *next_param;
    char params[MAX_AST_NODE_NAME*MAX_PARAMS];

    /*Print the global symbol table*/
    printf("===== Global Symbol Table =====\n");

    /*While we have children to print*/
    for (curr_child = head->child; curr_child != NULL; curr_child = curr_child->next){
        printf("%s\t%s\t%s\n", curr_child->name, curr_child->ptype, curr_child->rtype);
    }
    printf("\n");

    /*Print the other tables*/
    for (current = head->next_table; current != NULL; current = current->next_table){
        /*Build parameter type string*/
        strcpy(params, "(");
        if (current->param_list != NULL){
            for (next_param = current->param_list->next; next_param != NULL; next_param = next_param->next){
                strcat(params, next_param->type);
                if (next_param->next != NULL) strcat(params, ","); //Add ',' if it's not last parameter
            }
        }
        strcat(params, ")");

        /*Print the name*/
        printf("===== Function %s%s Symbol Table =====\n", current->name, params);

        /*While we have children to print*/
        for (curr_child = current->child; curr_child != NULL; curr_child = curr_child->next){
            printf("%s\t%s\t%s", curr_child->name, curr_child->ptype, curr_child->rtype);
            /*If its a parameter*/
            if (curr_child->is_param==1) printf("\tparam");
            printf("\n");
        }
        printf("\n");
    }
}







/*************************************************************************************
 * Prints a semantic error corresponding to given type as parameter.
 * 
 * Parameters:
 *      error: Which type of error it is;
 *      line: The line where the first token with the error appeared;
 *      col: The column where the first token with the error appeared;
 *      *token: Name of the token;
 *      *type1: Type 1 of a token, for errors with only one token;
 *      *type2: Type 2 of a token, for errors with two tokens.
 * 
 *************************************************************************************/
void semantic_error(int error, int line, int col, char *token, char *type1, char *type2){
    printf("Line %d, column %d: ", line, col);
    switch (error){
        case SYM_ALREADY_DEFINED:
            printf("Symbol %s already defined\n", token);
            break;
        case SYM_NOT_FOUND:
            printf("Cannot find symbol %s\n", token);
            break;
        case OP_CANT_APPLY_1:
            printf("Operator %s cannot be applied to type %s\n", token, type1);
            break;
        case OP_CANT_APPLY_2:
            printf("Operator %s cannot be applied to types %s, %s\n", token, type1, type2);
            break;
        case INCOMPATIBLE:
            printf("Incompatible type %s in %s statement\n", type1, token);
            break;
        case INVALID_OCTAL:
            printf("Invalid octal constant: %s\n", token);
            break;
        case SYM_NEVER_USED:
            printf("Symbol %s declared but never used\n", token);
    }
}




/*****************************************
 * Frees function parameters list.
 * 
 * Parameters:
 *      *head: Head of the linked list.
 *****************************************/
void free_param_list(List *head){
    List *current = head;
    List *next = head;

    for (; next != NULL; current = next){
        next = current->next;
        free(current);
    }
}







/**************************************************************************
 * Frees symbol table
 * 
 * Parameters:
 *      *head: Head of the list to be freed.
 * 
 **************************************************************************/
void free_symbol_table(Symbol_table *head){
    /*Iterate over all the tables*/
    Symbol_table *current, *next_table = NULL;
    for (current = head; next_table != NULL; current = next_table){
        /*First free this table's child nodes*/
        Symbol_node *curr_child = current->child;
        Symbol_node *next = current->child;
        for (; next!=NULL && curr_child!=NULL; curr_child = next){
            next = curr_child->next;
            free(curr_child);
        }

        /*Free the table's parameter list*/
        free_param_list(current->param_list);

        /*Free this table*/
        next_table = current->next_table;
        free(current);
    }
}