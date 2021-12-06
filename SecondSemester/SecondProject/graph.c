//
//  graph.c
//   
//
//  Created by Denise F. de Rezende on 03/03/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "graph.h"

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

typedef struct vertex{
	char id[41];
	type_graphinfos *vertex_info;
	type_list edges;
	DATA* other_data;
	void* data_for_other_algorithms;
}VERTEX;

typedef struct edge{
	VERTEX *to;
	type_graphinfos* edge_info;
}EDGE;

typedef struct graph{
	type_list vertices; // VERTEX *
	int amount_of_vertices;
	int amount_of_edges;
}GRAPH;

int _deallocate_edges_aux_graph(type_list edges, type_graphptrf_onetypeinfo deallocate){
	int done;
	int count = 0;
	if(edges == NULL || empty_list(edges)){
		return 0;
	}

	set_current_to_last_item_in_list(edges);
	do{
		done = is_current_first_item_in_list(edges);
		EDGE *del_edge = delete_allocated_current_item_in_list(edges);
		deallocate(del_edge->edge_info);
		free(del_edge);
		count++;
	}while(!done);
	destroi_list(edges);
	return count;
}

VERTEX* _new_vertex_for_graph_aux(GRAPH * graph, char id[]){
	VERTEX *vertex_node = malloc(sizeof(VERTEX));
	vertex_node->vertex_info = NULL;
	vertex_node->edges = NULL;
	vertex_node->other_data = malloc(sizeof(DATA));
	sprintf(vertex_node->id, "%s%c", id, '\0');
	return vertex_node;
}

