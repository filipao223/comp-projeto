#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "structs.h"
#include "ast.h"
#include "gen_code.h"

int count = 0;

int starts_with(const char *pre, const char *str)
{
    if( strncmp(pre, str, strlen(pre)) == 0) return 1;

    return 0;
}

char* type_of(ast_node* node){
    
    if(strcmp(node->name, "Int") == 0){
        return "i32";
    }

    if(strcmp(node->name, "bool") == 0){
        return "i1";
    }

    if(strcmp(node->name, "float32") == 0){
        return "double";
    }


    return " ";
}

char * type_of_operation(ast_node* node){

}

void generate_code(ast_node *root){
    if(root == NULL) return;
    if(strcmp(root->name, "Program") == 0){
        for(int i = 0; i < root->num_children; i++){
            if(strcmp(root->children[i]->name, "FuncDecl") == 0){
                generate_func(root->children[i]);
            }
        }
    }
}


void generate_func(ast_node* node){
    //printf("GENERATE_FUNC: %s\n", node->name);
    //primeiro for para os FuncDecl
    for(int i = 0; i < node -> num_children; i++){
        //for para os FuncHeader ou FuncBody
        //for(int j = 0; j < node->children[i]->num_children; j++){
            //printf("GENERATE_FUNC FOR: %s\n", node->children[i]->name);
            if(strcmp(node->children[i]->name, "FuncHeader") == 0){
                //temp é o FuncHeader
                ast_node* temp = node->children[i];
                char *id = temp->children[0]->id;
                //printf("ID: %s\n", id);
                char *type = type_of(temp->children[1]);
                printf("define %s @%s(", type, id);
                //printf("GENERATE_FUNC: %s\n", temp->children[2]->name);
                generate_func_params(temp->children[2]);
                printf(")\n");
            }

            if(strcmp(node->children[i]->name, "FuncBody") == 0){
                ast_node* temp = node->children[i];
                generate_func_body(temp);
            }
        //}
    }
   
}

char *generate_func_params(ast_node* node){
    //node que se recebe é FuncParams

    for(int i=0; i<node->num_children; i++)
    {
        //temp é o ParamDecl
        ast_node* temp = node->children[i];
        for(int j = 0; j<temp->num_children; j+=2){

            char* type = type_of(temp->children[j]);
            char* id = temp->children[j+1]->id;

            if( !strcmp(type," ") == 0 && !strcmp(id, " ") == 0){
                printf("%s %s", type, id);
                if(j < temp->num_children - 2){
                    printf(", ");
                }
            }
        }
        
    }

    return "";
    
}

char *generate_func_body(ast_node* node){

    for (int i = 0; i < node->num_children; i++){
        if(strcmp(node->children[i]->name, "If")){
           ast_node* temp = node->children[i]->children;
           char* op = type_of_operation(temp);
           char* var = temp->children[0];
           char* val = temp->children[1];
           printf("%ifcond = icmp %s ");
        }
    }
   
   return " ";

}