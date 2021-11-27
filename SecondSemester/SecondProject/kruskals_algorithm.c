
#include <stdio.h>
#include <string.h>
#include "kruskals_algorithm.h"

typedef struct vertex{
	char id[41];
	type_graphinfos *vertex_info;
	type_list edges;

	long dijkstra_tmp_value;
	long dijkstra_definitive_value;
	struct vertex *dijkstra_from_vertex;
    int kruskals_index;
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

typedef struct edge_kruskals{
    VERTEX *from;
	VERTEX *to;
    EDGE *edge;
}KEDGE; 

void _traverse_graph_conditional_actions_kruskals(type_graph graph, type_lptrf_oneitem vertex_action, type_lptrf_oneitem vertex_condition, type_lptrf_threeitems edge_action, type_lptrf_threeitems edge_condition){
	GRAPH *graph_ = graph; 
	if(graph_ == NULL) return;
	
	if(empty_list(graph_->vertices)){
		printf("Graph is empty.\n"); return;
	}

	set_current_to_first_item_in_list(graph_->vertices);

	int done;
	do{
		done = is_current_last_item_in_list(graph_->vertices);
		VERTEX *current_vertex = get_current_item_in_list(graph_->vertices);
		
		if(vertex_condition(current_vertex)){
			vertex_action(current_vertex);
		}
		int done_;

		if(current_vertex->edges == NULL || empty_list(current_vertex->edges)){
			move_current_forward_in_list(graph_->vertices);
			continue;
		} 
		
		set_current_to_first_item_in_list(current_vertex->edges);
		do {
			done_ = is_current_last_item_in_list(current_vertex->edges);
			EDGE *current_edge = get_current_item_in_list(current_vertex->edges);
			
			if(edge_condition(current_vertex, current_edge, (current_edge->to))){
				edge_action(current_vertex, current_edge, (current_edge->to));
			}
			
			move_current_forward_in_list(current_vertex->edges);
		}while(!done_);


		move_current_forward_in_list(graph_->vertices);
	}while (!done);

	return;	
}

type_disjoint_sets KA_union_find;
type_apqueue KA_edges;
type_graphptrf_onetypeinfo* KA_get_edge_value;


long _kruskals_true_vertex(VERTEX* vertex){
    return 1;
}

long _kruskals_true_edge(VERTEX* from_vertex, EDGE* edge, VERTEX* to_vertex){
    return 1;
}

void _kruskals_edges_action_edge(VERTEX* from_vertex, EDGE* edge, VERTEX* to_vertex){
    KEDGE* kedge = malloc(sizeof(KEDGE));
    kedge->from = from_vertex;
    kedge->to = to_vertex;
    kedge->edge = edge;
    insert_item_in_ascending_priority_queue(KA_edges, KA_get_edge_value(edge->edge_info), kedge);
}
void _kruskals_union_find_action_vertex(VERTEX* vertex){
    vertex->kruskals_index = making_a_new_set_containing_a_new_element(KA_union_find, vertex);
    return;
}

void _set_up_kruskals_union_find_and_edges_aux(type_graph graph, type_disjoint_sets union_find, type_apqueue edges){
    KA_union_find = union_find;
    KA_edges = edges;
    _traverse_graph_conditional_actions_kruskals(graph, (void*)_kruskals_union_find_action_vertex, (void*)_kruskals_true_vertex, (void*)_kruskals_edges_action_edge, (void*)_kruskals_true_edge);
}


type_list kruskals_algorithm_in_graph(type_graph graph, type_graphptrf_onetypeinfo get_edge_value){
	GRAPH *graph_ = graph; 
    KA_get_edge_value = get_edge_value;

    // criar uma lista de arestas
    type_apqueue edges = create_ascending_priority_queue();
    // criar um union find com os verticies
    type_disjoint_sets union_find = start_disjoint_sets(graph_->current_size);

    // inserir todos os vertices no meu union find
    // inserir todas as arestas no priority queue
    _set_up_kruskals_union_find_and_edges_aux(graph_, union_find, edges);

    // analizar as arestas
    _kruskals_algorithm_in_graph(graph_, edges, union_find);
}

type_list _kruskals_algorithm_in_graph(type_graph graph, type_apqueue edges, type_disjoint_sets union_find){
    int amount_of_minimum_edges = 0;
    int amount_of_vertex = get_disjoint_sets_max(union_find);

    while(amount_of_minimum_edges < amount_of_vertex-1){
        KEDGE* kedge = pull_item_in_ascending_priority_queue(edges);
        int from_index = (kedge->from)->kruskals_index;
        int to_index = (kedge->to)->kruskals_index;
        int representive_from = finding_the_representative_of_the_set_containing_element_in_disjoint_sets(union_find, from_index);
        int representive_to = finding_the_representative_of_the_set_containing_element_in_disjoint_sets(union_find, to_index);
        if(representive_from != representive_to){
            merging_two_sets_in_disjoint_sets(union_find, from_index, to_index);
            amount_of_minimum_edges++;
        }
        free(kedge);
    }
}