VERTEX *_find_vertex_by_id_in_graph(type_graph graph, char id[]){
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

EDGE * _find_edge_by_id_in_edges_list_in_graph(type_list edges, char to_vertex_id[]){
	if(edges == NULL) return NULL;
	if(empty_list(edges)) return NULL;
	set_current_to_first_item_in_list(edges);
	int done;
	do{
		done = is_current_last_item_in_list(edges);
		EDGE *current_edge = get_current_item_in_list(edges);
		if(strcmp((current_edge->to)->id,to_vertex_id) == 0){
			return current_edge;
		}
		move_current_forward_in_list(edges);
	}while (!done);
	return NULL;
}

void _deallocate_edges_that_point_to_vertex(GRAPH *graph, char id[], type_graphptrf_onetypeinfo deallocate_edge){
	int done;
	set_current_to_first_item_in_list(graph->vertices);
	do{
		done = is_current_last_item_in_list(graph->vertices);
		
		VERTEX *vertex = get_current_item_in_list(graph->vertices);

		if(vertex->edges == NULL || empty_list(vertex->edges) || (strcmp(vertex->id,id) == 0)){
			move_current_forward_in_list(graph->vertices);
			continue;
		}
		int done_;
		set_current_to_first_item_in_list(vertex->edges);
		do{
			done_ = is_current_last_item_in_list(vertex->edges);
			EDGE *edge = get_current_item_in_list(vertex->edges);

			if(strcmp((edge->to)->id,id) == 0){
				// deletar o edge
				EDGE *del_edge = delete_allocated_current_item_in_list(vertex->edges);
				deallocate_edge(del_edge->edge_info);
				free(del_edge);
				graph->amount_of_edges--;
			}

			move_current_forward_in_list(vertex->edges);

		}while(!done_);
		move_current_forward_in_list(graph->vertices);

	}while(!done);
}

long _compare_verticies_graph(VERTEX *vertex_one, VERTEX *vertex_two){
	return strcmp(vertex_one->id,vertex_two->id);
}

type_graph create_graph(){
	GRAPH *graph = malloc(sizeof(GRAPH)); 
	graph->vertices = create_list();
	graph->amount_of_vertices = 0;
	graph->amount_of_edges = 0;
	return graph;
}

int get_amount_of_vertices_in_graph(type_graph graph){
	GRAPH *graph_ = graph; 
	return graph_->amount_of_vertices;
}

int empty_graph(type_graph graph){
	GRAPH *graph_ = graph;
	if(empty_list(graph_->vertices)) return 1;
	return 0;
}

int add_vertex_to_graph(type_graph graph, char id[]){
	GRAPH *graph_ = graph;
	VERTEX *vertex = _find_vertex_by_id_in_graph(graph_, id);
	if(vertex == NULL){
		VERTEX *vertex_node = _new_vertex_for_graph_aux(graph_, id);
		insert_item_at_the_end_of_list(graph_->vertices, vertex_node);
		graph_->amount_of_vertices++;
		return 1;
	}
	return 0;
}

int set_vertex_info_in_graph(type_graph graph, char id[], type_graphinfos vertex_info){
	GRAPH *graph_ = graph;
	VERTEX *vertex = _find_vertex_by_id_in_graph(graph_, id);
	if(vertex == NULL) return 0;
	vertex->vertex_info = vertex_info;
	return 1;
}

type_graphinfos get_vertex_info_in_graph(type_graph graph, char id[]){
	GRAPH *graph_ = graph;
	VERTEX *vertex = _find_vertex_by_id_in_graph(graph_, id);
	if(vertex != NULL) return vertex->vertex_info;
	return NULL;
}

int add_edge_to_graph(type_graph graph, char from_vertex_id[], char to_vertex_id[]){	
	GRAPH *graph_ = graph;

	VERTEX *from_vertex_node = _find_vertex_by_id_in_graph(graph_, from_vertex_id);

	if(from_vertex_node != NULL){
		VERTEX *to_vertex_node = _find_vertex_by_id_in_graph(graph_, to_vertex_id);
		if(to_vertex_node != NULL){
			EDGE *edge_node = malloc(sizeof(EDGE));
			edge_node->edge_info = NULL;
			edge_node->to = to_vertex_node;

			if(from_vertex_node->edges == NULL){
				from_vertex_node->edges = create_list();
			}
			insert_item_at_the_end_of_list(from_vertex_node->edges, edge_node);
			graph_->amount_of_edges++;
			return 1;
		}
	}
	return 0;
}

int set_edge_info_in_graph(type_graph graph, char from_vertex_id[], char to_vertex_id[], type_graphinfos edge_info){
	GRAPH *graph_ = graph;

	VERTEX *from_vertex_node = _find_vertex_by_id_in_graph(graph_, from_vertex_id);
	
	if(from_vertex_node != NULL){
		EDGE *edge_node = _find_edge_by_id_in_edges_list_in_graph(from_vertex_node->edges, to_vertex_id);

		if(edge_node != NULL){
			edge_node->edge_info = edge_info;
			return 1;
		}
	}
	return 0;
}

type_graphinfos get_edge_info_in_graph(type_graph graph, char from_vertex_id[], char to_vertex_id[]){
	GRAPH *graph_ = graph;
	VERTEX *from_vertex_node = _find_vertex_by_id_in_graph(graph_, from_vertex_id);

	if(from_vertex_node != NULL){
		if(from_vertex_node->edges == NULL) return NULL;
		if(empty_list(from_vertex_node->edges)) return NULL;

		EDGE *edge = _find_edge_by_id_in_edges_list_in_graph(from_vertex_node->edges, to_vertex_id);
		if(edge != NULL) return edge->edge_info;
	}
	return NULL;
}


type_graphinfos remove_edge_from_graph(type_graph graph, char from_vertex_id[], char to_vertex_id[]){
	GRAPH *graph_ = graph;
	VERTEX *from_vertex_node = _find_vertex_by_id_in_graph(graph_, from_vertex_id);

	if(from_vertex_node != NULL){
		if(from_vertex_node->edges == NULL) return NULL;
		if(empty_list(from_vertex_node->edges)) return NULL;

		EDGE *edge = _find_edge_by_id_in_edges_list_in_graph(from_vertex_node->edges, to_vertex_id);

		if(edge != NULL){
			EDGE *edge_del = delete_allocated_current_item_in_list(from_vertex_node->edges);
			type_graphinfos edge_info = edge_del->edge_info;
			free(edge_del);
			graph_->amount_of_edges--;
			return edge_info;
		}
	}
	return NULL;
}

type_graphinfos remove_vertex_from_graph(type_graph graph, char id[], type_graphptrf_onetypeinfo deallocate_edge){
	GRAPH *graph_ = graph;
	VERTEX *vertex_node = _find_vertex_by_id_in_graph(graph_, id);

	if(vertex_node != NULL){
		// Deallocating the vertex edges
		int amount = _deallocate_edges_aux_graph(vertex_node->edges, deallocate_edge);
		vertex_node->edges = NULL;
		graph_->amount_of_edges = graph_->amount_of_edges - amount;

		// Deallocating other vertex edges that pointed to that vertex
		_deallocate_edges_that_point_to_vertex(graph, vertex_node->id, deallocate_edge);

		delete_item_in_list(graph_->vertices, vertex_node, (void*)_compare_verticies_graph);

		type_graphinfos vertex_info = vertex_node->vertex_info;
		free(vertex_node->other_data);
		free(vertex_node);
		
		graph_->amount_of_vertices--;
		return vertex_info;
	}
	return NULL;
}

void print_graph(type_graph graph, type_graphptrf_onetypeinfo print_vertex, type_graphptrf_onetypeinfo print_edge){
	GRAPH *graph_ = graph; 
	if(graph_ == NULL) return;

	if(empty_list(graph_->vertices)){
		printf("Graph is empty.\n"); 
		return;
	}
	
	set_current_to_first_item_in_list(graph_->vertices);

	printf("----------------------\n");
	int done;
	do{
		done = is_current_last_item_in_list(graph_->vertices);
		VERTEX *current_vertex = get_current_item_in_list(graph_->vertices);

		printf("\n");
		if(current_vertex->vertex_info != NULL) print_vertex(current_vertex->vertex_info);
		else printf("[EMPTY VERTEX INFO]");
		
		int done_;

		if(current_vertex->edges == NULL || empty_list(current_vertex->edges)){
			move_current_forward_in_list(graph_->vertices);
			continue;
		} 
		else printf("\t->\t");
		
		set_current_to_first_item_in_list(current_vertex->edges);
		do {
			done_ = is_current_last_item_in_list(current_vertex->edges);
			EDGE *current_edge = get_current_item_in_list(current_vertex->edges);
			if(current_vertex->vertex_info != NULL) print_vertex((current_edge->to)->vertex_info);
			else printf("[EMPTY VERTEX INFO]");
			
			printf("[");
			if(current_edge->edge_info != NULL) print_edge(current_edge->edge_info);
			else printf("EMPTY EDGE INFO");
			printf("] ");
			if(!done_) printf("\t-\t");
			move_current_forward_in_list(current_vertex->edges);
		}while(!done_);

		move_current_forward_in_list(graph_->vertices);
	}while (!done);

	printf("\n");
	printf("----------------------\n");
	return;	
}

void destroi_graph(type_graph graph, type_graphptrf_onetypeinfo deallocate_vertex, type_graphptrf_onetypeinfo deallocate_edge){
	GRAPH *graph_ = graph; 
	if(graph_ == NULL) return;

	if(empty_list(graph_->vertices)){
		printf("Can't destroi, graph is empty\n"); return;
	}

	set_current_to_first_item_in_list(graph_->vertices);
	int done;
	do{
		done = is_current_last_item_in_list(graph_->vertices);
		VERTEX *current_vertex = get_current_item_in_list(graph_->vertices);
		
		int done_;

		_deallocate_edges_aux_graph(current_vertex->edges, deallocate_edge);
		current_vertex->edges = NULL;
		delete_current_item_in_list(graph_->vertices);
		//delete_item_in_list(graph_->vertices, current_vertex, (void*)_compare_verticies_graph);
		deallocate_vertex(current_vertex->vertex_info);
		free(current_vertex->other_data);
		free(current_vertex);

		move_current_forward_in_list(graph_->vertices);
	}while (!done);


	return;	
}

type_graphinfos are_vertex_adjacent_in_graph_return_edge(type_graph graph, char from_vertex_id[], char to_vertex_id[]){
	GRAPH *graph_ = graph; 
	// finding the "vertex from"
	VERTEX *from_vertex_node = _find_vertex_by_id_in_graph(graph_, from_vertex_id);
	if(from_vertex_node == NULL) return NULL;

	// traverse the "vertex from" list of edges to try to find the "vertex to"
	EDGE *edge = _find_edge_by_id_in_edges_list_in_graph(from_vertex_node->edges, to_vertex_id);
	if(edge != NULL) return edge->edge_info;
	return NULL;
}

int are_vertex_adjacent_in_graph(type_graph graph, char from_vertex_id[], char to_vertex_id[]){
	GRAPH *graph_ = graph; 
	// finding the "vertex from"
	VERTEX *from_vertex_node = _find_vertex_by_id_in_graph(graph_, from_vertex_id);
	if(from_vertex_node == NULL) return 0;

	// traverse the "vertex from" list of edges to try to find the "vertex to"
	EDGE *edge = _find_edge_by_id_in_edges_list_in_graph(from_vertex_node->edges, to_vertex_id);
	if(edge != NULL) return 1;
	return 0;
}

type_list vertex_neighbors_in_graph(type_graph graph, char id[]){
	GRAPH *graph_ = graph; 

	VERTEX *vertex = _find_vertex_by_id_in_graph(graph_, id);

	if(vertex == NULL) return NULL;
	if(vertex->edges == NULL) return NULL;
	if(empty_list(vertex->edges)) return NULL;

	// Creating a list of neighbors to return to the user
	type_list neighbors_list = create_list();
	int done;
	set_current_to_first_item_in_list(vertex->edges);
	do{
		done = is_current_last_item_in_list(vertex->edges);
		EDGE* current_edge = get_current_item_in_list(vertex->edges);
		insert_item_at_the_end_of_list(neighbors_list, (current_edge->to)->vertex_info);
		move_current_forward_in_list(vertex->edges);
	}while(!done);

	return neighbors_list;
}

type_list destroi_list_created_with_vertex_neighbors_in_graph(type_list list){
	destroi_list(list);
	return NULL;
}

void traverse_graph_conditional_actions(type_graph graph, type_lptrf_oneitem vertex_action, type_lptrf_oneitem vertex_condition, type_lptrf_threeitems edge_action, type_lptrf_threeitems edge_condition){
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
		
		if(vertex_condition(current_vertex->vertex_info)){
			vertex_action(current_vertex->vertex_info);
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
			
			if(edge_condition(current_vertex->vertex_info, current_edge->edge_info, (current_edge->to)->vertex_info)){
				edge_action(current_vertex->vertex_info, current_edge->edge_info, (current_edge->to)->vertex_info);
			}
			
			move_current_forward_in_list(current_vertex->edges);
		}while(!done_);


		move_current_forward_in_list(graph_->vertices);
	}while (!done);

	return;	
}

