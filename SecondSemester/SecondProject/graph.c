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

// two lists:
// vertical que armazena os vertic
// list of VERTEX
// |
// |
// |
// list of EDGE | | | | | | 

// typedef struct neighbors_node{
// 	type_graphinfos* vertex_info;
// 	type_graphinfos* edge_info;
// }NEIGHBORS;

typedef struct vertex{
	char id[41];
	type_graphinfos *vertex_info;
	type_list edges;

	// dijkstra
	long dijkstra_tmp_value;
	long dijkstra_definitive_value;
	struct vertex *dijkstra_from_vertex;
	
	// kruskals
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

// AQUIDE remover esse amount_of_vertices nao uso para nada
type_graph create_graph(){
	GRAPH *graph = malloc(sizeof(GRAPH)); 
	graph->vertices = create_list();
	graph->current_size = 0;
	graph->amount_of_edges = 0;
	return graph;
}

int empty_graph(type_graph graph){
	GRAPH *graph_ = graph;
	if(empty_list(graph_->vertices)) return 1;
	return 0;
}



// returns the id of the inserted info
int add_vertex_to_graph(type_graph graph, char id[]){
	GRAPH *graph_ = graph;
	VERTEX *vertex = _find_vertex_by_id_in_graph(graph_, id);
	if(vertex == NULL){
		VERTEX *vertex_node = _new_vertex_for_graph_aux(graph_, id);
		insert_item_at_the_end_of_list(graph_->vertices, vertex_node);
		graph_->current_size++;
		return 1;
	}
	return 0;
}

void set_vertex_info_in_graph(type_graph graph, char vertex_id[], type_graphinfos vertex_info){
	GRAPH *graph_ = graph;
	VERTEX *vertex = _find_vertex_by_id_in_graph(graph_, vertex_id);
	vertex->vertex_info = vertex_info;
}

type_graphinfos get_vertex_info_in_graph(type_graph graph, char id[]){
	GRAPH *graph_ = graph;
	VERTEX *vertex = _find_vertex_by_id_in_graph(graph_, id);
	if(vertex != NULL) return vertex->vertex_info;
	return NULL;
}


// já insere a aresta junto com a info dela
// tenho que verificar se já tá la? o edge?????????????/
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
		_find_edge_by_id_in_edges_list_in_graph(from_vertex_node->edges, to_vertex_id);
		EDGE *edge_node = _find_edge_by_id_in_edges_list_in_graph(from_vertex_node->edges, to_vertex_id);

		//EDGE *edge_node = _find_vertex_by_id_in_graph(graph_->vertices, to_vertex_id);
		edge_node->edge_info = edge_info;
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


//type_graphinfos vertex_info, type_graphptrf_twoitems compare_vertices, type_graphptrf_onetypeinfo deallocate_vertex,
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
		free(vertex_node);
		
		graph_->current_size--;
		return vertex_info;
	}
	return NULL;
}


void print_graph(type_graph graph, type_graphptrf_onetypeinfo print_vertex, type_graphptrf_onetypeinfo print_edge){
	GRAPH *graph_ = graph; 
	if(graph_ == NULL) return;

	set_current_to_first_item_in_list(graph_->vertices);
	if(empty_list(graph_->vertices)){
		printf("Graph is empty.\n"); return;
	}

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
		free(current_vertex);

		move_current_forward_in_list(graph_->vertices);
	}while (!done);


	return;	
}

type_graphinfos are_vertex_adjacent_in_graph_return_edge(type_graph graph, char from_vertex_id[], char to_vertex_id[]){
	GRAPH *graph_ = graph; 
	// achar o vertex do from, 
	VERTEX *from_vertex_node = _find_vertex_by_id_in_graph(graph_, from_vertex_id);
	if(from_vertex_node == NULL) return NULL;

	//caminhar na sua lista de edges e ver se alguem aponta para vertex_info_to
	EDGE *edge = _find_edge_by_id_in_edges_list_in_graph(from_vertex_node->edges, to_vertex_id);
	if(edge != NULL) return edge->edge_info;
	return NULL;
}


int are_vertex_adjacent_in_graph(type_graph graph, char from_vertex_id[], char to_vertex_id[]){
	GRAPH *graph_ = graph; 
	// achar o vertex do from, 
	VERTEX *from_vertex_node = _find_vertex_by_id_in_graph(graph_, from_vertex_id);
	if(from_vertex_node == NULL) return 0;

	//caminhar na sua lista de edges e ver se alguem aponta para vertex_info_to
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

	// não posso fazer isso se nao devolve umas coisas nada a ver
	// return vertex->edges;

	// formar uma lista para retornar
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

void _traverse_graph_verticies_with_action(type_graph graph, type_lptrf_oneitem action){
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
		action(current_vertex);
		move_current_forward_in_list(graph_->vertices);
	}while (!done);

	return;	
}

