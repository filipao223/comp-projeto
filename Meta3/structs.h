#ifndef STRUCTS_H
#define STRUCTS_H


#define MAX_TEMP 1024

#define MAX_AST_NODE_NAME 1024
#define MAX_AST_NODE_ID 1024
#define MAX_AST_NODE_CHILDREN 1024

#define MAX_SYMBOL_TABLE_NAME 1024

#define MAX_PARAMS 15




//AST
typedef struct ast_node{
    /*Type of node, Id(), Call(), ...*/
    char name[MAX_AST_NODE_NAME];
    /*Name of the variable or function*/
    char id[MAX_AST_NODE_ID];
    char type[MAX_AST_NODE_NAME];
    /*Note in the annotated AST*/
    char note[MAX_AST_NODE_NAME];
    struct ast_node *parent;
    struct ast_node *children[MAX_AST_NODE_CHILDREN];
    /*Line and column number of the token*/
    int line, col;
    int num_children;
    int has_next_node;
} ast_node;




//Symbol table
typedef struct symbol_table{
    char name[MAX_SYMBOL_TABLE_NAME];
    /*List of parameters of the function, head node has no info*/
    struct list *param_list;
    struct symbol_node *child;
    struct symbol_table *next_table;
} Symbol_table;






//Symbol node
typedef struct symbol_node{
    /*Name of the symbol*/
    char name[MAX_AST_NODE_NAME];
    /*Type of the symbol*/
    char rtype[MAX_AST_NODE_NAME];
    /*Only for global table function, paramaters (), (int),...*/
    char ptype[MAX_AST_NODE_NAME];
    /*For function symbol tables, if this symbol is it's parameter*/
    int is_param;
    struct symbol_node *next;
} Symbol_node;






//Simple linked list
typedef struct list{
    char name[MAX_AST_NODE_NAME];
    char type[MAX_AST_NODE_NAME];
    struct list *next;
} List;




#endif