int traverse_verticies_until_conditional_action_graph(type_graph graph, type_lptrf_oneitem vertex_action, type_lptrf_oneitem vertex_condition){
	GRAPH *graph_ = graph; 
	if(graph_ == NULL) return 0;
	
	if(empty_list(graph_->vertices)){
		printf("Graph is empty.\n"); 
		return 0;
	}

	set_current_to_first_item_in_list(graph_->vertices);

	int done;
	do{
		done = is_current_last_item_in_list(graph_->vertices);
		VERTEX *current_vertex = get_current_item_in_list(graph_->vertices);
		
		if(vertex_condition(current_vertex->vertex_info)){
			vertex_action(current_vertex->vertex_info);
			return 1;
		}

		move_current_forward_in_list(graph_->vertices);
	}while (!done);

	return 0;	
}

void traverse_verticies_with_conditional_action_graph(type_graph graph, type_lptrf_oneitem vertex_action, type_lptrf_oneitem vertex_condition){
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
		
		if(vertex_condition(current_vertex->vertex_info)){
			vertex_action(current_vertex->vertex_info);
		}

		move_current_forward_in_list(graph_->vertices);
	}while (!done);

	return;	
}

type_graph duplicate_graph_with_conditionals(type_graph graph, type_lptrf_oneitem vertex_condition, type_lptrf_threeitems edge_condition){
	GRAPH* graph_ = graph; 
	if(graph_ == NULL) return NULL;
	GRAPH* duplicated_graph = create_graph();
	if(empty_list(graph_->vertices)){
		printf("Graph is empty.\n"); 
		return duplicated_graph;
	}

	// Inserting vertex
	set_current_to_first_item_in_list(graph_->vertices);
	int done;
	do{
		done = is_current_last_item_in_list(graph_->vertices);
		VERTEX *current_vertex = get_current_item_in_list(graph_->vertices);
		
		if((long)vertex_condition(current_vertex->vertex_info)){
			add_vertex_to_graph(duplicated_graph, current_vertex->id);
			set_vertex_info_in_graph(duplicated_graph, current_vertex->id, current_vertex->vertex_info);
		}
		move_current_forward_in_list(graph_->vertices);
	}while (!done);

	// Inserting edges
	set_current_to_first_item_in_list(graph_->vertices);
	do{
		done = is_current_last_item_in_list(graph_->vertices);
		VERTEX *current_vertex = get_current_item_in_list(graph_->vertices);
		
		if((long)vertex_condition(current_vertex->vertex_info)){
			if(current_vertex->edges == NULL || empty_list(current_vertex->edges)){
				move_current_forward_in_list(graph_->vertices);
				continue;
			} 
			int done_;

			set_current_to_first_item_in_list(current_vertex->edges);
			do {
				done_ = is_current_last_item_in_list(current_vertex->edges);
				EDGE *current_edge = get_current_item_in_list(current_vertex->edges);
				
				if((long)edge_condition(current_vertex->vertex_info, current_edge->edge_info, (current_edge->to)->vertex_info)){
					add_edge_to_graph(duplicated_graph, current_vertex->id, (current_edge->to)->id);
					set_edge_info_in_graph(duplicated_graph, current_vertex->id, (current_edge->to)->id, current_edge->edge_info);
				}
				move_current_forward_in_list(current_vertex->edges);
			}while(!done_);
		}
		move_current_forward_in_list(graph_->vertices);
	}while (!done);

	return duplicated_graph;	
}

