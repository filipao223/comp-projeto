#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "structs.h"

void insert_new_table(Symbol_table*, char*);
int insert_new_child(Symbol_table*, char*, char*, char*, char*);

void print_symbol_table(Symbol_table*);

void free_symbol_table(Symbol_table*);


#endif