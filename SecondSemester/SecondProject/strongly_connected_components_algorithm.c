
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "strongly_connected_components_algorithm.h" 

typedef struct dfs_data{
	// depth first search
	int SCCA_visited;
    int SCCA_starting_time;
    int SCCA_finnishing_time;
	int SCCA_id;
	int SCCA_component;
}DFS_DATA;

typedef struct vertex_aux_data{
	// depth first search
	int SCCA_visited;
    int SCCA_starting_time;
    int SCCA_finnishing_time;

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
	type_list vertices; // VERTEX*
	int amount_of_vertices;
	int amount_of_edges;
}GRAPH;

int *SCCA_finishing_time;
int *SCCA_order;
int *SCCA_backorder;
int *SCCA_solution;
int SCCA_index;

int DFS_time;
int DFS_done;
int DFS_index_components;


void _DFS_traverse_graph_verticies_with_action(type_graph graph, type_graphptrf_onetypeinfo action){
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

void _DFS_depth_first_search_visit_start(VERTEX* vertex){
	DFS_time++;
	vertex->data_for_other_algorithms->SCCA_visited = 1;
	vertex->data_for_other_algorithms->SCCA_starting_time = DFS_time;
}

void _DFS_depth_first_search_visit_finnish(VERTEX* vertex){
	DFS_time++;
	vertex->data_for_other_algorithms->SCCA_finnishing_time = DFS_time;
}

void _DFS_set_up_depth_first_search_traversal_with_actions_in_graph_action(VERTEX* vertex){
	vertex->data_for_other_algorithms->SCCA_visited = 0;
	vertex->data_for_other_algorithms->SCCA_starting_time = 0;
	vertex->data_for_other_algorithms->SCCA_finnishing_time = 0;
}

void _DFS_set_up_depth_first_search_traversal_with_actions_in_graph(type_graph graph){
	DFS_time = 0;
	_DFS_traverse_graph_verticies_with_action(graph, (void*)_DFS_set_up_depth_first_search_traversal_with_actions_in_graph_action);
}

VERTEX* _DFS_find_unvisited_vertex_for_depth_first_search(GRAPH* graph, int order[], int next){//, int *new_i){
    int done;
	size_t n = graph->amount_of_vertices;
	if(next >= n) return NULL;

	set_current_to_first_item_in_list(graph->vertices);
	for(int j = 0; j < order[next]; j++){
		move_current_forward_in_list(graph->vertices);
	}

	VERTEX * current_vertex = get_current_item_in_list(graph->vertices);
	if(current_vertex->data_for_other_algorithms->SCCA_visited == 0) return current_vertex;
	return NULL;
}

void _DFS_(VERTEX* vertex, type_lptrf_oneitem vertex_action_one, type_lptrf_oneitem vertex_action_two){
	vertex_action_one(vertex);

	if(vertex->edges == NULL || empty_list(vertex->edges)){
		vertex_action_two(vertex);
		return; // stuck
	}
	
	set_current_to_first_item_in_list(vertex->edges);
	EDGE* edge;
	int done;
	do{
		done = is_current_last_item_in_list(vertex->edges);
		edge = get_current_item_in_list(vertex->edges);
		if((edge->to)->data_for_other_algorithms->SCCA_visited == 0){
			VERTEX* next_vertex = edge->to;
			_DFS_(next_vertex, vertex_action_one, vertex_action_two);
		}
		move_current_forward_in_list(vertex->edges);
	}while(!done);

	vertex_action_two(vertex);
	return;
}

void _DFS_depth_first_search_with_actions_in_graph(type_graph graph, int order[], type_lptrf_oneitem vertex_action_one, type_lptrf_oneitem vertex_action_two){
	GRAPH *graph_ = graph; 
	if(graph_ == NULL || empty_graph(graph_)) return;
	_DFS_set_up_depth_first_search_traversal_with_actions_in_graph(graph_);

    DFS_index_components = 0;

    for(int i=0; i < graph_->amount_of_vertices; i++){
	    VERTEX* vertex = _DFS_find_unvisited_vertex_for_depth_first_search(graph, order, i);//, &new_i);
        if(vertex == NULL) continue;//break;
        _DFS_(vertex, vertex_action_one, vertex_action_two);
        DFS_index_components++;
    }
    
}

long _SCCA_reverse_graph_vertex_condition(type_graphinfos vertex){
    return 1;
}

long _SCCA_reverse_graph_edge_condition(type_graphinfos from_vertex, type_graphinfos edge, type_graphinfos to_vertex){
    return 1;
}

void _set_up_vector_order(VERTEX* vertex){
	vertex->data_for_other_algorithms = malloc(sizeof(DFS_DATA));
	vertex->data_for_other_algorithms->SCCA_id = SCCA_index;
    SCCA_order[SCCA_index] = vertex->data_for_other_algorithms->SCCA_id;
    SCCA_index++;
}

void _set_up_reversed_graph(VERTEX* vertex){
	vertex->data_for_other_algorithms = malloc(sizeof(DFS_DATA));
	vertex->data_for_other_algorithms->SCCA_visited = 0;
}

void _saving_computed_finishing_time(VERTEX* vertex){
	_DFS_depth_first_search_visit_finnish(vertex);
    SCCA_finishing_time[SCCA_index] = vertex->data_for_other_algorithms->SCCA_finnishing_time;
    SCCA_backorder[SCCA_index] = vertex->data_for_other_algorithms->SCCA_id;
    SCCA_index++;
}

void _SCCA_compute_visit_start(VERTEX* vertex){
	_DFS_depth_first_search_visit_start(vertex);
    return;
}

void _SCCA_compute_visit(VERTEX* vertex){
	vertex->data_for_other_algorithms->SCCA_visited = 1;
    return;
}

void _SCCA_output_ending(VERTEX* vertex){
    vertex->data_for_other_algorithms->SCCA_component = DFS_index_components;
}

void _SCCA_create_backorder(int finishing_time[], int backorder[], int size){
    // selection sort
	int j, biggest, save_value_of_i, i, tmp;
	
    for(j = 0; j < size; j++){
		biggest = finishing_time[j];
		save_value_of_i = j;

		for(i = j; i < size; i++){
			if(finishing_time[i] > biggest){
				biggest = finishing_time[i];
				save_value_of_i = i;
			}
		}

		tmp = finishing_time[j];
		finishing_time[j] = finishing_time[save_value_of_i];
		finishing_time[save_value_of_i] = tmp;
        
		tmp = backorder[j];
		backorder[j] = backorder[save_value_of_i];
		backorder[save_value_of_i] = tmp;
	}
}

void _set_up_solution_vertex(VERTEX* vertex){
	SCCA_solution[SCCA_index] = vertex->data_for_other_algorithms->SCCA_component;
	SCCA_index++;
}

void _SCCA_clean_up_vertices(VERTEX* vertex){
    free(vertex->data_for_other_algorithms);
}

void _SCCA_vertex_nothing(type_graphinfos vertex){
    return;
}

void _SCCA_edge_nothing(type_graphinfos from_vertex, type_graphinfos edge, type_graphinfos to_vertex){
    return;
}

void strongly_connected_components_algorithm(type_graph graph, int *solution_vector){
    GRAPH* graph_ = graph;
    int order[graph_->amount_of_vertices];
    int backorder[graph_->amount_of_vertices];
    int finishing_time[graph_->amount_of_vertices];

    SCCA_order = order;
    SCCA_backorder = backorder;
    SCCA_finishing_time = finishing_time;
	SCCA_solution = solution_vector;

    SCCA_index = 0;
    _DFS_traverse_graph_verticies_with_action(graph_, (void*)_set_up_vector_order);
    SCCA_index = 0;
	// 1. Call DFS.G to compute finishing times u:f for each vertex u 
    _DFS_depth_first_search_with_actions_in_graph(graph_, order, (void*)_SCCA_compute_visit_start, (void*)_saving_computed_finishing_time);

	// 2. compute GT
    type_graph reversed_graph = create_reverse_graph_with_conditionals(graph, (void*)_SCCA_reverse_graph_vertex_condition, (void*)_SCCA_reverse_graph_edge_condition);

    _SCCA_create_backorder(finishing_time, backorder, graph_->amount_of_vertices);

	// 3. call DFS.GT, but in the main loop of DFS, consider the vertices in order of decreasing u:f (as computed in line 1)
    _DFS_traverse_graph_verticies_with_action(reversed_graph, (void*)_set_up_reversed_graph);
	_DFS_depth_first_search_with_actions_in_graph(reversed_graph, backorder, (void*)_SCCA_compute_visit, (void*)_SCCA_output_ending);


	// 4. output the vertices of each tree in the depth-first forest formed in line 3 as a separate strongly connected component
	SCCA_index = 0;
    // Putting in solution_vector the component that each vertex belongs to 
	// Note that this is in the same order as the vertex appear in the graph
	_DFS_traverse_graph_verticies_with_action(reversed_graph, (void*)_set_up_solution_vertex);

	//AQUIDE tem que fazer o cleanup
	_DFS_traverse_graph_verticies_with_action(graph, (void*)_SCCA_clean_up_vertices);
	_DFS_traverse_graph_verticies_with_action(reversed_graph, (void*)_SCCA_clean_up_vertices);
	destroi_graph(reversed_graph, (void*)_SCCA_vertex_nothing, (void*)_SCCA_edge_nothing);
	return;
}