type_graph create_reverse_graph_with_conditionals(type_graph base_graph, type_lptrf_oneitem vertex_condition, type_lptrf_threeitems edge_condition){
	GRAPH *graph_ = base_graph; 
	if(graph_ == NULL) return NULL;
	
	type_graph reversed_graph = create_graph();
	if(empty_list(graph_->vertices)){
		printf("Graph is empty.\n"); 
		return reversed_graph;
	}

	// Inserting vertex
	set_current_to_first_item_in_list(graph_->vertices);
	int done;
	do{
		done = is_current_last_item_in_list(graph_->vertices);
		VERTEX *current_vertex = get_current_item_in_list(graph_->vertices);
		
		if((long)vertex_condition(current_vertex->vertex_info)){
			add_vertex_to_graph(reversed_graph, current_vertex->id);
			set_vertex_info_in_graph(reversed_graph, current_vertex->id, current_vertex->vertex_info);
		}
		move_current_forward_in_list(graph_->vertices);
	}while (!done);

	// Inserting revesed edges 
	set_current_to_first_item_in_list(graph_->vertices);
	do{
		done = is_current_last_item_in_list(graph_->vertices);
		VERTEX *current_vertex = get_current_item_in_list(graph_->vertices);
		if((long)vertex_condition(current_vertex->vertex_info)){
			if(current_vertex->edges == NULL || empty_list(current_vertex->edges)){
				move_current_forward_in_list(graph_->vertices);
				continue;
			} 
			int done_;

			set_current_to_first_item_in_list(current_vertex->edges);
			do {
				done_ = is_current_last_item_in_list(current_vertex->edges);
				EDGE *current_edge = get_current_item_in_list(current_vertex->edges);
				
				if((long)edge_condition(current_vertex->vertex_info, current_edge->edge_info, (current_edge->to)->vertex_info)){
					add_edge_to_graph(reversed_graph, (current_edge->to)->id, current_vertex->id);
					set_edge_info_in_graph(reversed_graph, (current_edge->to)->id, current_vertex->id, current_edge->edge_info);
				}
				move_current_forward_in_list(current_vertex->edges);
			}while(!done_);
		}
		move_current_forward_in_list(graph_->vertices);
	}while (!done);

	return reversed_graph;	
}

