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
	type_list vertices; // VERTEX
	int current_size; // amount of vertices
	int amount_of_edges;
}GRAPH;

type_apqueue GA_PRIORITY_QUEUE;
long GA_PATHCOST;
VERTEX* GA_SOURCE;


// INT LONG OU FLOAT
// ACHO MELHOR FLOAT
// AI EU LIDO COM UM APONTADOR!!!!!!

void _traverse_graph_alg_verticies_with_action(type_graph graph, type_graphptrf_onetypeinfo action){
	GRAPH *graph_ = graph; 
	if(graph_ == NULL) return;
	
	if(empty_list(graph_->vertices)){
		printf("Graph is empty.\n"); 
        return;
	}

	set_current_to_first_item_in_list(graph_->vertices);
    int i = 0;
	int done;
	do{
		done = is_current_last_item_in_list(graph_->vertices);
		VERTEX *current_vertex = get_current_item_in_list(graph_->vertices);
		action(current_vertex);
		move_current_forward_in_list(graph_->vertices);
        i++;
	}while (!done);
    // printf("\n\n\nI=%d\n\n\n", i);
	return;	
}

VERTEX *_find_vertex_by_id_in_graph_alg(type_graph graph, char id[]){
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
    // FLOAT?
}


void _set_up_dijkstras_values_in_graph_aux(GRAPH * graph, VERTEX* source, type_apqueue priority_queue){
    GA_PRIORITY_QUEUE = priority_queue;
    GA_SOURCE = source;
    _traverse_graph_alg_verticies_with_action(graph, (void*)_set_up_dijkstras_values_in_graph_action_aux);
    source->data_for_other_algorithms = malloc(sizeof(DIJKSTRA_DATA));
    source->data_for_other_algorithms->dijkstra_definitive_value = 0;
    source->data_for_other_algorithms->dijkstra_from_vertex = NULL;
}


long _compare_two_vertex_for_galgorithms(VERTEX* vertex, VERTEX* vertex2){
    int size1 = strlen(vertex->id);
    int size2 = strlen(vertex2->id);
    int max = size1 > size2 ? size1 : size2;

    if(strncmp(vertex->id,vertex2->id, max) == 0){
        return 0;
    } 
    return -1;
}

long _condition_vertex_for_galgorithms(VERTEX* vertex){
    if(GA_PATHCOST < vertex->data_for_other_algorithms->dijkstra_tmp_value){
        return 1;
    }
    return 0;
}

void print_(VERTEX* vertex){
    printf("%ld ", vertex->data_for_other_algorithms->dijkstra_tmp_value);

}

long _print_condition_dijkstra(VERTEX* vertex){
    if(vertex->data_for_other_algorithms->dijkstra_tmp_value == __INT_MAX__) return 0;
    return 1;
}
// AQUIDE poderia só chamar a função que fiz no graph?
type_list _dijkstras_algorithm_with_destination_in_graph_aux(GRAPH *graph, VERTEX* vertex_source, VERTEX* vertex_destination, type_apqueue priority_queue, type_graphptrf_onetypeinfo get_edge_value, type_list solution_array){
    
    // base case:
    // visit os vizinhos e coloco valores temporarios do custo
    // tanto no grafo quanto na fila
 
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

                    // colocando valores temporários no gráfo
                    EDGE* edge = get_current_item_in_list(vertex->edges);
                    // valor da aresta + valor que está no nó anterior
                    long path_cost = (long)get_edge_value(edge->edge_info) + vertex->data_for_other_algorithms->dijkstra_definitive_value;
                    GA_PATHCOST = path_cost;
                    
                    int changed = conditionally_change_item_priority_in_ascending_priority_queue(priority_queue, path_cost, (edge->to), (void*)_compare_two_vertex_for_galgorithms, (void*)_condition_vertex_for_galgorithms);
                    // colocando valores temporários na fila                
                    if(changed == 1){
                        // printf("mudei alguem\n");
                        (edge->to)->data_for_other_algorithms->dijkstra_tmp_value = path_cost;
                        (edge->to)->data_for_other_algorithms->dijkstra_from_vertex = vertex;
                    }
                    move_current_forward_in_list(vertex->edges);
                }while(!done);

                // pego o de menor custo e seto para definitivo
            }
        }
        VERTEX* next_vertex = pull_item_in_ascending_priority_queue(priority_queue);
        // printf("next=[%ld]\n", next_vertex->dijkstra_tmp_value);
        // printf("NEXT ID:[%s]\n", next_vertex->id);
        // printf("dps do pull_item_in_ascending_priority_queue\n");
        next_vertex->data_for_other_algorithms->dijkstra_definitive_value = next_vertex->data_for_other_algorithms->dijkstra_tmp_value;
        vertex = next_vertex;
        printf("------------------------------------------------------------------------------------------------\n\n\n");
        print_ascending_priority_queue_with_condition(priority_queue, (void*)print_, (void*)_print_condition_dijkstra);
        printf("------------------------------------------------------------------------------------------------\n\n\n");

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


