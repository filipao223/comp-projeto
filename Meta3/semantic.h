#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "structs.h"


/*Semantic errors*/
#define SYM_ALREADY_DEFINED 1
#define SYM_NOT_FOUND       2
#define OP_CANT_APPLY_1     3
#define OP_CANT_APPLY_2     4
#define INCOMPATIBLE        5
#define INVALID_OCTAL       6
#define SYM_NEVER_USED      7




int check_program_symbols(Symbol_table*, ast_node*);
int check_funcdecl_symbols(Symbol_table*, ast_node*, List*, char*, char*);

int check_program_semantic(Symbol_table*, ast_node*);
int check_node_semantic(Symbol_table*, ast_node*);

int insert_new_table(Symbol_table*, char*, List*);
int insert_new_child(Symbol_table*, char*, char*, char*, char*, int);

Symbol_node* search_symbol(Symbol_table*, char*, char*);
Symbol_table* search_table(Symbol_table*, char*);

void annotate_ast(Symbol_table*, ast_node*);
void annotate_node(Symbol_table*, ast_node*, char*);
int is_expr_with_child(char*);
int is_expr_bool(char*);

int check_bad_octal(char*);

void store_func_params(List*, ast_node*);

void print_symbol_table(Symbol_table*);

void semantic_error(int, int, int, char*, char*, char*);

void free_param_list(List*);
void free_symbol_table(Symbol_table*);


#endif