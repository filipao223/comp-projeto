#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "structs.h"
#include "semantic.h"





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
int insert_new_table(Symbol_table* head, char name[]){
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

    printf("%d parameters\n", params->num_children);

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





int check_func(Symbol_table *head, ast_node *funcdecl, List *param_list, char rtype[], char table_name[]){
    List *next_param;
    char type[MAX_AST_NODE_NAME], name[MAX_AST_NODE_NAME];
    int error_count = 0;

    /*Insert return type and parameters in the function table*/
    insert_new_child(head, table_name, "return", "", rtype, 0);
    for (next_param = param_list->next; next_param != NULL; next_param = next_param->next){
        insert_new_child(head, table_name, next_param->name, "", next_param->type, 1);
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
            error_count += insert_new_child(head, table_name, name, "", type, 0);
        }
    }

    return error_count;
}





/*******************************************************************************************
 * Starts semantic analysis and symbol table build.
 * Checks for any var declaration and function declaration, and then checks the functions.
 * 
 * Parameters:
 *      *head: The head of the linked list;
 *      *root: Root node of the AST.
 * 
 * Returns:
 *      The number of found semantic errors.
 * 
 *******************************************************************************************/
int check_program(Symbol_table *head, ast_node *root){
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
            error_count += insert_new_child(head, "global", name, "", type, 0);
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
                for (next_param = param_list->next; next_param != NULL; next_param = next_param->next){
                    strcat(params, next_param->type);
                    if (next_param->next != NULL) strcat(params, ","); //Add ',' if it's not last parameter
                }
            }
            strcat(params, ")");

            /*Insert the function in the global table*/
            error_count += insert_new_child(head, "global", name, params, type, 0);

            /*Also add the new table*/
            strcpy(table_name, name); strcat(table_name, params);
            insert_new_table(head, table_name);

            /*Verify the function body*/
            check_func(head, current, param_list, type, table_name);

            /*Free parameters list*/
            free_param_list(param_list);
        }
    }

    /*Annotate the AST*/
    //annotate_ast(head, root);

    return error_count;
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

    /*Print the global symbol table*/
    printf("===== Global Symbol Table =====\n");

    /*While we have children to print*/
    for (curr_child = head->child; curr_child != NULL; curr_child = curr_child->next){
        printf("%s\t%s\t%s\n", curr_child->name, curr_child->ptype, curr_child->rtype);
    }
    printf("\n");

    /*Print the other tables*/
    for (current = head->next_table; current != NULL; current = current->next_table){
        /*Print the namee*/
        printf("===== Function %s Symbol Table =====\n", current->name);

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

        /*Free this table*/
        next_table = current->next_table;
        free(current);
    }
}