type_list dijkstras_algorithm_with_destination_in_graph(type_graph graph, char source_info_id[], char destination_info_id[], type_graphptrf_onetypeinfo get_edge_value){
	GRAPH *graph_ = graph; 
	VERTEX* source_node = _find_vertex_by_id_in_graph_alg(graph_, source_info_id);
    VERTEX* destination_node = _find_vertex_by_id_in_graph_alg(graph_, destination_info_id);

    set_ascending_priority_queue_max_size(graph_->current_size+1);
    type_apqueue priority_queue = create_ascending_priority_queue();
	_set_up_dijkstras_values_in_graph_aux(graph_, source_node, priority_queue);

    set_list_max_size(graph_->current_size+1);
    type_list solution_array = create_list();

	solution_array = _dijkstras_algorithm_with_destination_in_graph_aux(graph_, source_node, destination_node, priority_queue, (void*)get_edge_value, solution_array);
	//AQUIDE cleanup function desalocar memória do DIJKSTRA DATA
    return solution_array;
}






// ACHO QUE PODE APAGAR

// void _dijkstras_algorithm_with_destination_in_graph_aux_recursive(GRAPH *graph, VERTEX* vertex, VERTEX* vertex_destination, type_apqueue priority_queue, type_graphptrf_onetypeinfo get_edge_value){
    
//     // base case:
//     // visit os vizinhos e coloco valores temporarios do custo
//     // tanto no grafo quanto na fila
//     printf("------------------------------------------------------------------------------------------------\n\n\n");
//     print_ascending_priority_queue_with_condition(priority_queue, (void*)print_, (void*)_print_condition_dijkstra);
//     printf("------------------------------------------------------------------------------------------------\n\n\n");

//     // setando os valores temp! -------------------
//     if(vertex->edges != NULL){
//         if(!empty_list(vertex->edges)){
//             set_current_to_first_item_in_list(vertex->edges);
//             int done;
//             do{
//                 done = is_current_last_item_in_list(vertex->edges);

//                 // colocando valores temporários no gráfo
//                 EDGE* edge = get_current_item_in_list(vertex->edges);
//                 // valor da aresta + valor que está no nó anterior
//                 long path_cost = (long)get_edge_value(edge->edge_info) + vertex->dijkstra_definitive_value;
//                 GA_PATHCOST = path_cost;
                
//                 int changed = conditionally_change_item_priority_in_ascending_priority_queue(priority_queue, path_cost, (edge->to), (void*)_compare_two_vertex_for_galgorithms, (void*)_condition_vertex_for_galgorithms);
                
//                 // colocando valores temporários na fila                
//                 if(changed == 1){
//                     printf("mudei alguem\n");
//                     (edge->to)->dijkstra_tmp_value = path_cost;
//                     (edge->to)->dijkstra_from_vertex = vertex;
//                 }
//                 move_current_forward_in_list(vertex->edges);
//             }while(!done);

//             // pego o de menor custo e seto para definitivo
//         }
//     }
//     printf("fora do while\n");

//     // condicao de parada ====== fim
//     if(strcmp(vertex->id, vertex_destination->id) == 0){
//         printf("CURRENT ID: [%s]\n", vertex->id);
//         printf("LAST ID: [%s]\n", vertex_destination->id);
//         return;
//     }
//     if(empty_ascending_priority_queue(priority_queue)) return;

//     // para onde vou?
//     // PEGANDO DO PRIORITY QUEUE O MENOR 
//     VERTEX* next_vertex = pull_item_in_ascending_priority_queue(priority_queue);
//     printf("next=[%ld]\n", next_vertex->dijkstra_tmp_value);
//     printf("NEXT ID:[%s]\n", next_vertex->id);
//     printf("dps do pull_item_in_ascending_priority_queue\n");
//     next_vertex->dijkstra_definitive_value = next_vertex->dijkstra_tmp_value;

//     //return _dijkstras_algorithm_in_graph_aux(graph, next_vertex, priority_queue, get_edge_value);
//     _dijkstras_algorithm_with_destination_in_graph_aux_recursive(graph, next_vertex, vertex_destination, priority_queue, get_edge_value);
// }