void traverse_graph_conditional_actions(type_graph graph, type_lptrf_oneitem vertex_action, type_lptrf_oneitem vertex_condition, type_lptrf_threeitems edge_action, type_lptrf_threeitems edge_condition){
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


void traverse_graph_conditional_actions_plus_vertex_condition_is_no_edges(type_graph graph, type_lptrf_oneitem vertex_action, type_lptrf_threeitems edge_action, type_lptrf_oneitem edge_condition){
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

		if(current_vertex->edges == NULL || empty_list(current_vertex->edges)){
			vertex_action(current_vertex->vertex_info);
			move_current_forward_in_list(graph_->vertices);
			continue;
		} 

		int done_;
		set_current_to_first_item_in_list(current_vertex->edges);
		do {
			done_ = is_current_last_item_in_list(current_vertex->edges);
			EDGE *current_edge = get_current_item_in_list(current_vertex->edges);
			
			if(edge_condition(current_edge->edge_info)){
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


// void traverse_verticies_with_conditional_deletion_graph(type_graph graph, type_lptrf_oneitem vertex_action, type_lptrf_oneitem vertex_condition, type_lptrf_oneitem deallocate_vertex, type_lptrf_oneitem deallocate_edge){
// 	GRAPH *graph_ = graph; 
// 	if(graph_ == NULL) return;
	
// 	if(empty_list(graph_->vertices)){
// 		printf("Graph is empty.\n"); 
// 		return;
// 	}

// 	set_current_to_first_item_in_list(graph_->vertices);

// 	int done;
// 	do{
// 		done = is_current_last_item_in_list(graph_->vertices);
// 		VERTEX *current_vertex = get_current_item_in_list(graph_->vertices);
		
// 		if(vertex_condition(current_vertex->vertex_info)){
// 			vertex_action(current_vertex->vertex_info);
// 			if(current_vertex != NULL){
// 				// Deallocating the vertex edges
// 				_deallocate_edges_aux_graph(current_vertex->edges, deallocate_edge);
// 				current_vertex->edges = NULL;

// 				// Deallocating other vertex edges that pointed to that vertex
// 				_deallocate_edges_that_point_to_vertex(graph, current_vertex->id, deallocate_edge);

// 				delete_item_in_list(graph_->vertices, current_vertex, (void*)_compare_verticies_graph);

// 				type_graphinfos vertex_info = current_vertex->vertex_info;
// 				free(current_vertex);
				
// 				graph_->current_size--;
// 			}
// 		}

// 		move_current_forward_in_list(graph_->vertices);
// 	}while (!done);

// 	return;	
// }



// void traverse_verticies_until_conditional_action_graph(type_graph graph, type_lptrf_oneitem vertex_action, type_lptrf_oneitem vertex_condition){
// 	GRAPH *graph_ = graph; 
// 	if(graph_ == NULL) return;
	
// 	if(empty_list(graph_->vertices)){
// 		printf("Graph is empty.\n"); return;
// 	}

// 	set_current_to_first_item_in_list(graph_->vertices);

// 	int done;
// 	do{
// 		done = is_current_last_item_in_list(graph_->vertices);
// 		VERTEX *current_vertex = get_current_item_in_list(graph_->vertices);
		
// 		if(vertex_condition(current_vertex)){
// 			vertex_action(current_vertex->vertex_info);
// 		}
// 		int done_;

// 		move_current_forward_in_list(graph_->vertices);
// 	}while (!done);

// 	return;	
// }

// nao implementado pq nao fazia sentido nesse tipo de implementacao
// get_vertex_value(G, x): returns the value associated with the vertex x;



// não sei se foi feito da melhor forma....
// set_vertex_value(G, x, v): sets the value associated with the vertex x to v. => change
// set_edge_value(G, x, y, v): sets the value associated with the edge (x, y) to v. => change
// neighbors(G, x): lists all vertices y such that there is an edge from the vertex x to the vertex y; => lista nova com possibilidade de desaloca-la sem mudar o grafo
// => essa lista nao pode ser alterada!!!!! 



// adjacent(G, x, y): tests whether there is an edge from the vertex x to the vertex y;
// add_vertex(G, x): adds the vertex x, if it is not there;
// remove_vertex(G, x): removes the vertex x, if it is there;
// add_edge(G, x, y): adds the edge from the vertex x to the vertex y, if it is not there;
// remove_edge(G, x, y): removes the edge from the vertex x to the vertex y, if it is there;
// Structures that associate values to the edges usually also provide:[1]
// get_edge_value(G, x, y): returns the value associated with the edge (x, y);

// /* -------------------------------------- dijkstras -------------------------------------- */

// #include "ascending_priority_queue.h"
// int GA_PATHCOST;


// void _set_up_dijkstras_values_in_graph_action_aux(VERTEX* vertex){
//     vertex->dijkstra_tmp_value = __INT_MAX__; // INT64_MAX
//     // FLOAT?
// }

// void _set_up_dijkstras_values_in_graph_aux(GRAPH * graph, VERTEX* source){
//     _traverse_graph_verticies_with_action(graph, (void*)_set_up_dijkstras_values_in_graph_action_aux);
//     source->dijkstra_definitive_value = 0;
// }




// long _compare_two_vertex_for_galgorithms(VERTEX* vertex, VERTEX* vertex2){
//     return(strcmp(vertex->id,vertex2->id));
// }

// long _condition_vertex_for_galgorithms(VERTEX* vertex){
//     if(GA_PATHCOST < vertex->dijkstra_tmp_value){
//         return 1;
//     }
//     return 0;
// }


// void _dijkstras_algorithm_in_graph_aux(GRAPH *graph, VERTEX* vertex, type_list priority_queue, type_graphptrf_onetypeinfo get_edge_value){
// 	// base case:
//     // visit os vizinhos e coloco valores temporarios do custo
//     // tanto no grafo quanto na fila

//     // setando os valores temp! -------------------
//     if(vertex->edges != NULL){
//         if(!empty_list(vertex->edges)){
            
//             set_current_to_first_item_in_list(vertex->edges);

//             int done;
//             do{
//                 done = is_current_last_item_in_list(vertex->edges);

//                 // FALTA ALGUM TIPO DE VERIFICACAO SE O ELEMENTO JA TA LA 
//                 // SE SIM COMPARAR VALORES E MUDAR A PRIORIDADE
//                 //int change_item_priority_in_ascending_priority_queue(type_apqueue queue, int new_priority, type_apqitems item, type_apqptrf_twoitems check_if_equal);
    
//                 // colocando valores temporários no gráfo
//                 EDGE* edge = get_current_item_in_list(vertex->edges);
//                 // valor da aresta + valor que está no nó anterior
//                 long path_cost = (long)get_edge_value(edge->edge_info) + vertex->dijkstra_definitive_value;
//                 GA_PATHCOST = path_cost;
                
//                 int changed = conditionally_change_item_priority_in_ascending_priority_queue(priority_queue, path_cost, edge->to, (void*)_compare_two_vertex_for_galgorithms, (void*)_condition_vertex_for_galgorithms);
//                 if(changed){
//                     (edge->to)->dijkstra_tmp_value = path_cost;
//                 }
//                 // colocando valores temporários na fila
//                 else if(changed == -1) {
//                         insert_item_in_ascending_priority_queue(priority_queue, path_cost, edge->to);
//                         (edge->to)->dijkstra_tmp_value = path_cost;
//                     }

//                 move_current_forward_in_list(vertex->edges);
//             }while(!done);

//             // pego o de menor custo e seto para definitivo
//         }
//     }

//     // condicao de parada ====== fim
//     if(empty_ascending_priority_queue(priority_queue)) return;

//     // para onde vou?
//     // PEGANDO DO PRIORITY QUEUE O MENOR 
//     VERTEX* next_vertex =  pull_item_in_ascending_priority_queue(priority_queue);
//     next_vertex->dijkstra_definitive_value = next_vertex->dijkstra_tmp_value;

//     //_dijkstras_algorithm_in_graph_aux(graph, next_vertex, priority_queue, get_edge_value);
//     return _dijkstras_algorithm_in_graph_aux(graph, next_vertex, priority_queue, get_edge_value);
// }

// // SOS AQUIDE ver que tipo colocar a variavel do edge!!!!!!



// void dijkstras_algorithm_in_graph(type_graph graph, char source_info_id[], type_graphptrf_onetypeinfo get_edge_value){
// 	GRAPH *graph_ = graph; 
//     printf("antes do _find_vertex_by_id_in_graph_alg\n");
// 	VERTEX* source_node = _find_vertex_by_id_in_graph(graph, source_info_id);
//     printf("antes do _set_up_dijkstras_values_in_graph_aux\n");
// 	_set_up_dijkstras_values_in_graph_aux(graph_, source_node);
//     set_list_max_size(graph_->current_size+1);
//     type_apqueue priority_queue = create_ascending_priority_queue();
// 	_dijkstras_algorithm_in_graph_aux(graph, source_node, priority_queue, get_edge_value);
// }

