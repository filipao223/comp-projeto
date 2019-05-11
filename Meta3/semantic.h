#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "structs.h"

int check_program(Symbol_table*, ast_node*);
int check_funcdecl(Symbol_table*, ast_node*, List*, char*, char*);

int insert_new_table(Symbol_table*, char*, List*);
int insert_new_child(Symbol_table*, char*, char*, char*, char*, int);

Symbol_node* search_symbol(Symbol_table*, char*, char*);
Symbol_table* search_table(Symbol_table*, char*);

void annotate_ast(Symbol_table*, ast_node*);
void annotate_node(Symbol_table*, ast_node*);
int is_expr_with_child(char*);
int is_expr_bool(char*);

void store_func_params(List*, ast_node*);

void print_symbol_table(Symbol_table*);

void free_param_list(List*);
void free_symbol_table(Symbol_table*);


#endif