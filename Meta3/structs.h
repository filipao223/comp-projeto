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
    char name[MAX_AST_NODE_NAME];
    char id[MAX_AST_NODE_ID];
    char type[MAX_AST_NODE_NAME];
    struct ast_node *parent;
    struct ast_node *children[MAX_AST_NODE_CHILDREN];
    int num_children;
    int has_next_node;
} ast_node;

//Symbol table
typedef struct symbol_table{
    char name[MAX_SYMBOL_TABLE_NAME];
    struct symbol_node *child;
    struct symbol_table *next_table;
} Symbol_table;

//Symbol node
typedef struct symbol_node{
    char name[MAX_AST_NODE_NAME];
    char rtype[MAX_AST_NODE_NAME];
    char ptype[MAX_AST_NODE_NAME];
    struct symbol_node *next;
} Symbol_node;


//Simple linked list (for function parameters)
typedef struct list{
    char name[MAX_AST_NODE_NAME];
    char type[MAX_AST_NODE_NAME];
    struct list *next;
} List;

#endif