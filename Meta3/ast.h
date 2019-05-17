#ifndef AST_H
#define AST_H

#include "structs.h"


//AST functions
void insert_paramdecl(List*, char*, char*);
ast_node *create_new_node(char name[], char id[]);
ast_node *create_new_node_param(char name[], char id[], char type[]);
ast_node *add_ast_node(ast_node *parent, ast_node *child);
ast_node *add_ast_list(ast_node *parent, ast_node *head);
ast_node *append_list(ast_node *parent, ast_node *root_node);
void copy_ast_data(ast_node *dest, ast_node *src);
void copy_ast_children(ast_node *dest, ast_node *src);
void print_ast_tree(ast_node *root, int level);
void free_ast_tree(ast_node* root);


#endif