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
    
    if(strcmp(node->name, "Int") == 0 || strcmp(node->note, "int") == 0){
        return "i32";
    }

    if(strcmp(node->name, "bool") == 0){
        return "i1";
    }

    if(strcmp(node->name, "Float32" ) == 0 || strcmp(node->note, "float32") == 0){
        return "double";
    }


    return "";
}

int is_operation(char* op){
    if(strcmp(op,"Eq") == 0 || strcmp(op,"Ne") == 0 || strcmp(op,"Lt") == 0
    || strcmp(op,"Gt") == 0 || strcmp(op,"Le") == 0 || strcmp(op,"Ge") == 0 ){
        return 1;
    }

    return 0;
}

char * type_of_operation(ast_node* node){

    if (strcmp(node->name, "Eq") == 0){
        return "eq";
    }

    if (strcmp(node->name, "Ne") == 0){
        return "ne";
    }

    if (strcmp(node->name, "Lt") == 0){
        return "slt";
    }

    if (strcmp(node->name, "Gt") == 0){
        return "sgt";
    }

    if (strcmp(node->name, "Le") == 0){
        return "sle";
    }

    if (strcmp(node->name, "Ge") == 0){
        return "sge";
    }

    return "";
}

void generate_code(ast_node *root){
    if(root == NULL) return;
    if(strcmp(root->name, "Program") == 0){
        for(int i = 0; i < root->num_children; i++){
            if(strcmp(root->children[i]->name, "FuncDecl") == 0){
                generate_func(root->children[i]);
            }
            if(strcmp(root->children[i]->name, "VarDecl") == 0){
                generate_var_decl(root->children[i], 1);
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
                if(strcmp(type,"") == 0){
                    printf("define @%s(", id);
                }else{
                    printf("define %s @%s(", type, id);
                }
                //printf("GENERATE_FUNC: %s\n", temp->children[2]->name);
                generate_func_params(temp->children[2]);
                printf("){\n");
            }

            if(strcmp(node->children[i]->name, "FuncBody") == 0){
                ast_node* temp = node->children[i];
                generate_func_body(temp);
                printf("}\n");
            }

        //}
    }
   
}

char *generate_func_params(ast_node* node){
    //node que se recebe é FuncParams
    if(node == NULL) return "";

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

char *generate_var_decl(ast_node* node, int global){

    char* type = type_of(node->children[0]);
    char* name = node->children[1]->id;

    if(global == 1){
        printf("@%s = global %s\n", name, type);
    }else{
        printf("%%%s = alloca %s\n", name, type);
    }


    return "";    
}

char *generate_parse_args(ast_node* node){

    //char* call = "";
    char* arg = node->children[0]->id;
    char* value = node->children[1]->id;
    char* arg_type = type_of(node->children[0]);
    char* value_type = type_of(node->children[1]);

    /*if(strcmp(node->children[1]->name, "Call") == 0){
        printf("IN");
        ast_node* temp = node->children[1];
        char* func = temp->children[0]->id;
        char* arguments = temp->children[1]->id;
        sprintf(call, "%s%d", "call", count);
        count++;
        value = call;
        printf("%%%s = call %s @%s(%s)\n", call, value_type,func,arguments);       
    }*/

    printf("store %s %s, %s* %%%s\n", value_type, value, arg_type, arg);

    return "";
}

char *generate_func_body(ast_node* node){

    for (int i = 0; i < node->num_children; i++){
        if(strcmp(node->children[i]->name, "If") == 0){
            for (int j = 0; j < node->children[i]->num_children ; j++)
            {
                //Filhos do IF
                ast_node* temp = node->children[i]->children[j];
                if(is_operation(temp->name)){
                    char* op = type_of_operation(temp);
                    char* var = temp->children[0]->id;
                    char* val = temp->children[1]->id;
                    char* type = temp->note;
                    printf("%%ifcond = icmp %s %s %%%s, %%%s\n", op, type, var, val);
                }

                if(strcmp(temp->name, "Block")){
                    
                }
                
            }
            
           
        }

        if(strcmp(node->children[i]->name, "VarDecl") == 0){
            generate_var_decl(node->children[i], 0);
        }

        if(strcmp(node->children[i]->name, "Assign") == 0){
            generate_parse_args(node->children[i]);    
        }
    }
   
   return "";

}