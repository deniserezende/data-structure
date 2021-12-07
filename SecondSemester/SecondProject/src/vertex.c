

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vertex.h"

typedef struct vertex{
    char id[40];
    double x, y; //coordinates
}VERTEX;

type_vertex new_vertex(char id[], double x, double y){
    VERTEX *vertex = malloc(sizeof(VERTEX));

    sprintf(vertex->id, "%s", id);
    vertex->x = x;
    vertex->y = y;

    return(vertex);
}

char* get_vertex_id(type_vertex vertex){
    VERTEX *vertex_ = vertex;
    return(vertex_->id);  
}

double get_vertex_x(type_vertex vertex){
    VERTEX *vertex_ = vertex;
    return(vertex_->x);  
}

double get_vertex_y(type_vertex vertex){
    VERTEX *vertex_ = vertex;
    return(vertex_->y);  
}

void destroi_vertex(type_vertex vertex){
    VERTEX *vertex_ = vertex;
    free(vertex_);  
}
