#ifndef GEN_CODE_H
#define GEN_CODE_H


#include "structs.h"

int starts_with(const char *, const char *);
char* extract_between(const char *, const char *, const char *);
char* type_of(ast_node*);
char* type_of_operation(ast_node* );
void generate_code(ast_node *);
void generate_func(ast_node* );
char *generate_func_params(ast_node* );
char *generate_func_body(ast_node*);
char *generate_var_decl(ast_node* , int);
int is_operation(char* );
char *generate_parse_args(ast_node* );

#endif
