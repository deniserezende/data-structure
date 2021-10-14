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
    fprintf(output_file,"\n}\n");
    fclose(output_file);
}

// void add_tree_element(char* parent, char* child_left, char* child_right, FILE *output_file){
//     char *edge = " -> ";
//     char *NullNode = " [shape=point, style=\"invis\"]";
//     char *invisEdge = " [style=\"invis\"]";
//     char *ident = "   ";
//     char lstring[100], rstring[100];


//     if(parent == NULL) return;
//     if(child_left != NULL){
//         sprintf(lstring,"%s%s%s%s ;\n",ident, parent, edge, child_left);
//         fprintf(output_file, "%s", lstring);
//     }
//     if(child_right != NULL){
//         sprintf(rstring,"%s%s%s%s ;\n",ident, parent, edge, child_right);
//         fprintf(output_file,"%s", rstring);
//     }
// }

void appear_node_in_tree_design(FILE *output_file){
    char *node = " node[shape=ellipse, style=\"\"]";
    char *edge = " edge[style=\"\"]"; 
    char string[100];

    sprintf(string,"%s\n%s\n",node, edge);
    fprintf(output_file, "%s", string);
}

void hide_node_in_tree_design(FILE *output_file){
    char *node = " node[shape=point, style=\"invis\"]";
    char *edge = " edge[style=\"invis\"]"; 
    char string[100];

    sprintf(string,"%s\n%s\n",node, edge);
    fprintf(output_file, "%s", string);
}

void add_parent_in_tree_design(char* parent, FILE *output_file){
    char *edge = " -> ";

    char *ident = "   ";
    char string[100];

    sprintf(string,"%s%s%s {", ident, parent, edge);
    fprintf(output_file, "%s", string);
}

void add_root_in_tree_design(char* root, FILE *output_file){
    char string[20];
    sprintf(string,"\t%s //root\n", root);
    fprintf(output_file, "%s", string);
}

void add_child_in_tree_design(char* child, FILE *output_file){
    char string[100];

    //sprintf(string,"child[shape=ellipse, label=%s] , ", child);
    sprintf(string,"%s};\n", child);
    fprintf(output_file, "%s", string);
}

void close_child(FILE *output_file){
    char string[5];
    sprintf(string,"}%c\n", '\0');
    fprintf(output_file, "%s", string);
}


void add_empty_child_in_tree_design(FILE *output_file){
    char string[100];

    long rand = random();

    sprintf(string,"%ld};\n", rand);
    //sprintf(string," , ");
    fprintf(output_file, "%s", string);
}
// talvez aqui separar escrever o pai ->
 // dps o filho ???? nao ta uma boa estratégia

 