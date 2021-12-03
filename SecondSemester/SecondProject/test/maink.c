#include <stdio.h>
#include "graph.h"
#include <stdlib.h>
#include "kruskals_algorithm.h"


typedef struct vertex_node{
    int num;
    char numc[10];
}VERT;

typedef struct edge{
    int num;
}ED;

long get_edge_value(ED* ed1){
    return (long)ed1->num;
}

long compare_vertices(VERT* vert1, VERT*vert2){
    if(vert1->num == vert2->num) return 0;
    return 1;
}

void print_ed(ED* ed1){
    printf("%d", ed1->num);
}

void print_ver(VERT* vert1){
    printf("%d", vert1->num);
}

void deallocate_edge(ED *ed1){
    //printf("edge:%d\n", ed1->num);
    free(ed1);
}

void deallocate_vertex(VERT *ed1){
    //printf("vertex(:%d\n", ed1->num);
    free(ed1);
}

long return_true(type_litems item){
    return 1;
}

long print_ver_l(VERT* vert1){
    printf("%d\t", vert1->num);
    return 0;
}

int main(){
    type_graph graph = create_graph();

    printf("\nINICIANDO\n");

    VERT* vertex = malloc(sizeof(VERT));
    vertex->num = 1;
    sprintf(vertex->numc, "1");
    add_vertex_to_graph(graph, vertex->numc);
    set_vertex_info_in_graph(graph, vertex->numc, vertex);
    
    VERT* vertex2 = malloc(sizeof(VERT));
    vertex2->num = 2;
    sprintf(vertex2->numc, "2");
    add_vertex_to_graph(graph, vertex2->numc);
    set_vertex_info_in_graph(graph, vertex2->numc, vertex2);
    
    VERT* vertex3 = malloc(sizeof(VERT));
    vertex3->num = 3;
    sprintf(vertex3->numc, "3");
    add_vertex_to_graph(graph, vertex3->numc);
    set_vertex_info_in_graph(graph, vertex3->numc, vertex3);

    VERT* vertex4 = malloc(sizeof(VERT));
    vertex4->num = 4;
    sprintf(vertex4->numc, "4");
    add_vertex_to_graph(graph, vertex4->numc);
    set_vertex_info_in_graph(graph, vertex4->numc, vertex4);

    VERT* vertex5 = malloc(sizeof(VERT));
    vertex5->num = 5;
    sprintf(vertex5->numc, "5");
    add_vertex_to_graph(graph, vertex5->numc);
    set_vertex_info_in_graph(graph, vertex5->numc, vertex5);

    printf("\nINSERI OS VERTEX\n");

    print_graph(graph, (void*)print_ver, (void*)print_ed);


    // ED* edge12 = malloc(sizeof(ED));
    // edge12->num = 3;
    // add_edge_to_graph(graph, vertex->numc, vertex2->numc);
    // set_edge_info_in_graph(graph, vertex->numc, vertex2->numc, edge12);

    // ED* edge25 = malloc(sizeof(ED));
    // edge25->num = 4;
    // add_edge_to_graph(graph, vertex2->numc, vertex5->numc);
    // set_edge_info_in_graph(graph, vertex2->numc, vertex5->numc, edge25);

    ED* edge34 = malloc(sizeof(ED));
    edge34->num = 2;
    add_edge_to_graph(graph, vertex3->numc, vertex4->numc);
    set_edge_info_in_graph(graph, vertex3->numc, vertex4->numc, edge34);

    ED* edge45 = malloc(sizeof(ED));
    edge45->num = 5;
    add_edge_to_graph(graph, vertex4->numc, vertex5->numc);
    set_edge_info_in_graph(graph, vertex4->numc, vertex5->numc, edge45);

    // ED* edge51 = malloc(sizeof(ED));
    // edge51->num = 1;
    // add_edge_to_graph(graph, vertex5->numc, vertex->numc);
    // set_edge_info_in_graph(graph, vertex5->numc, vertex->numc, edge51);
    
    printf("\nINSERI OS EDS\n");

    print_graph(graph, (void*)print_ver, (void*)print_ed);


    // type_graph graphy = kruskals_algorithm_in_graph(graph, (void*)get_edge_value);


    // print_graph(graph, (void*)print_ver, (void*)print_ed);
    // printf("graphy\n\n");
    // print_graph(graphy, (void*)print_ver, (void*)print_ed);


    // int *vector = malloc(sizeof(int) * 5);

    // for(int i=0; i < 5; i++){
    //     vector[i] = 1;
    // }

    int vector[5];

    printf("começando o kruskals_algorithm_in_graph_forest\n");

    type_graph graphy = kruskals_algorithm_in_graph_forest(graph, (void*)get_edge_value, vector);

    printf("fim do kruskals_algorithm_in_graph_forest\n");


    print_graph(graph, (void*)print_ver, (void*)print_ed);
    printf("graphy\n\n");
    print_graph(graphy, (void*)print_ver, (void*)print_ed);

    for(int i=0; i < 5; i++){
        printf("v=[%d]\n", vector[i]);
    }

}