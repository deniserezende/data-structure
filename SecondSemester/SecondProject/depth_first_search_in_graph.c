
#include <stdio.h>
#include "depth_first_search_in_graph.h"

typedef struct dfs_data{
	// depth first search
	int DFS_visited;
    int DFS_starting_time;
    int DFS_finnishing_time;
	int DFS_id;
}DFS_DATA;

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
	DFS_DATA* data_for_other_algorithms;
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

int G_time;
int G_order_index;


void DFS_traverse_graph_verticies_with_action(type_graph graph, type_graphptrf_onetypeinfo action){
	GRAPH *graph_ = graph; 
	if(graph_ == NULL) return;
	
	if(empty_list(graph_->vertices)){
		printf("Graph is empty.\n"); 
        return;
	}
	int index = 0;

	set_current_to_first_item_in_list(graph_->vertices);
	int done;
	do{
		done = is_current_last_item_in_list(graph_->vertices);
		VERTEX *current_vertex = get_current_item_in_list(graph_->vertices);
		current_vertex->data_for_other_algorithms = malloc(sizeof(DFS_DATA));
    	current_vertex->data_for_other_algorithms->DFS_id = index;
		action(current_vertex);
		index++;
		move_current_forward_in_list(graph_->vertices);
	}while (!done);
	return;	
}

VERTEX* _DFS_find_unvisited_vertex_for_depth_first_search(GRAPH* graph, int order[]){
	int done;
	size_t n = graph->current_size;
	if(G_order_index >= n) return NULL;

	set_current_to_first_item_in_list(graph->vertices);
	for(int j = 1; j < order[G_order_index]; j++){
		move_current_forward_in_list(graph->vertices);
	}

	VERTEX * current_vertex = get_current_item_in_list(graph->vertices);
	G_order_index++;
	if(current_vertex->data_for_other_algorithms->DFS_visited == 0) return current_vertex;

	return _DFS_find_unvisited_vertex_for_depth_first_search(graph, order);
}

void _DFS_depth_first_search_visit_start(VERTEX* vertex){
	G_time++;
	vertex->data_for_other_algorithms->DFS_visited = 1;
	vertex->data_for_other_algorithms->DFS_starting_time = G_time;
}

void _DFS_depth_first_search_visit_finnish(VERTEX* vertex){
	G_time++;
	vertex->data_for_other_algorithms->DFS_finnishing_time = G_time;
}

void _DFS_depth_first_search_with_actions_in_graph(type_graph graph, int order[], VERTEX* from_vertex, VERTEX* vertex, type_lptrf_oneitem vertex_action_one, type_lptrf_oneitem vertex_action_two){
	_DFS_depth_first_search_visit_start(vertex);
	vertex_action_one(vertex);

	if(vertex->edges == NULL || empty_list(vertex->edges)){
		return; // stuck
	}

	set_current_to_first_item_in_list(vertex->edges);
	EDGE* edge;
	int done;
	do{
		done = is_current_last_item_in_list(vertex->edges);
		edge = get_current_item_in_list(vertex->edges);
		if(edge->to->data_for_other_algorithms->DFS_visited == 0) break;
		move_current_forward_in_list(vertex->edges);
	}while(!done);

	VERTEX* _next_vertex;
	VERTEX* _from_vertex;
	if(edge->to->data_for_other_algorithms->DFS_visited == 1){
		_next_vertex = _DFS_find_unvisited_vertex_for_depth_first_search(graph, order);
		if(_next_vertex == NULL) return; // done
		_from_vertex = NULL;
	}
	else{ // if edge has not been visited
		_next_vertex = edge->to;
		_from_vertex = vertex;
	}

	_DFS_depth_first_search_with_actions_in_graph(graph, order, _from_vertex, _next_vertex, vertex_action_one, vertex_action_two);
	_DFS_depth_first_search_visit_finnish(vertex);
	vertex_action_two(vertex);
}

void _DFS_set_up_depth_first_search_traversal_with_actions_in_graph_action(VERTEX* vertex){
	vertex->data_for_other_algorithms->DFS_visited = 0;
	vertex->data_for_other_algorithms->DFS_starting_time = 0;
	vertex->data_for_other_algorithms->DFS_finnishing_time = 0;
}

void _DFS_set_up_depth_first_search_traversal_with_actions_in_graph(type_graph graph){
	G_time = 0;
	DFS_traverse_graph_verticies_with_action(graph, (void*)_DFS_set_up_depth_first_search_traversal_with_actions_in_graph_action);
}

void DFS_depth_first_search_with_actions_in_graph(type_graph graph, int order[], type_lptrf_oneitem vertex_action_one, type_lptrf_oneitem vertex_action_two){
	GRAPH *graph_ = graph; 
	if(graph_ == NULL || empty_graph(graph_)) return;
	_DFS_set_up_depth_first_search_traversal_with_actions_in_graph(graph_);

	G_order_index = 0;
	VERTEX* vertex = _DFS_find_unvisited_vertex_for_depth_first_search(graph, order);
    _DFS_depth_first_search_with_actions_in_graph(graph_, order, NULL, vertex, vertex_action_one, vertex_action_two);
}

