#include <stdio.h>
#include "graph.h"
#include <stdlib.h>

typedef struct vertex_node{
    int num;
}VERT;

typedef struct edge{
    int num;
}EDGE;


long compare_vertices(VERT* vert1, VERT*vert2){
    if(vert1->num == vert2->num) return 0;
    return 1;
}

void print_ed(EDGE* ed1){
    printf("%d", ed1->num);
}

void print_ver(VERT* vert1){
    printf("%d", vert1->num);
}

void deallocate_edge(EDGE *ed1){
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
    printf("%d", vert1->num);
    return 0;
}

int main(){
    type_graph graph = create_graph(5);
    VERT* vertex = malloc(sizeof(VERT));
    vertex->num = 1;
    insert_vertex_in_graph(graph, vertex, (void*)compare_vertices);
    
    VERT* vertex2 = malloc(sizeof(VERT));
    vertex2->num = 2;
    insert_vertex_in_graph(graph, vertex2, (void*)compare_vertices);
    
    VERT* vertex3 = malloc(sizeof(VERT));
    vertex3->num = 3;
    insert_vertex_in_graph(graph, vertex3, (void*)compare_vertices);
    
    VERT* vertex4 = malloc(sizeof(VERT));
    vertex4->num = 4;
    insert_vertex_in_graph(graph, vertex4, (void*)compare_vertices);


    EDGE* edge = malloc(sizeof(EDGE));
    edge->num = 6;
    insert_edge_in_graph(graph, vertex, vertex2, (void*)compare_vertices, edge);

    EDGE* edge1 = malloc(sizeof(EDGE));
    edge1->num = 5;
    EDGE* edge2 = malloc(sizeof(EDGE));
    edge2->num = 5;
    insert_edge_in_graph(graph, vertex, vertex3, (void*)compare_vertices, edge1);
    insert_edge_in_graph(graph, vertex3, vertex, (void*)compare_vertices, edge2);

    print_graph(graph, (void*)print_ver, (void*)print_ed);

    printf("antes:%d\n", are_vertex_adjacent_in_graph(graph, vertex, vertex2, (void*)compare_vertices));

    remove_edge_from_graph(graph, vertex, vertex2,  (void*)compare_vertices, (void*)deallocate_edge);

    printf("depois:%d\n", are_vertex_adjacent_in_graph(graph, vertex, vertex2, (void*)compare_vertices));


    printf("random:%d\n", are_vertex_adjacent_in_graph(graph, vertex2, vertex, (void*)compare_vertices));

    
    print_graph(graph, (void*)print_ver, (void*)print_ed);

    EDGE* edge3 = malloc(sizeof(EDGE));
    edge3->num = 9;
    EDGE* edge4 = malloc(sizeof(EDGE));
    edge4->num = 10;
    insert_edge_in_graph(graph, vertex2, vertex, (void*)compare_vertices, edge3);
    insert_edge_in_graph(graph, vertex4, vertex3, (void*)compare_vertices, edge4);
    
    print_graph(graph, (void*)print_ver, (void*)print_ed);

    EDGE* edge11 = malloc(sizeof(EDGE));
    edge11->num = 10;
    insert_edge_in_graph(graph, vertex3, vertex2, (void*)compare_vertices, edge11);
    
    EDGE* edge12 = malloc(sizeof(EDGE));
    edge12->num = 10;
    insert_edge_in_graph(graph, vertex3, vertex4, (void*)compare_vertices, edge12);

    print_graph(graph, (void*)print_ver, (void*)print_ed);


    type_list NEIGHBORS =  vertex_neighbors_in_graph(graph, vertex3, (void*)compare_vertices);

    printf("LIST:\n");
    traverse_full_list_with_conditional_action(NEIGHBORS, (void*)return_true, (void*) print_ver_l);
    printf("\nLIST.\n");
    NEIGHBORS = destroi_list_created_with_vertex_neighbors_in_graph(NEIGHBORS);

    printf("ANTES:\n");
    print_graph(graph, (void*)print_ver, (void*)print_ed);

    EDGE* edge15 = malloc(sizeof(EDGE));
    edge15->num = 100;
    int mudou_edge = change_edge_info_value_in_graph(graph, vertex3, vertex4, (void*)compare_vertices, edge15);

    printf("mudou_edge:\n");
    print_graph(graph, (void*)print_ver, (void*)print_ed);

    VERT* vertex3new = malloc(sizeof(VERT));
    vertex3new->num = 200;
    int mudou_vertex = change_vertex_info_value_in_graph(graph, vertex3, (void*)compare_vertices, vertex3new);

    printf("mudou_vertex:\n");
    print_graph(graph, (void*)print_ver, (void*)print_ed);


    printf("antes2:%d\n", are_vertex_adjacent_in_graph(graph, vertex4, vertex3, (void*)compare_vertices));

    remove_vertex_from_graph(graph, vertex3new, (void*)compare_vertices, (void*) deallocate_vertex, (void*)deallocate_edge);

    printf("depois2:%d\n", are_vertex_adjacent_in_graph(graph, vertex4, vertex3, (void*)compare_vertices));

    print_graph(graph, (void*)print_ver, (void*)print_ed);

    destroi_graph(graph, (void*)deallocate_vertex, (void*)deallocate_edge);

    print_graph(graph, (void*)print_ver, (void*)print_ed);



}