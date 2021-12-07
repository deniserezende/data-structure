#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dijkstras_algorithm.h"

typedef struct dijkstra_data{
	// dijkstra
	long dijkstra_tmp_value;
	long dijkstra_definitive_value;
	struct vertex *dijkstra_from_vertex;
}DIJKSTRA_DATA;

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
	DATA *other_data;
	DIJKSTRA_DATA *data_for_other_algorithms;
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

type_apqueue GA_PRIORITY_QUEUE;
long GA_PATHCOST;
VERTEX* GA_SOURCE;

void _dijkstras_traverse_graph_verticies_with_action(type_graph graph, type_graphptrf_onetypeinfo action){
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

VERTEX *_dijkstras_find_vertex_by_id_in_graph(type_graph graph, char id[]){
	GRAPH *graph_ = (GRAPH*) graph;
    if(graph_ == NULL) return NULL;
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

void _set_up_dijkstras_values_in_graph_action_aux(VERTEX* vertex){
    int size1 = strlen(vertex->id);
    int size2 = strlen(GA_SOURCE->id);
    int max = size1 > size2 ? size1 : size2;
    if(size2 == size1 && strncmp(GA_SOURCE->id, vertex->id, max) == 0){
        return;
    }
    vertex->data_for_other_algorithms = malloc(sizeof(DIJKSTRA_DATA));
    vertex->data_for_other_algorithms->dijkstra_tmp_value = __LONG_MAX__; 
    vertex->data_for_other_algorithms->dijkstra_from_vertex = NULL;
    insert_item_in_ascending_priority_queue(GA_PRIORITY_QUEUE, __LONG_MAX__, vertex);
}

void _set_up_dijkstras_values_in_graph_aux(GRAPH * graph, VERTEX* source, type_apqueue priority_queue){
    GA_PRIORITY_QUEUE = priority_queue;
    GA_SOURCE = source;
    _dijkstras_traverse_graph_verticies_with_action(graph, (void*)_set_up_dijkstras_values_in_graph_action_aux);
    source->data_for_other_algorithms = malloc(sizeof(DIJKSTRA_DATA));
    source->data_for_other_algorithms->dijkstra_definitive_value = 0;
    source->data_for_other_algorithms->dijkstra_from_vertex = NULL;
}

long _dijkstras_compare_two_vertex(VERTEX* vertex, VERTEX* vertex2){
    int size1 = strlen(vertex->id);
    int size2 = strlen(vertex2->id);
    int max = size1 > size2 ? size1 : size2;

    if(strncmp(vertex->id,vertex2->id, max) == 0){
        return 0;
    } 
    return -1;
}

long _dijkstras_condition_vertex(VERTEX* vertex){
    if(GA_PATHCOST < vertex->data_for_other_algorithms->dijkstra_tmp_value){
        return 1;
    }
    return 0;
}

type_list _dijkstras_algorithm_with_destination_in_graph_aux(GRAPH *graph, VERTEX* vertex_source, VERTEX* vertex_destination, type_apqueue priority_queue, type_graphptrf_onetypeinfo get_edge_value, type_list solution_array){
    // Base case: Visit the neighbors and put temporary cost values in them (in graph and in priority queue)
    VERTEX* vertex = vertex_source;
    insert_item_at_the_end_of_list(solution_array, vertex->vertex_info); 

    while(!(strcmp(vertex->id, vertex_destination->id) == 0)){
        if(empty_ascending_priority_queue(priority_queue)) break;
        if(vertex->edges != NULL){
            if(!empty_list(vertex->edges)){
                set_current_to_first_item_in_list(vertex->edges);
                int done;
                do{
                    done = is_current_last_item_in_list(vertex->edges);

                    EDGE* edge = get_current_item_in_list(vertex->edges);
                    long path_cost = (long)get_edge_value(edge->edge_info) + vertex->data_for_other_algorithms->dijkstra_definitive_value;
                    GA_PATHCOST = path_cost;

                    // Changing temporary values in priority queue
					// Edge value + previous node definitive value    
                    int changed = conditionally_change_item_priority_in_ascending_priority_queue(priority_queue, path_cost, (edge->to), (void*)_dijkstras_compare_two_vertex, (void*)_dijkstras_condition_vertex);
					
                    // If changed value in priority queue, than change in graph
					// Edge value + previous node definitive value            
                    if(changed == 1){
                        (edge->to)->data_for_other_algorithms->dijkstra_tmp_value = path_cost;
                        (edge->to)->data_for_other_algorithms->dijkstra_from_vertex = vertex;
                    }
                    move_current_forward_in_list(vertex->edges);
                }while(!done);
            }
        }
        // Get next item in priority queue
		// Set to the definitive the cost and process the vertex
        VERTEX* next_vertex = pull_item_in_ascending_priority_queue(priority_queue);
        next_vertex->data_for_other_algorithms->dijkstra_definitive_value = next_vertex->data_for_other_algorithms->dijkstra_tmp_value;
        vertex = next_vertex;
    }

    vertex = vertex_destination;
    int done;
    do{
        done = (strcmp(vertex->id, vertex_source->id) == 0);
        insert_item_at_the_end_of_list(solution_array, vertex->vertex_info); 
        vertex = vertex->data_for_other_algorithms->dijkstra_from_vertex;
    }while(!done);

    return solution_array;
}

void _dijkstras_clean_up_vertices(VERTEX* vertex){
    free(vertex->data_for_other_algorithms);
}

type_list dijkstras_algorithm_with_destination_in_graph(type_graph graph, char source_info_id[], char destination_info_id[], type_graphptrf_onetypeinfo get_edge_value){
	GRAPH *graph_ = graph; 
	VERTEX* source_node = _dijkstras_find_vertex_by_id_in_graph(graph_, source_info_id);
    VERTEX* destination_node = _dijkstras_find_vertex_by_id_in_graph(graph_, destination_info_id);
	
    // Creating a priority queue
    set_ascending_priority_queue_max_size(graph_->amount_of_vertices+1);
    type_apqueue priority_queue = create_ascending_priority_queue();
	
	// Putting temporary values in graph -> max values (infinite)
    _set_up_dijkstras_values_in_graph_aux(graph_, source_node, priority_queue);

    // Creating a list for the solution
    set_list_max_size(graph_->amount_of_vertices+1);
    type_list solution_array = create_list();

	// Doing the breadth first search traversal until the destination in processed
	solution_array = _dijkstras_algorithm_with_destination_in_graph_aux(graph_, source_node, destination_node, priority_queue, (void*)get_edge_value, solution_array);
	
    //AQUIDE cleanup function desalocar memória do DIJKSTRA DATA
    // Clean up
    _dijkstras_traverse_graph_verticies_with_action(graph, (void*)_dijkstras_clean_up_vertices);
    destroi_ascending_priority_queue(priority_queue);
    return solution_array;
}

type_list dijkstras_destroi_solution_array(type_list solution_array){
    destroi_list(solution_array);
    return NULL;
}