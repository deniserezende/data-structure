
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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

void _kruskals_traverse_graph_conditional_actions(type_graph graph, type_lptrf_oneitem vertex_action, type_lptrf_oneitem vertex_condition, type_lptrf_threeitems edge_action, type_lptrf_threeitems edge_condition){
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

void _kruskals_edges_action_edge(VERTEX* from_vertex, EDGE* edge, VERTEX* to_vertex){
    KEDGE* kedge = malloc(sizeof(KEDGE));
    kedge->from = from_vertex;
    kedge->to = to_vertex;
    kedge->edge = edge;
    long key = (long)KA_get_edge_value(edge->edge_info);
    insert_item_in_ascending_priority_queue(KA_edges, key, kedge);
}

VERTEX* _kruskals_new_vertex_for_graph_aux(GRAPH * graph, char id[]){
	VERTEX *vertex_node = malloc(sizeof(VERTEX));
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

void _kruskals_union_find_action_vertex(VERTEX* vertex){
    vertex->kruskals_index = making_a_new_set_containing_a_new_element(KA_union_find, vertex);
    VERTEX* vertex_added = _kruskals_add_vertex_to_graph(KA_solution_graph, vertex->id);
    vertex_added->vertex_info = vertex->vertex_info;
    vertex_added->kruskals_index = vertex->kruskals_index;
    return;
}

void _set_up_kruskals_union_find_and_edges_aux(type_graph graph, type_disjoint_sets union_find, type_apqueue edges, type_graph solution_graph){
    KA_union_find = union_find;
    KA_edges = edges;
    KA_solution_graph = solution_graph;
    _kruskals_traverse_graph_conditional_actions(graph, (void*)_kruskals_union_find_action_vertex, (void*)_kruskals_true_vertex, (void*)_kruskals_edges_action_edge, (void*)_kruskals_true_edge);
}

void print_edd(KEDGE *kedge){
    long v = (long)KA_get_edge_value((kedge->edge)->edge_info);
    printf("e=%lf \t", v);
}




type_graph _kruskals_algorithm_in_graph(type_graph graph, type_apqueue edges, type_disjoint_sets union_find, type_graph solution_graph){
    int amount_of_minimum_edges = 0;
    int amount_of_vertex = get_disjoint_sets_max(union_find);


    while(amount_of_minimum_edges < amount_of_vertex-1){
        if(empty_ascending_priority_queue(edges)) break; // to só colocando um break por enquanto
        // sem warning "AQUIDE"
        KEDGE* kedge = pull_item_in_ascending_priority_queue(edges);
        print_ascending_priority_queue(edges, (void*)print_edd);
        printf("\n");

        int from_index = (kedge->from)->kruskals_index;
        int to_index = (kedge->to)->kruskals_index;
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

type_graph kruskals_algorithm_in_graph(type_graph graph, type_graphptrf_onetypeinfo get_edge_value){
	GRAPH *graph_ = graph; 
    type_graph solution_graph = create_graph();
    KA_get_edge_value = get_edge_value;

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

    return solution_graph;
}







void _kruskals_algorithm_in_graph_forest_action(VERTEX* vertex){
    printf("vertex->kruskals_index=%d\n", vertex->kruskals_index);
    int representative_index = finding_the_representative_of_the_set_containing_element_in_disjoint_sets(KA_union_find, vertex->kruskals_index);
    printf("representative_index=%d\n", representative_index);
    KA_vector_solution[KA_index] = representative_index;
    KA_index++;
}


type_graph _kruskals_algorithm_in_graph_forest(type_graph graph, type_apqueue edges, type_disjoint_sets union_find, type_graph solution_graph, int vector[]){
    int amount_of_minimum_edges = 0;
    int amount_of_vertex = get_disjoint_sets_max(union_find);

    while(amount_of_minimum_edges < amount_of_vertex-1 && !empty_ascending_priority_queue(edges)){

        KEDGE* kedge = pull_item_in_ascending_priority_queue(edges);
        print_ascending_priority_queue(edges, (void*)print_edd);

        int from_index = (kedge->from)->kruskals_index;
        int to_index = (kedge->to)->kruskals_index;
        int representive_from = finding_the_representative_of_the_set_containing_element_in_disjoint_sets(union_find, from_index);
        int representive_to = finding_the_representative_of_the_set_containing_element_in_disjoint_sets(union_find, to_index);

        if(representive_from != representive_to){
            merging_two_sets_in_disjoint_sets(union_find, from_index, to_index);
            amount_of_minimum_edges++;


            // COLOCANDO NO GRAFO SOLUCAO
            // verificar se já existe
            add_edge_to_graph(solution_graph, (kedge->from)->id, (kedge->to)->id);
            set_edge_info_in_graph(solution_graph, (kedge->from)->id, (kedge->to)->id, (kedge->edge)->edge_info);

        }
        printf("fim do while\n");
        free(kedge);
    }

    int amount_of_spanning_tree = amount_of_vertex - amount_of_minimum_edges;

    KA_vector_solution = vector;
    KA_union_find = union_find;
    KA_index = 0;
    _kruskals_traverse_verticies_with_conditional_action_graph(solution_graph, (void*)_kruskals_algorithm_in_graph_forest_action, (void*)_kruskals_true_vertex);

    return solution_graph;
}

type_graph kruskals_algorithm_in_graph_forest(type_graph graph, type_graphptrf_onetypeinfo get_edge_value, int vector[]){
	GRAPH *graph_ = graph; 
    type_graph solution_graph = create_graph();
    KA_get_edge_value = get_edge_value;

    // criar uma lista de arestas
    type_apqueue edges = create_ascending_priority_queue();
    // criar um union find com os verticies
    type_disjoint_sets union_find = start_disjoint_sets(graph_->current_size);

    // inserir todos os vertices no meu union find
    // inserir todas as arestas no priority queue
    _set_up_kruskals_union_find_and_edges_aux(graph_, union_find, edges, solution_graph);

    print_ascending_priority_queue(edges, (void*)print_edd);

    // analizar as arestas
    solution_graph = _kruskals_algorithm_in_graph_forest(graph_, edges, union_find, solution_graph, vector);

    return solution_graph;
}