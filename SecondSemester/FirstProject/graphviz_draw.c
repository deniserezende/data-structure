//
//  graphviz_draw.c
//  
//
//  Created by Denise F. de Rezende on 03/09/21.
//

#include <stdio.h>
#include <stdlib.h>
#include "graphviz_draw.h"

FILE *begin_design(const char *output_filename){
    FILE *output_file;
    output_file = fopen(output_filename,"w");
    fprintf(output_file,"digraph G {\n");

    return output_file;
}

void end_design(FILE *output_file){
    fprintf(output_file,"}\n");
    fclose(output_file);
}

void add_tree_element(char* parent, char* child_left, char* child_right, FILE *output_file){
    char *edge = " -> ";
    char *NullNode = " [shape=point, style=\"invis\"]";
    char *invisEdge = " [style=\"invis\"]";
    char *ident = "   ";
    char lstring[100], rstring[100];


    if(parent == NULL) return;
    if(child_left != NULL){
        sprintf(lstring,"%s%s%s%s ;\n",ident, parent, edge, child_left);
        fprintf(output_file, "%s", lstring);
    }
    if(child_right != NULL){
        sprintf(rstring,"%s%s%s%s ;\n",ident, parent, edge, child_right);
        fprintf(output_file,"%s", rstring);
    }
}


// talvez aqui separar escrever o pai ->
 // dps o filho ???? nao ta uma boa estratégia

 