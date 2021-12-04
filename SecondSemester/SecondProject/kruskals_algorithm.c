
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "kruskals_algorithm.h"

typedef struct kruskals_data{
	// kruskals
    int kruskals_index;
}KRUSKALS_DATA;

typedef struct vertex_aux_data{
	// depth first search
	int dfs_visited;
    int dfs_starting_time;
    int dfs_finnishing_time;

	// breadth first search
	long bfs_tmp_value;
	long bfs_def_value;
	struct vertex *bfs_from_vertex;
}DATA;

// // testar se vai assim:
// // se der mudar nos outros externos
// typedef struct vertex_aux_data{
// 	// kruskals
//     int kruskals_index;
// }DATA;

typedef struct vertex{
	char id[41];
	type_graphinfos *vertex_info;
	type_list edges;
	DATA *other_data;
	KRUSKALS_DATA *data_for_other_algorithms;
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

void _kruskals_traverse_graph_conditional_actions(type_graph graph, type_lptrf_oneitem vertex_action, type_lptrf_oneitem vertex_condition, type_lptrf_threeitems edge_action, type_lptrf_threeitems edge_condition){
	GRAPH *graph_ = graph; 
	if(graph_ == NULL) return;
    int in = 0;
	
	if(empty_list(graph_->vertices)){
		printf("Graph is empty.\n"); return;
	}

	set_current_to_first_item_in_list(graph_->vertices);

	int done;
	do{
		done = is_current_last_item_in_list(graph_->vertices);
		VERTEX *current_vertex = get_current_item_in_list(graph_->vertices);
		
		if((long)vertex_condition(current_vertex)){
			vertex_action(current_vertex);
		}

		if(current_vertex->edges == NULL || empty_list(current_vertex->edges)){
			move_current_forward_in_list(graph_->vertices);
			continue;
		} 

		int done_;
		set_current_to_first_item_in_list(current_vertex->edges);
		do {
            in++;
			done_ = is_current_last_item_in_list(current_vertex->edges);
			EDGE *current_edge = get_current_item_in_list(current_vertex->edges);
			
			if((long)edge_condition(current_vertex, current_edge, (current_edge->to))){
				edge_action(current_vertex, current_edge, (current_edge->to));
			}
			
			move_current_forward_in_list(current_vertex->edges);
		}while(!done_);


		move_current_forward_in_list(graph_->vertices);
	}while (!done);

    printf("era para ter.... %d\n", in);
	return;	
}


void _kruskals_traverse_verticies_with_conditional_action_graph(type_graph graph, type_lptrf_oneitem vertex_action, type_lptrf_oneitem vertex_condition){
	GRAPH *graph_ = graph; 
	if(graph_ == NULL) return;
	
	if(empty_list(graph_->vertices)){
		printf("Graph is empty.\n"); 
		return;
	}

	set_current_to_first_item_in_list(graph_->vertices);

	int done;
	do{
		done = is_current_last_item_in_list(graph_->vertices);
		VERTEX *current_vertex = get_current_item_in_list(graph_->vertices);
		
		if(vertex_condition(current_vertex)){
			vertex_action(current_vertex);
		}

		move_current_forward_in_list(graph_->vertices);
	}while (!done);

	return;	
}


VERTEX *_kruskals_find_vertex_by_id_in_graph(type_graph graph, char id[]){
	GRAPH *graph_ = graph;
	if(graph_->vertices == NULL) return NULL;
	if(empty_list(graph_->vertices)) return NULL;

	set_current_to_first_item_in_list(graph_->vertices);
	int done;
	do{
		done = is_current_last_item_in_list(graph_->vertices);
		VERTEX *current_vertex = get_current_item_in_list(graph_->vertices);
		if(strcmp(current_vertex->id,id) == 0){
			return current_vertex;
		}
		move_current_forward_in_list(graph_->vertices);
	}while (!done);
	return NULL;
}

type_disjoint_sets KA_union_find;
type_apqueue KA_edges;
type_graphptrf_onetypeinfo* KA_get_edge_value;
int KA_index;
int *KA_vector_solution;
type_graph KA_solution_graph;

long _kruskals_true_vertex(VERTEX* vertex){
    return 1;
}

long _kruskals_true_edge(VERTEX* from_vertex, EDGE* edge, VERTEX* to_vertex){
    return 1;
}

long _kruskals_false_edge(VERTEX* from_vertex, EDGE* edge, VERTEX* to_vertex){
    return 0;
}
void _kruskals_do_nothing_edge(VERTEX* from_vertex, EDGE* edge, VERTEX* to_vertex){
    return;
}
// ou aqui o problem
void _kruskals_edges_action_edge(VERTEX* from_vertex, EDGE* edge, VERTEX* to_vertex){
    printf("no _kruskals_edges_action_edge\n");
    KEDGE* kedge = malloc(sizeof(KEDGE));
    kedge->from = from_vertex;
    kedge->to = to_vertex;
    kedge->edge = edge;
    long key = (long)KA_get_edge_value(edge->edge_info);
    insert_item_in_ascending_priority_queue(KA_edges, key, kedge);
}

VERTEX* _kruskals_new_vertex_for_graph_aux(GRAPH * graph, char id[]){
	VERTEX *vertex_node = malloc(sizeof(VERTEX));
    vertex_node->other_data = malloc(sizeof(DATA));
    vertex_node->data_for_other_algorithms = malloc(sizeof(KRUSKALS_DATA));
	vertex_node->vertex_info = NULL;
	vertex_node->edges = NULL;
	sprintf(vertex_node->id, "%s%c", id, '\0');
	return vertex_node;
}

VERTEX * _kruskals_add_vertex_to_graph(type_graph graph, char id[]){
	GRAPH *graph_ = graph;
    VERTEX *vertex_node = _kruskals_new_vertex_for_graph_aux(graph_, id);
    insert_item_at_the_end_of_list(graph_->vertices, vertex_node);
    graph_->current_size++;
    return vertex_node;
}
// ou aqui o problem
void _kruskals_union_find_action_vertex(VERTEX* vertex){
    printf("no _kruskals_union_find_action_vertex\n");
	vertex->data_for_other_algorithms = malloc(sizeof(KRUSKALS_DATA));
    vertex->data_for_other_algorithms->kruskals_index = making_a_new_set_containing_a_new_element(KA_union_find, vertex);
    VERTEX* vertex_added = _kruskals_add_vertex_to_graph(KA_solution_graph, vertex->id);
    printf("depois do  vertex_added\n");
    vertex_added->vertex_info = vertex->vertex_info;
    printf("depois do vertex_added->vertex_info\n");
    // nessa linhas
    vertex_added->data_for_other_algorithms->kruskals_index  = vertex->data_for_other_algorithms->kruskals_index;
    return;
}
// sipa o problema tá aqui
void _set_up_kruskals_union_find_and_edges_aux(type_graph graph, type_disjoint_sets union_find, type_apqueue edges, type_graph solution_graph){
    KA_union_find = union_find;
    KA_edges = edges;
    KA_solution_graph = solution_graph;
    printf("setei o basico\n");
    _kruskals_traverse_graph_conditional_actions(graph, (void*)_kruskals_union_find_action_vertex, (void*)_kruskals_true_vertex, (void*)_kruskals_edges_action_edge, (void*)_kruskals_true_edge);
}

void print_edd(KEDGE *kedge){
    long v = (long)KA_get_edge_value((kedge->edge)->edge_info);
    printf("e=%ld \t", v);
}




type_graph _kruskals_algorithm_in_graph(type_graph graph, type_apqueue edges, type_disjoint_sets union_find, type_graph solution_graph){
    int amount_of_minimum_edges = 0;
    int amount_of_vertex = get_disjoint_sets_max(union_find);

    while(amount_of_minimum_edges < amount_of_vertex-1){
        if(empty_ascending_priority_queue(edges)) break; // to só colocando um break por enquanto
        // sem warning "AQUIDE"
        KEDGE* kedge = pull_item_in_ascending_priority_queue(edges);

        int from_index = (kedge->from)->data_for_other_algorithms->kruskals_index;
        int to_index = (kedge->to)->data_for_other_algorithms->kruskals_index;
        int representive_from = finding_the_representative_of_the_set_containing_element_in_disjoint_sets(union_find, from_index);
        int representive_to = finding_the_representative_of_the_set_containing_element_in_disjoint_sets(union_find, to_index);
        if(representive_from != representive_to){
            merging_two_sets_in_disjoint_sets(union_find, from_index, to_index);
            amount_of_minimum_edges++;


            // COLOCANDO NO GRAFO SOLUCAO
            // verificar se já existe
            EDGE* edge = get_edge_info_in_graph(solution_graph, (kedge->from)->id, (kedge->to)->id);

            if(edge == NULL){
                add_edge_to_graph(solution_graph, (kedge->from)->id, (kedge->to)->id);
                set_edge_info_in_graph(solution_graph, (kedge->from)->id, (kedge->to)->id, (kedge->edge)->edge_info);

                add_edge_to_graph(solution_graph, (kedge->to)->id, (kedge->from)->id);
                set_edge_info_in_graph(solution_graph, (kedge->to)->id, (kedge->from)->id, (kedge->edge)->edge_info);
            }
        }
        free(kedge);
    }
    return solution_graph;
}

void _kruskals_clean_up_vertices(VERTEX* vertex){
    free(vertex->data_for_other_algorithms);
}

type_graph kruskals_algorithm_in_graph(type_graph graph, type_graphptrf_onetypeinfo get_edge_value){
	GRAPH *graph_ = graph; 
    type_graph solution_graph = create_graph();
    KA_get_edge_value = get_edge_value;
    
    set_ascending_priority_queue_max_size(graph_->amount_of_edges + 1);

    // criar uma lista de arestas
    type_apqueue edges = create_ascending_priority_queue();

    // criar um union find com os verticies
    type_disjoint_sets union_find = start_disjoint_sets(graph_->current_size);

    // inserir todos os vertices no meu union find
    // inserir todas as arestas no priority queue
    _set_up_kruskals_union_find_and_edges_aux(graph_, union_find, edges, solution_graph);

    print_ascending_priority_queue(edges, (void*)print_edd);

    // analizar as arestas
    solution_graph = _kruskals_algorithm_in_graph(graph_, edges, union_find, solution_graph);

	//AQUIDE cleanup function desalocar memória do KRUSKALS_DATA
    _kruskals_traverse_graph_conditional_actions(graph, (void*)_kruskals_clean_up_vertices, (void*)_kruskals_true_vertex, (void*)_kruskals_do_nothing_edge, (void*)_kruskals_false_edge);
    return solution_graph;
}