#include <stdio.h>
#include "graph.h"
#include "strongly_connected_components_algorithm.h"
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

void returned(EDGE* ed1){
    return;
}

void print_ver(VERT* vert1){
    printf("%s\t%d", vert1->numc, vert1->num);
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
    sprintf(v1->numc, "a");
    add_vertex_to_graph(graph, v1->numc);
    set_vertex_info_in_graph(graph, v1->numc, v1);
    
    VERT* v2 = malloc(sizeof(VERT));
    v2->num = 2;
    sprintf(v2->numc, "b");
    add_vertex_to_graph(graph, v2->numc);
    set_vertex_info_in_graph(graph, v2->numc, v2);
    
    VERT* v3 = malloc(sizeof(VERT));
    v3->num = 3;
    sprintf(v3->numc, "c");
    add_vertex_to_graph(graph, v3->numc);
    set_vertex_info_in_graph(graph, v3->numc, v3);

    VERT* v4 = malloc(sizeof(VERT));
    v4->num = 4;
    sprintf(v4->numc, "d");
    add_vertex_to_graph(graph, v4->numc);
    set_vertex_info_in_graph(graph, v4->numc, v4);

    VERT* v5 = malloc(sizeof(VERT));
    v5->num = 5;
    sprintf(v5->numc, "e");
    add_vertex_to_graph(graph, v5->numc);
    set_vertex_info_in_graph(graph, v5->numc, v5);

    VERT* v6 = malloc(sizeof(VERT));
    v6->num = 6;
    sprintf(v6->numc, "f");
    add_vertex_to_graph(graph, v6->numc);
    set_vertex_info_in_graph(graph, v6->numc, v6);

    VERT* v7 = malloc(sizeof(VERT));
    v7->num = 7;
    sprintf(v7->numc, "g");
    add_vertex_to_graph(graph, v7->numc);
    set_vertex_info_in_graph(graph, v7->numc, v7);

    VERT* v8 = malloc(sizeof(VERT));
    v8->num = 8;
    sprintf(v8->numc, "h");
    add_vertex_to_graph(graph, v8->numc);
    set_vertex_info_in_graph(graph, v8->numc, v8);

    printf("\nINSERI OS VERTEX\n");
    print_graph(graph, (void*)print_ver, (void*)print_ed);


    EDGE* ab = malloc(sizeof(EDGE));
    ab->num = 2;
    add_edge_to_graph(graph, v1->numc, v2->numc);
    set_edge_info_in_graph(graph, v1->numc, v2->numc, ab);

    EDGE* bc = malloc(sizeof(EDGE));
    bc->num = 1;
    add_edge_to_graph(graph, v2->numc, v3->numc);
    set_edge_info_in_graph(graph, v2->numc, v3->numc, bc);

    EDGE* cd = malloc(sizeof(EDGE));
    cd->num = 3;
    add_edge_to_graph(graph, v3->numc, v4->numc);
    set_edge_info_in_graph(graph, v3->numc, v4->numc, cd);

    EDGE* dc = malloc(sizeof(EDGE));
    dc->num = 3;
    add_edge_to_graph(graph, v4->numc, v3->numc);
    set_edge_info_in_graph(graph, v4->numc, v3->numc, dc);


    EDGE* dh = malloc(sizeof(EDGE));
    dh->num = 6;
    add_edge_to_graph(graph, v4->numc, v8->numc);
    set_edge_info_in_graph(graph, v4->numc, v8->numc, dh);

    // EDGE* hh = malloc(sizeof(EDGE));
    // hh->num = 6;
    // add_edge_to_graph(graph, v8->numc, v8->numc);
    // set_edge_info_in_graph(graph, v8->numc, v8->numc, hh);

    EDGE* gh = malloc(sizeof(EDGE));
    gh->num = 9;
    add_edge_to_graph(graph, v7->numc, v8->numc);
    set_edge_info_in_graph(graph, v7->numc, v8->numc, gh);

    EDGE* cg = malloc(sizeof(EDGE));
    cg->num = 9;
    add_edge_to_graph(graph, v3->numc, v7->numc);
    set_edge_info_in_graph(graph, v3->numc, v7->numc, cg);


    EDGE* gf = malloc(sizeof(EDGE));
    gf->num = 2;
    add_edge_to_graph(graph, v7->numc, v6->numc);
    set_edge_info_in_graph(graph, v7->numc, v6->numc, gf);
    
    EDGE* fg = malloc(sizeof(EDGE));
    fg->num = 2;
    add_edge_to_graph(graph, v6->numc, v7->numc);
    set_edge_info_in_graph(graph, v6->numc, v7->numc, fg);

    EDGE* bf = malloc(sizeof(EDGE));
    bf->num = 3;
    add_edge_to_graph(graph, v2->numc, v6->numc);
    set_edge_info_in_graph(graph, v2->numc, v6->numc, bf);

    EDGE* ef = malloc(sizeof(EDGE));
    ef->num = 3;
    add_edge_to_graph(graph, v5->numc, v6->numc);
    set_edge_info_in_graph(graph, v5->numc, v6->numc, ef);

    EDGE* be = malloc(sizeof(EDGE));
    be->num = 3;
    add_edge_to_graph(graph, v2->numc, v5->numc);
    set_edge_info_in_graph(graph, v2->numc, v5->numc, be);

    EDGE* ea = malloc(sizeof(EDGE));
    ea->num = 1;
    add_edge_to_graph(graph, v5->numc, v1->numc);
    set_edge_info_in_graph(graph, v5->numc, v1->numc, ea);

    printf("\nINSERI OS EDGES\n");

    print_graph(graph, (void*)print_ver, (void*)print_ed);


    int size = get_amount_of_vertices_in_graph(graph);
    int *vector = malloc(sizeof(int) * size);
    printf("\nsize=%d\n", size);

    strongly_connected_components_algorithm(graph, vector);


    for(int i=0; i < size; i++){
        printf("%d\t", vector[i]);
    }
    print_graph(graph, (void*)print_ver, (void*)returned);

    free(vector);

    printf("\nTO NO FIM\n");

    // printf("Empty graph (main): %d\n", empty_graph(graph));
    // printf("BEGIN dijkstras_algorithm_in_graph\n");
    // dijkstras_algorithm_in_graph(graph, v1->numc, (void*)get_edge_cost);
    // printf("END dijkstras_algorithm_in_graph\n");

}