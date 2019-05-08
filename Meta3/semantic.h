#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "structs.h"

int check_program(Symbol_table*, ast_node*);
int check_funcdecl(Symbol_table*);

int insert_new_table(Symbol_table*, char*);
int insert_new_child(Symbol_table*, char*, char*, char*, char*);

void print_symbol_table(Symbol_table*);

void free_symbol_table(Symbol_table*);


#endif