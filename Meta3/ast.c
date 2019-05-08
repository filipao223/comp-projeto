#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "structs.h"
#include "ast.h"





/******************************************************************************
* Mallocs and returns a new struct ast_node.
* 
* Param:
*   name: Name of the AST node block (Print, Assign, If, ...);
*   id: Optional string for nodes that also have a value (int, float, string).
*
* Returns: Malloc'd struct ast_node.
******************************************************************************/
ast_node *create_new_node(char name[], char id[]){
    ast_node *new_node = malloc(sizeof(struct ast_node));
    new_node->num_children = 0;
    if (name == NULL) return NULL; //Name can't be empty
    strcpy(new_node->name, name);

    if (id != NULL) strcpy(new_node->id, id);
    else strcpy(new_node->id, "");

    return new_node;
}


/**********************************************************************************************
 * Mallocs and returns a new struct ast_node, also filling in a type, for function parameters.
 * 
 * Param:
 *   name: Name of the AST node block (Print, Assign, If, ...);
 *   id: Optional string for nodes that also have a value (int, float, string).
 *   type: Type (int, float32, string) of the parameter
 *
 * Returns: Malloc'd struct ast_node.
 *
 **********************************************************************************************/
ast_node *create_new_node_param(char name[], char id[], char type[]){
    ast_node *new_node = malloc(sizeof(struct ast_node));
    new_node->num_children = 0;
    new_node->has_next_node = 0;
    if (name == NULL) return NULL; //Name can't be empty
    strcpy(new_node->name, name);

    if (id != NULL) strcpy(new_node->id, id);
    else strcpy(new_node->id, "");

    if (type != NULL) strcpy(new_node->type, type);
    else strcpy(new_node->type, "");

    return new_node;
}



/*
* Adds a given child node as a parameter to given parent node's children list.
* 
* Param:
*   parent: Parent struct ast_node to which node will be appended
*   child: struct ast_node which will be appended
*
* Returns: The given parent node.
*/
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


/*TODO: remove this*/
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



/*
* Appends all child nodes of a given root node as a parameter to another node. 
* Assumes that a node with name "root" is always given.
* 
* Param:
*   parent: Name of the AST node which will receive child nodes;
*   root_node: AST node which name is "root" that contains child nodes to append.
*
* Returns: The given parent node.
*/
ast_node *append_list(ast_node *parent, ast_node *root_node){
    if (parent != NULL && root_node != NULL){
        for(int i=0; i<root_node->num_children; i++){
            ast_node *current = root_node->children[i];
            parent->children[parent->num_children] = create_new_node("empty", NULL);
            copy_ast_data(parent->children[parent->num_children], current);
            copy_ast_children(parent->children[parent->num_children], current);
            parent->num_children += 1;
            free(current);
        }
        return parent;
    }

    return NULL;
}



/*
* Copies all the data (name and id) from a node to another.
* 
* Param:
*   dest: Name of the AST node which will receive the data;
*   src: Source of the data.
*
*/
void copy_ast_data(ast_node *dest, ast_node *src){
    if (dest != NULL && src != NULL){
        strcpy(dest->name, src->name);
        if (strcmp(src->id, "")!=0) strcpy(dest->id, src->id);
    }
}



/*
* Copies all child nodes from a node to another.
* 
* Param:
*   dest: Name of the AST node which will receive the nodes;
*   src: Source of the nodes.
*
*/
void copy_ast_children(ast_node *dest, ast_node *src){
    if (dest != NULL && src != NULL){
        for (int i=0; i<src->num_children; i++){
            dest->children[dest->num_children] = src->children[i];
            dest->num_children += 1;
        }
    }
}



/*
* Prints tree starting from the given node.
* 
* Param:
*   root: Node from which to start printing;
*   level: Used to print correct indentation characters, 0 means no dots.
*
*/
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



/*
* Deallocates the tree nodes (depth-first search) starting from given node.
* 
* Param:
*   root: Root node of the tree;
*
*/
void free_ast_tree(ast_node* root){
    if (root==NULL) return;
    //Iterate over all children
    for (int i=0; i< root->num_children; i++){
        free_ast_tree(root->children[i]);
    }

    //Free memory
    free(root);
}