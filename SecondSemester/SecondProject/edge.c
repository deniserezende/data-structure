

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "edge.h"

typedef struct edge{
    char id[40];
    char id_vertex_one[40];
    char id_vertex_two[40];
    char cep_left_block[40];
    char cep_right_block[40];
    double speed_limit;
    double edge_length;
}EDGE;

type_edge new_edge(char id[], char id_vertex_one[], char id_vertex_two[], char cep_right_block[], char cep_left_block[], double edge_length, double speed_limit){
    EDGE *edge = malloc(sizeof(EDGE));

    sprintf(edge->id, "%s", id);
    sprintf(edge->id_vertex_one, "%s", id_vertex_one);
    sprintf(edge->id_vertex_two, "%s", id_vertex_two);
    sprintf(edge->cep_left_block, "%s", cep_left_block);
    sprintf(edge->cep_right_block, "%s", cep_right_block);

    edge->speed_limit = speed_limit;
    edge->edge_length = edge_length;

    return(edge);
}

char* get_edge_id(type_edge edge){
    EDGE *edge_ = edge;
    return(edge_->id);  
}

double get_edge_length(type_edge edge){
    EDGE *edge_ = edge;
    return(edge_->edge_length);  
}

double get_edge_speed_limit(type_edge edge){
    EDGE *edge_ = edge;
    return(edge_->speed_limit);  
}

void destroi_edge(type_edge edge){
    EDGE *edge_ = edge;
    free(edge_);
}