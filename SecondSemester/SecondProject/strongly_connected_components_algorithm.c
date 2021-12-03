
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "strongly_connected_components_algorithm.h"

typedef struct vertex_aux_data{
	// dijkstra
	long dijkstra_tmp_value;
	long dijkstra_definitive_value;
	struct vertex *dijkstra_from_vertex;
	
	// kruskals
    int kruskals_index;

	// depth first search
	int dfs_visited;
    int dfs_starting_time;
    int dfs_finnishing_time;

	// breadth first search
	long bfs_tmp_value;
	long bfs_def_value;
	struct vertex *bfs_from_vertex;
}DATA;

typedef struct vertex{
	char id[41];
	type_graphinfos *vertex_info;
	type_list edges;
	DATA *data_for_other_algorithms;
}VERTEX;

typedef struct edge{
	VERTEX *to;
	type_graphinfos* edge_info;
}EDGE;

typedef struct graph{
	type_list vertices; // VERTEX
	int current_size; // amount of vertices
	int amount_of_edges;
}GRAPH;

long reverse_graph_vertex_condition(type_graphinfos vertex){
    return 1;
}

long reverse_graph_edge_condition(type_graphinfos from_vertex, type_graphinfos edge, type_graphinfos to_vertex){
    return 1;
}

type_graph strongly_connected_components_algorithm(type_graph graph, type_graphptrf_onetypeinfo get_edge_value, int solution_vector[]){
    GRAPH* graph_ = graph;

    // setup order vector (depois arrumar)
    int order[graph_->current_size];
    for(int i=0; i < graph_->current_size; i++){
        order[i] = i;
    }
    
// 1 call DFS.G/ to compute finishing times u:f for each vertex u 
    depth_first_search_traversal_with_conditional_actions_in_graph(graph, order, type_lptrf_oneitem vertex_action, type_lptrf_oneitem vertex_condition, type_lptrf_threeitems edge_action, type_lptrf_threeitems edge_condition){

// 2 compute GT
    type_graph reversed_graph = create_reverse_graph_with_conditionals(graph, (void*)reverse_graph_vertex_condition, (void*)reverse_graph_edge_condition);

    // setup order vector para ser a ordem inversa do outro
    // é so inverter esse vetor??????????????????????????????????
    // acho que não

// 3 call DFS.GT/, but in the main loop of DFS, consider the vertices in order of decreasing u:f (as computed in line 1)
    // setup order vector (depois arrumar)
    int decreasing_order[graph_->current_size];
    for(int i=0; i < graph_->current_size; i++){
        decreasing_order[i] = order[graph_->current_size - i];
    }
    depth_first_search_traversal_with_conditional_actions_in_graph(reversed_graph, decreasing_order, type_lptrf_oneitem vertex_action, type_lptrf_oneitem vertex_condition, type_lptrf_threeitems edge_action, type_lptrf_threeitems edge_condition){

// 4 output the vertices of each tree in the depth-first forest formed in line 3 as a separate strongly connected component
    // criar um grafo com as componentes
    // e colocar em um vetor a qual componente pertence



}