// breadth_first_search +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

long G_PATHCOST;
type_apqueue G_PRIORITY_QUEUE;
VERTEX* G_SOURCE;

void _traverse_graph_verticies_with_action(type_graph graph, type_graphptrf_onetypeinfo action){
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
		action(current_vertex);
		move_current_forward_in_list(graph_->vertices);
	}while (!done);
	return;	
}

void _set_up_traverse_breadth_search_values_in_graph_action_aux(VERTEX* vertex){
    int size1 = strlen(vertex->id);
    int size2 = strlen(G_SOURCE->id);
    int max = size1 > size2 ? size1 : size2;
    if(size2 == size1 && strncmp(G_SOURCE->id, vertex->id, max) == 0){
        return;
    }
    vertex->other_data->bfs_tmp_value = __LONG_MAX__; 
    vertex->other_data->bfs_from_vertex = NULL;
    insert_item_in_ascending_priority_queue(G_PRIORITY_QUEUE, __LONG_MAX__, vertex);
}

void _set_up_traverse_breadth_search_values_in_graph_aux(GRAPH * graph, VERTEX* source, type_apqueue priority_queue){
    G_PRIORITY_QUEUE = priority_queue;
    G_SOURCE = source;
    _traverse_graph_verticies_with_action(graph, (void*)_set_up_traverse_breadth_search_values_in_graph_action_aux);
    source->other_data->bfs_def_value = 0;
    source->other_data->bfs_from_vertex = NULL;
}

