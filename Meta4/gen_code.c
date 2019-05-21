#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "structs.h"
#include "ast.h"
#include "gen_code.h"

int func_decl = 0;

int starts_with(const char *pre, const char *str)
{
    if( strncmp(pre, str, strlen(pre)) == 0) return 1;

    return 0;
}

char* extract_between(const char *str, const char *p1, const char *p2)
{
  const char *i1 = strstr(str, p1);
  if(i1 != NULL){
    const size_t pl1 = strlen(p1);
    const char *i2 = strstr(i1 + pl1, p2);
    if(p2 != NULL){
     /* Found both markers, extract text. */
    const size_t mlen = i2 - (i1 + pl1);
    char *ret = malloc(mlen + 1);
    if(ret != NULL){
       memcpy(ret, i1 + pl1, mlen);
       ret[mlen] = '\0';
       return ret;
     }
    }
  }

  return " ";
}

char* type_of(ast_node* node){
    
    if(strcmp(node->name, "Int")){
        return "i32";
    }

    if(strcmp(node->name, "bool")){
        return "i1";
    }

    if(strcmp(node->name, "float32")){
        return "double";
    }


    return " ";
}

void generate_code(ast_node *root){
    if(root == NULL) return;

    if(strcmp(root->name, "Program")){
        printf("IN_PROGRAM\n");
        for(int i = 0; i < root->num_children; i++){
            if(strcmp(root->children[i]->name, "FuncDecl")){
                generate_func(root->children[i]);
            }
        }
    }
}


void generate_func(ast_node* node){
    printf("IN_FUNC\n");
    //primeiro for para os FuncDecl
    for(int i = 0; i < node -> num_children; i++){
        //for para os FuncHeader ou FuncBody
        for(int j = 0; j < node->children[i]->num_children; j++){
            if(strcmp(node->children[i]->name, "FuncHeader")){
                //temp é o FuncHeader
                ast_node* temp = node->children[i];
                char *id = extract_between(temp->children[0]->name, "(", ")");
                char *type = type_of(temp->children[1]);
                printf("define %s @%s(", type, id);
                generate_func_params(temp->children[2]);
            }
        }
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
            char* id = extract_between(temp->children[j+1]->name, "Id(", ")");

            if( !strcmp(type," ") && !strcmp(id, " ")){
                printf("%s %s", type, id);
                if(j < temp->num_children - 1){
                    printf(", ");
                }
            }
        }
        
    }

    return "";
    
}