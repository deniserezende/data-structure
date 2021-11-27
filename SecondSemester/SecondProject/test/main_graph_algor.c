#include <stdio.h>
#include "graph.h"
#include "graph_algorithms.h"
#include <stdlib.h>

typedef struct vertex_node{
    int num;
    char numc[10];
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

long get_edge_cost(EDGE *ed1){
    return ed1->num;
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

    VERT* v1 = malloc(sizeof(VERT));
    v1->num = 1;
    sprintf(v1->numc, "1");
    add_vertex_to_graph(graph, v1->numc);
    set_vertex_info_in_graph(graph, v1->numc, v1);
    
    VERT* v2 = malloc(sizeof(VERT));
    v2->num = 2;
    sprintf(v2->numc, "2");
    add_vertex_to_graph(graph, v2->numc);
    set_vertex_info_in_graph(graph, v2->numc, v2);
    
    VERT* v3 = malloc(sizeof(VERT));
    v3->num = 3;
    sprintf(v3->numc, "3");
    add_vertex_to_graph(graph, v3->numc);
    set_vertex_info_in_graph(graph, v3->numc, v3);

    VERT* v4 = malloc(sizeof(VERT));
    v4->num = 4;
    sprintf(v4->numc, "4");
    add_vertex_to_graph(graph, v4->numc);
    set_vertex_info_in_graph(graph, v4->numc, v4);

    VERT* v5 = malloc(sizeof(VERT));
    v5->num = 5;
    sprintf(v5->numc, "5");
    add_vertex_to_graph(graph, v5->numc);
    set_vertex_info_in_graph(graph, v5->numc, v5);

    VERT* v6 = malloc(sizeof(VERT));
    v6->num = 6;
    sprintf(v6->numc, "6");
    add_vertex_to_graph(graph, v6->numc);
    set_vertex_info_in_graph(graph, v6->numc, v6);

    VERT* v7 = malloc(sizeof(VERT));
    v7->num = 7;
    sprintf(v7->numc, "7");
    add_vertex_to_graph(graph, v7->numc);
    set_vertex_info_in_graph(graph, v7->numc, v7);

    printf("\nINSERI OS VERTEX\n");
    print_graph(graph, (void*)print_ver, (void*)print_ed);


    EDGE* e1 = malloc(sizeof(EDGE));
    e1->num = 2;
    add_edge_to_graph(graph, v1->numc, v2->numc);
    set_edge_info_in_graph(graph, v1->numc, v2->numc, e1);

    EDGE* e2 = malloc(sizeof(EDGE));
    e2->num = 1;
    add_edge_to_graph(graph, v2->numc, v3->numc);
    set_edge_info_in_graph(graph, v2->numc, v3->numc, e2);

    EDGE* e3 = malloc(sizeof(EDGE));
    e3->num = 3;
    add_edge_to_graph(graph, v4->numc, v3->numc);
    set_edge_info_in_graph(graph, v4->numc, v3->numc, e3);


    EDGE* e4 = malloc(sizeof(EDGE));
    e4->num = 6;
    add_edge_to_graph(graph, v2->numc, v4->numc);
    set_edge_info_in_graph(graph, v2->numc, v4->numc, e4);


    EDGE* e5 = malloc(sizeof(EDGE));
    e5->num = 9;
    add_edge_to_graph(graph, v3->numc, v6->numc);
    set_edge_info_in_graph(graph, v3->numc, v6->numc, e5);

    EDGE* e6 = malloc(sizeof(EDGE));
    e6->num = 2;
    add_edge_to_graph(graph, v4->numc, v6->numc);
    set_edge_info_in_graph(graph, v4->numc, v6->numc, e6);


    EDGE* e7 = malloc(sizeof(EDGE));
    e7->num = 3;
    add_edge_to_graph(graph, v1->numc, v7->numc);
    set_edge_info_in_graph(graph, v1->numc, v7->numc, e7);


    EDGE* e8 = malloc(sizeof(EDGE));
    e8->num = 1;
    add_edge_to_graph(graph, v7->numc, v5->numc);
    set_edge_info_in_graph(graph, v7->numc, v5->numc, e8);

    printf("\nINSERI OS EDGES\n");


    print_graph(graph, (void*)print_ver, (void*)print_ed);

    // printf("antes2:%d\n", are_vertex_adjacent_in_graph(graph, vertex4->numc, vertex3->numc));
    // remove_vertex_from_graph(graph, vertex3->numc, (void*)deallocate_edge);
    // printf("depois2:%d\n", are_vertex_adjacent_in_graph(graph, vertex4->numc, vertex3->numc));

    // print_graph(graph, (void*)print_ver, (void*)print_ed);

    // destroi_graph(graph, (void*)deallocate_vertex, (void*)deallocate_edge);

    // print_graph(graph, (void*)print_ver, (void*)print_ed);

    
    printf("Empty graph (main): %d\n", empty_graph(graph));
    printf("BEGIN dijkstras_algorithm_in_graph\n");
    dijkstras_algorithm_in_graph(graph, v1->numc, (void*)get_edge_cost);
    printf("END dijkstras_algorithm_in_graph\n");

}



// int main(){
//     type_graph graph = create_graph();

//     printf("\nINICIANDO\n");

//     VERT* vertex = malloc(sizeof(VERT));
//     vertex->num = 1;
//     sprintf(vertex->numc, "1");
//     add_vertex_to_graph(graph, vertex->numc);
//     set_vertex_info_in_graph(graph, vertex->numc, vertex);
    
//     VERT* vertex2 = malloc(sizeof(VERT));
//     vertex2->num = 2;
//     sprintf(vertex2->numc, "2");
//     add_vertex_to_graph(graph, vertex2->numc);
//     set_vertex_info_in_graph(graph, vertex2->numc, vertex2);
    
//     VERT* vertex3 = malloc(sizeof(VERT));
//     vertex3->num = 3;
//     sprintf(vertex3->numc, "3");
//     add_vertex_to_graph(graph, vertex3->numc);
//     set_vertex_info_in_graph(graph, vertex3->numc, vertex3);

//     VERT* vertex4 = malloc(sizeof(VERT));
//     vertex4->num = 4;
//     sprintf(vertex4->numc, "4");
//     add_vertex_to_graph(graph, vertex4->numc);
//     set_vertex_info_in_graph(graph, vertex4->numc, vertex4);

//     printf("\nINSERI OS VERTEX\n");
//     print_graph(graph, (void*)print_ver, (void*)print_ed);


//     EDGE* edge = malloc(sizeof(EDGE));
//     edge->num = 6;
//     add_edge_to_graph(graph, vertex->numc, vertex2->numc);
//     set_edge_info_in_graph(graph, vertex->numc, vertex2->numc, edge);

//     EDGE* edge1 = malloc(sizeof(EDGE));
//     edge1->num = 4;
//     add_edge_to_graph(graph, vertex->numc, vertex3->numc);
//     set_edge_info_in_graph(graph, vertex->numc, vertex3->numc, edge1);

//     EDGE* edge2 = malloc(sizeof(EDGE));
//     edge2->num = 5;
//     add_edge_to_graph(graph, vertex3->numc, vertex->numc);
//     set_edge_info_in_graph(graph, vertex3->numc, vertex->numc, edge2);

//     printf("\nINSERI OS EDGES\n");


//     print_graph(graph, (void*)print_ver, (void*)print_ed);


//     printf("antes:%d\n", are_vertex_adjacent_in_graph(graph, vertex->numc, vertex2->numc));
//     type_graphinfos info = remove_edge_from_graph(graph, vertex->numc, vertex2->numc);
//     printf("depois:%d\n", are_vertex_adjacent_in_graph(graph, vertex->numc, vertex2->numc));

//     printf("random:%d\n", are_vertex_adjacent_in_graph(graph, vertex4->numc, vertex3->numc));

//     print_graph(graph, (void*)print_ver, (void*)print_ed);

//     EDGE* edge3 = malloc(sizeof(EDGE));
//     edge3->num = 9;
//     add_edge_to_graph(graph, vertex2->numc, vertex->numc);
//     set_edge_info_in_graph(graph, vertex2->numc, vertex->numc, edge3);

//     EDGE* edge4 = malloc(sizeof(EDGE));
//     edge4->num = 10;
//     add_edge_to_graph(graph, vertex4->numc, vertex3->numc);
//     set_edge_info_in_graph(graph, vertex4->numc, vertex3->numc, edge4);
    
//     print_graph(graph, (void*)print_ver, (void*)print_ed);

//     EDGE* edge11 = malloc(sizeof(EDGE));
//     edge11->num = 10;
//     add_edge_to_graph(graph, vertex3->numc, vertex2->numc);
//     set_edge_info_in_graph(graph, vertex3->numc, vertex2->numc, edge11);

//     EDGE* edge12 = malloc(sizeof(EDGE));
//     edge12->num = 33;
//     add_edge_to_graph(graph, vertex3->numc, vertex4->numc);
//     set_edge_info_in_graph(graph, vertex3->numc, vertex4->numc, edge12);

//     print_graph(graph, (void*)print_ver, (void*)print_ed);


//     type_list NEIGHBORS =  vertex_neighbors_in_graph(graph, vertex3->numc);

//     printf("LIST:\n");
//     traverse_full_list_with_conditional_action(NEIGHBORS, (void*)return_true, (void*) print_ver_l);
//     printf("\nLIST.\n");
//     NEIGHBORS = destroi_list_created_with_vertex_neighbors_in_graph(NEIGHBORS);


//     print_graph(graph, (void*)print_ver, (void*)print_ed);

//     // printf("antes2:%d\n", are_vertex_adjacent_in_graph(graph, vertex4->numc, vertex3->numc));
//     // remove_vertex_from_graph(graph, vertex3->numc, (void*)deallocate_edge);
//     // printf("depois2:%d\n", are_vertex_adjacent_in_graph(graph, vertex4->numc, vertex3->numc));

//     // print_graph(graph, (void*)print_ver, (void*)print_ed);

//     // destroi_graph(graph, (void*)deallocate_vertex, (void*)deallocate_edge);

//     // print_graph(graph, (void*)print_ver, (void*)print_ed);

    
//     printf("Empty graph (main): %d\n", empty_graph(graph));
//     printf("BEGIN dijkstras_algorithm_in_graph\n");
//     dijkstras_algorithm_in_graph(graph, vertex3->numc, (void*)get_edge_cost);
//     printf("END dijkstras_algorithm_in_graph\n");

// }