long _compare_two_vertex_in_graph(VERTEX* vertex, VERTEX* vertex2){
    int size1 = strlen(vertex->id);
    int size2 = strlen(vertex2->id);
    int max = size1 > size2 ? size1 : size2;

    if(strncmp(vertex->id,vertex2->id, max) == 0){
        return 0;
    } 
    return -1;
}

long _condition_vertex_for_traverse_breadth_search_in_graph(VERTEX* vertex){
    if(G_PATHCOST < vertex->other_data->bfs_tmp_value){
        return 1;
    }
    return 0;
}

void _traverse_breadth_first_search_with_conditional_actions_in_graph(GRAPH *graph, VERTEX* vertex_source, type_apqueue priority_queue, type_lptrf_oneitem vertex_action, type_lptrf_oneitem vertex_condition, type_lptrf_threeitems edge_action, type_lptrf_threeitems edge_condition){
    // Base case: Visit the neighbors and put temporary cost values in them (in graph and in priority queue)
    VERTEX* vertex = vertex_source;

    while(!empty_ascending_priority_queue(priority_queue)){

		if((long)vertex_condition(vertex->vertex_info)){
			vertex_action(vertex->vertex_info);
		}

        if(vertex->edges != NULL){
            if(!empty_list(vertex->edges)){
                set_current_to_first_item_in_list(vertex->edges);
                int done;
                do{
                    done = is_current_last_item_in_list(vertex->edges);

                    EDGE* edge = get_current_item_in_list(vertex->edges);
                    long path_cost = (long) 1 + vertex->other_data->bfs_def_value;
                    G_PATHCOST = path_cost;

                    // Changing temporary values in priority queue
					// Edge value + previous node definitive value                    
                    int changed = conditionally_change_item_priority_in_ascending_priority_queue(priority_queue, path_cost, (edge->to), (void*)_compare_two_vertex_in_graph, (void*)_condition_vertex_for_traverse_breadth_search_in_graph);
                    
					// If changed value in priority queue, than change in graph
					// Edge value + previous node definitive value                
                    if(changed == 1){
                        (edge->to)->other_data->bfs_tmp_value = path_cost;
                        (edge->to)->other_data->bfs_from_vertex = vertex;
                    }

					if((long)edge_condition(vertex->vertex_info, edge->edge_info, (edge->to)->vertex_info)){
						edge_action(vertex->vertex_info, edge->edge_info, (edge->to)->vertex_info);
					}

                    move_current_forward_in_list(vertex->edges);
                }while(!done);
            }
        }
		// Get next item in priority queue
		// Set to the definitive the cost and process the vertex
        VERTEX* next_vertex = pull_item_in_ascending_priority_queue(priority_queue);
        next_vertex->other_data->bfs_def_value = next_vertex->other_data->bfs_tmp_value;
        vertex = next_vertex;
    }
}

void breadth_first_search_traversal_with_conditional_actions_in_graph(type_graph graph, char source[], type_lptrf_oneitem vertex_action, type_lptrf_oneitem vertex_condition, type_lptrf_threeitems edge_action, type_lptrf_threeitems edge_condition){
	GRAPH *graph_ = graph; 
	VERTEX* source_node = _find_vertex_by_id_in_graph(graph_, source);

	// Creating a priority queue
    set_ascending_priority_queue_max_size(graph_->amount_of_vertices+1);
    type_apqueue priority_queue = create_ascending_priority_queue();

	// Putting temporary values in graph -> max values (infinite)
	_set_up_traverse_breadth_search_values_in_graph_aux(graph_, source_node, priority_queue);

	// Doing the breadth first search traversal
	_traverse_breadth_first_search_with_conditional_actions_in_graph(graph_, source_node, priority_queue, vertex_action, vertex_condition, edge_action, edge_condition);

    return;
}