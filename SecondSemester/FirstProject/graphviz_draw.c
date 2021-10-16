//
//  graphviz_draw.c
//  
//
//  Created by Denise F. de Rezende on 03/09/21.
//

#include <stdio.h>
#include <stdlib.h>
#include "graphviz_draw.h"

int GD_draw;
int GD_size = 400;

type_dot begin_design(const char *filename){
    FILE *file;
    file = fopen(filename,"w");
    fprintf(file,"digraph G {\n");
    GD_draw = 0;
    return file;
}

void end_design(type_dot file){
    FILE *dot_file = file;
    fprintf(dot_file,"\n}\n");
    fclose(dot_file);
}

void reset_design(){
    GD_draw = 0;
}

void set_size_for_strings(int size){
    GD_size = size;
}


void appear_node_in_tree_design(type_dot file){
    FILE *dot_file = file;
    char *node = " node[shape=ellipse, style=\"\"]";
    char *edge = " edge[style=\"\"]"; 
    char string[100];

    sprintf(string,"%s\n%s\n",node, edge);
    fprintf(dot_file, "%s", string);
}

void hide_node_in_tree_design(type_dot file){
    FILE *dot_file = file;
    char *node = " node[shape=point, style=\"invis\"]";
    char *edge = " edge[style=\"invis\"]"; 
    char string[100];

    sprintf(string,"%s\n%s\n",node, edge);
    fprintf(dot_file, "%s", string);
}

void add_parent_in_tree_design(char* parent, type_dot file){
    FILE *dot_file = file;
    char *edge = " -> ";

    char *ident = "   ";
    char *string = malloc(sizeof(char) * GD_size);

    sprintf(string,"%s%s%s {", ident, parent, edge);
    fprintf(dot_file, "%s", string);

    free(string);
}

void add_root_in_tree_design(char* root, type_dot file){
    FILE *dot_file = file;
    char *string = malloc(sizeof(char) * GD_size);
    sprintf(string,"\t%s //root\n", root);
    fprintf(dot_file, "%s", string);
    free(string);
}

void add_child_in_tree_design(char* child, type_dot file){
    FILE *dot_file = file;
    char *string = malloc(sizeof(char) * GD_size);
    //sprintf(string,"child[shape=ellipse, label=%s] , ", child);
    sprintf(string,"%s};\n", child);
    fprintf(dot_file, "%s", string); 
    free(string);
}

void close_child(type_dot file){
    FILE *dot_file = file;
    char string[5];
    sprintf(string,"}%c\n", '\0');
    fprintf(dot_file, "%s", string);
}


void add_empty_child_in_tree_design(type_dot file){
    FILE *dot_file = file;
    char string[100];

    long rand = random();

    sprintf(string,"%ld};\n", rand);
    //sprintf(string," , ");
    fprintf(dot_file, "%s", string);
}
// get_info MUST RETURN A CHAR*
void insert_blocks_rects_parent_list_of_not_null_child(type_dot file, type_list parent, type_gdptrf_onelist get_info){
    FILE *dot_file = file;
    if(parent == NULL) return;
    
    char *idtmp = malloc(sizeof(char) * GD_size);

    if(GD_draw == 0){
        sprintf(idtmp, "%s%c", (char*)get_info(parent), '\0');
        add_root_in_tree_design(idtmp, dot_file);
        GD_draw++;
    }
    appear_node_in_tree_design(dot_file);
    sprintf(idtmp, "%c", '\0');
    sprintf(idtmp, "%s%c", (char*)get_info(parent), '\0');
    add_parent_in_tree_design(idtmp, dot_file);  

    free(idtmp);  
}

void insert_blocks_rects_parent_list_of_null_child(type_dot file, type_list parent, type_gdptrf_onelist get_info){
    FILE *dot_file = file;
    if(parent == NULL) return;
    
    char *idtmp = malloc(sizeof(char) * GD_size);

    if(GD_draw == 0){
        sprintf(idtmp, "%s%c", (char*)get_info(parent), '\0');
        add_root_in_tree_design(idtmp, dot_file);
        GD_draw++;
    }
    hide_node_in_tree_design(dot_file);
    sprintf(idtmp, "%s%c", (char*)get_info(parent), '\0');
    add_parent_in_tree_design(idtmp, dot_file);   

    free(idtmp);   
}


void insert_blocks_rects_child_list(type_dot file, type_list child, type_gdptrf_onelist get_info){
    FILE *dot_file = file;
    char *idtmp = malloc(sizeof(char) * GD_size);

    if(child != NULL){
        printf("to no if dentro do insert_blocks_rects_child_list\n");
        sprintf(idtmp, "%s%c", (char*)get_info(child), '\0');
        add_child_in_tree_design(idtmp, dot_file);
    }
    else{
        add_empty_child_in_tree_design(dot_file);
    }

    free(idtmp);   
}