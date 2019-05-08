#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
 *      ptype[]: Parameter type of the symbol.
 * 
 * Returns:
 *      -1 if the table wasn't found, 1 if the symbol was appended and 0 if the symbol
 *          was already appended.
 * 
 ******************************************************************************************/
int insert_new_child(Symbol_table* head, char table[], char name[], char ptype[], char rtype[]){
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
    new_node->next = NULL;
    
    if (curr_child != NULL) curr_child->next = new_node;
    else current->child = new_node; 

    return 1;
}




int check_program(Symbol_table* head, ast_node* root){
    ast_node *current = root->children[0];
    int error_count = 0;
    /*Check for any variable declarations or functions*/
    for (int i=0; i< root->num_children; i++){
        /*Check for VarDecl*/
        if (strcmp(current->name,"VarDecl")==0){
            /*Store type and name*/
            char type[MAX_AST_NODE_NAME], name[MAX_AST_NODE_NAME];
            strcpy(type, current->children[0]->name); strcpy(name, current->children[1]->id);
            error_count += insert_new_child(head, "global", name, "", type);
        }
        /*Check for FuncDecl*/
        
    }

    return error_count;
}




/******************************************************************************
 * Print the symbol table.
 * 
 * Parameters:
 *      *head: Head of the linked list.
 * 
 ******************************************************************************/
void print_symbol_table(Symbol_table* head){
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
            printf("%s\t%s\t%s\n", curr_child->name, curr_child->ptype, curr_child->rtype);
        }
        printf("\n");
    }
}




/**************************************************************************
 * Frees symbol table
 * 
 * Parameters:
 *      *head: Head of the list to be freed.
 * 
 **************************************************************************/
void free_symbol_table(Symbol_table* head){
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