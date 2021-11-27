//
//  graph.c
//   
//
//  Created by Denise F. de Rezende on 03/03/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "graph.h"

// two lists:
// vertical que armazena os vertic
// list of VERTEX
// |
// |
// |
// list of EDGE | | | | | | 

// typedef struct neighbors_node{
// 	type_graphitems* vertex_info;
// 	type_graphitems* edge_info;
// }NEIGHBORS;

typedef struct vertex{
	type_graphitems *vertex_info;
	type_list edges;
	long temp_dijkstra_value;
	//type_list edges_infos_only;
}VERTEX;

typedef struct edge{
	VERTEX *to;
	type_graphitems* edge_info;
}EDGE;

typedef struct graph{
	type_list vertices; // VERTEX
	int declared_size; // amount of declared vertices
	int current_size; // amount of vertices
}GRAPH;

VERTEX * _find_vertex_in_list_aux_graph(type_list vertices, type_graphitems vertex_info, type_graphptrf_twoitems compare){
	if(vertices == NULL) return NULL;
	if(empty_list(vertices)) return NULL;
	
	set_current_to_first_item_in_list(vertices);
	int done;
	do{
		done = is_current_last_item_in_list(vertices);
		VERTEX *current_vertex = get_current_item_in_list(vertices);
		if(compare(current_vertex->vertex_info, vertex_info) == 0){
			return current_vertex;
		}
		move_current_forward_in_list(vertices);
	}while (!done);
	return NULL;
}
EDGE * _find_edge_in_list_aux_graph(type_list edges, type_graphitems edge_info, type_graphptrf_twoitems compare){
	if(edges == NULL) return NULL;
	if(empty_list(edges)) return NULL;
	
	set_current_to_first_item_in_list(edges);
	int done;
	do{
		done = is_current_last_item_in_list(edges);
		EDGE *current_edge = get_current_item_in_list(edges);
		if(compare(current_edge->edge_info, edge_info) == 0){
			return current_edge;
		}
		move_current_forward_in_list(edges);
	}while (!done);
	return NULL;
}
EDGE * _find_edge_by_to_vertex_in_list_aux_graph(type_list edges, type_graphitems vertex_info, type_graphptrf_twoitems compare){
	if(edges == NULL) return NULL;
	if(empty_list(edges)) return NULL;
	

	set_current_to_first_item_in_list(edges);
	int done;
	do{
		done = is_current_last_item_in_list(edges);
		EDGE *current_edge = get_current_item_in_list(edges);
		if(compare((current_edge->to)->vertex_info, vertex_info) == 0){
			return current_edge;
		}
		move_current_forward_in_list(edges);
	}while (!done);
	return NULL;
}

void _deallocate_edges_aux_graph(type_list edges, type_graphptrf_oneitem deallocate){
	int done;
	if(edges == NULL || empty_list(edges)){
		return;
	}

	set_current_to_last_item_in_list(edges);
	do{
		done = is_current_first_item_in_list(edges);
		EDGE *del_edge = delete_allocated_current_item_in_list(edges);
		deallocate(del_edge->edge_info);
		free(del_edge);
	}while(!done);
	destroi_list(edges);
}


void _deallocate_edges_that_point_to_vertex(GRAPH *graph, type_graphitems vertex_info, type_graphptrf_twoitems compare_vertices, type_graphptrf_oneitem deallocate_edge){
	
	int done;
	set_current_to_first_item_in_list(graph->vertices);
	do{
		done = is_current_last_item_in_list(graph->vertices);
		
		VERTEX *vertex = get_current_item_in_list(graph->vertices);

		if(vertex->edges == NULL || empty_list(vertex->edges) || (compare_vertices(vertex->vertex_info, vertex_info) == 0)){
			move_current_forward_in_list(graph->vertices);
			continue;
		}
		int done_;
		set_current_to_first_item_in_list(vertex->edges);
		do{
			done_ = is_current_last_item_in_list(vertex->edges);
			EDGE *edge = get_current_item_in_list(vertex->edges);

			if(compare_vertices((edge->to)->vertex_info, vertex_info) == 0){
				// deletar o edge
				EDGE *del_edge = delete_allocated_current_item_in_list(vertex->edges);
				deallocate_edge(del_edge->edge_info);
				free(del_edge);
			}

			move_current_forward_in_list(vertex->edges);

		}while(!done_);
		move_current_forward_in_list(graph->vertices);

	}while(!done);
}

type_graph create_graph(int amount_of_vertices){
	GRAPH *graph = malloc(sizeof(GRAPH)); 
	graph->vertices = create_list();
	graph->declared_size = amount_of_vertices;
	graph->current_size = 0;
	return graph;
}

int insert_vertex_in_graph(type_graph graph, type_graphitems vertex_info, type_graphptrf_twoitems compare_vertices){
	GRAPH *graph_ = graph;
	VERTEX *vertex_node = malloc(sizeof(VERTEX));
	vertex_node->vertex_info = vertex_info;
	vertex_node->edges = NULL;

	VERTEX *vertex_found = _find_vertex_in_list_aux_graph(graph_->vertices, vertex_info, compare_vertices);
	if(vertex_found == NULL){
		insert_item_at_the_end_of_list(graph_->vertices, vertex_node);
		graph_->current_size++;
		return 1;
	}
	free(vertex_node);
	return 0;
}

// já insere a aresta junto com a info dela
// tenho que verificar se já tá la? o edge?????????????/
void insert_edge_in_graph(type_graph graph, type_graphitems from_vertex_info, type_graphitems to_vertex_info, type_graphptrf_twoitems compare_vertices,  type_graphitems edge_info){
	GRAPH *graph_ = graph;
	VERTEX *from_vertex_node = _find_vertex_in_list_aux_graph(graph_->vertices, from_vertex_info, compare_vertices);
	
	if(from_vertex_node != NULL){
		VERTEX *to_vertex_node = _find_vertex_in_list_aux_graph(graph_->vertices, to_vertex_info, compare_vertices);
		if(to_vertex_node != NULL){
			EDGE *edge_info_node = malloc(sizeof(EDGE));
			
			edge_info_node->edge_info = edge_info;
			edge_info_node->to = to_vertex_node;
			if(from_vertex_node->edges == NULL){
				from_vertex_node->edges = create_list();
				insert_item_at_the_end_of_list(from_vertex_node->edges, edge_info_node);
			}
			else{
				insert_item_at_the_end_of_list(from_vertex_node->edges, edge_info_node);
			}
		}
	}
}

type_graphitems get_edge_info_in_graph(type_graph graph, type_graphitems from_vertex_info, type_graphitems to_vertex_info, type_graphptrf_twoitems compare_vertices){
	GRAPH *graph_ = graph;
	VERTEX *from_vertex_node = _find_vertex_in_list_aux_graph(graph_->vertices, from_vertex_info, compare_vertices);
	if(from_vertex_node != NULL){
		if(from_vertex_node->edges == NULL) return NULL;
		if(empty_list(from_vertex_node->edges)) return NULL;

		EDGE *edge = _find_edge_by_to_vertex_in_list_aux_graph(from_vertex_node->edges, to_vertex_info, compare_vertices);

		if(edge != NULL) return edge->edge_info;
	}
	return NULL;
}

// return -1 => valor foi sobrescrito
// return 1 => valor foi apenas inserido, não tinha valor prévio
// return 0 => operaçao falhou (motivos:)
int change_edge_info_value_in_graph(type_graph graph, type_graphitems from_vertex_info, type_graphitems to_vertex_info, type_graphptrf_twoitems compare_vertices, type_graphitems new_edge_info){
	GRAPH *graph_ = graph;
	VERTEX *from_vertex_node = _find_vertex_in_list_aux_graph(graph_->vertices, from_vertex_info, compare_vertices);
	if(from_vertex_node != NULL){
		if(from_vertex_node->edges == NULL) return 0;
		if(empty_list(from_vertex_node->edges)) return 0;

		EDGE *edge = _find_edge_by_to_vertex_in_list_aux_graph(from_vertex_node->edges, to_vertex_info, compare_vertices);

		if(edge != NULL){
			edge->edge_info = new_edge_info;
			return 1;
		}
		else{
			edge->edge_info = new_edge_info;
			return -1;
		}
	}
	return 0;
}

// return -1 => valor foi sobrescrito
// return 1 => valor foi apenas inserido, não tinha valor prévio mas vertice existia
// return 0 => operaçao falhou (motivos:)
int change_vertex_info_value_in_graph(type_graph graph, type_graphitems vertex_info, type_graphptrf_twoitems compare_vertices, type_graphitems new_vertex_info){
	GRAPH *graph_ = graph;
	VERTEX *vertex_node = _find_vertex_in_list_aux_graph(graph_->vertices, vertex_info, compare_vertices);
	if(vertex_node != NULL){
		if(vertex_node->vertex_info != NULL){
			vertex_node->vertex_info = new_vertex_info;
			return -1;
		}
		else{
			vertex_node->vertex_info = new_vertex_info;
			return 1;
		}		
	}

	return 0;
}

// doesn't make sense
// type_graphitems get_vertex_info_in_graph(type_graph graph, type_graphitems vertex, type_graphptrf_twoitems compare_vertices){
// 	GRAPH *graph_ = graph;
// 	VERTEX *vertex_node = _find_vertex_in_list_aux_graph(graph_->vertices, vertex, compare_vertices);
// 	if(vertex_node != NULL){
// 		return vertex_node->vertex_info;
// 	}
// 	return NULL;
// }

int remove_edge_from_graph(type_graph graph, type_graphitems from_vertex_info, type_graphitems to_vertex_info, type_graphptrf_twoitems compare_vertices, type_graphptrf_oneitem deallocate_edge){
	GRAPH *graph_ = graph;
	VERTEX *from_vertex_node = _find_vertex_in_list_aux_graph(graph_->vertices, from_vertex_info, compare_vertices);
	if(from_vertex_node != NULL){
		if(from_vertex_node->edges == NULL) return 0;
		if(empty_list(from_vertex_node->edges)) return 0;

		EDGE *edge = _find_edge_by_to_vertex_in_list_aux_graph(from_vertex_node->edges, to_vertex_info, compare_vertices);
		if(edge != NULL){
			EDGE *edge = delete_allocated_current_item_in_list(from_vertex_node->edges);
			deallocate_edge(edge->edge_info);
			free(edge);
			return 1;
		}
	}
	return 0;
}

int remove_vertex_from_graph(type_graph graph, type_graphitems vertex_info, type_graphptrf_twoitems compare_vertices, type_graphptrf_oneitem deallocate_vertex, type_graphptrf_oneitem deallocate_edge){
	GRAPH *graph_ = graph;
	VERTEX *vertex_node = _find_vertex_in_list_aux_graph(graph_->vertices, vertex_info, compare_vertices);
	if(vertex_node != NULL){
		// Deallocating the vertex edges
		_deallocate_edges_aux_graph(vertex_node->edges, deallocate_edge);
		vertex_node->edges = NULL;

		// Deallocating other vertex edges that pointed to that vertex
		_deallocate_edges_that_point_to_vertex(graph, vertex_node->vertex_info, compare_vertices, deallocate_edge);

		delete_item_in_list(graph_->vertices, vertex_node, (void*)compare_vertices);
		deallocate_vertex(vertex_node->vertex_info);
		free(vertex_node);
		
		graph_->current_size--;
		return 1;
	}
	return 0;
}


void print_graph(type_graph graph, type_graphptrf_oneitem print_vertex, type_graphptrf_oneitem print_edge){
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
		print_vertex(current_vertex->vertex_info);
		
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
			print_vertex((current_edge->to)->vertex_info);
			
			printf("[");
			print_edge(current_edge->edge_info);
			printf("] ");
			if(!done_) printf("-\t");
			move_current_forward_in_list(current_vertex->edges);
		}while(!done_);

		move_current_forward_in_list(graph_->vertices);
	}while (!done);

	printf("\n");
	printf("----------------------\n");
	return;	
}

void destroi_graph(type_graph graph, type_graphptrf_oneitem deallocate_vertex, type_graphptrf_oneitem deallocate_edge){
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
		//delete_item_in_list(graph_->vertices, current_vertex, (void*)compare_vertices);
		deallocate_vertex(current_vertex->vertex_info);
		free(current_vertex);

		// if(current_vertex->edges == NULL || empty_list(current_vertex->edges)){
		// 	// remove vertex and move on

		// 	move_current_forward_in_list(graph_->vertices);
		// 	continue;
		// } 
		
		// set_current_to_first_item_in_list(current_vertex->edges);
		// do {
		// 	done_ = is_current_last_item_in_list(current_vertex->edges);
		// 	EDGE *current_edge = get_current_item_in_list(current_vertex->edges);
		// 	// remove edge and move on to the next

		// 	move_current_forward_in_list(current_vertex->edges);
		// }while(!done_);


		// remove vertex and move on

		move_current_forward_in_list(graph_->vertices);
	}while (!done);


	return;	
}

int are_vertex_adjacent_in_graph(type_graph graph, type_graphitems from_vertex_info, type_graphitems to_vertex_info, type_graphptrf_twoitems compare_vertices){
	GRAPH *graph_ = graph; 
	// achar o vertex do from, 
	VERTEX* from_vertex = _find_vertex_in_list_aux_graph(graph_->vertices, from_vertex_info, compare_vertices);
	if(from_vertex == NULL) return 0;

	//caminhar na sua lista de edges e ver se alguem aponta para vertex_info_to
	EDGE *edge = _find_edge_by_to_vertex_in_list_aux_graph(from_vertex->edges, to_vertex_info, compare_vertices);
	if(edge == NULL) return 0;

	return 1;
}

type_list vertex_neighbors_in_graph(type_graph graph, type_graphitems vertex_info, type_graphptrf_twoitems compare_vertices){
	GRAPH *graph_ = graph; 

	VERTEX* vertex = _find_vertex_in_list_aux_graph(graph_->vertices, vertex_info, compare_vertices);
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

// void dijkstras_algorithm_in_graph(type_graph graph, type_graphitems source_info, type_graphptrf_twoitems compare_vertices, type_graphptrf_oneitem get_edge_value){
// 	GRAPH *graph_ = graph; 
// 	VERTEX* source_node = _find_vertex_in_list_aux_graph(graph_->vertices, source_info, compare_vertices);
// 	_set_up_dijkstras_values_in_graph_aux();
// 	_dijkstras_algorithm_in_graph_aux(graph, source_node, NULL, get_edge_value);
// }


// long _dijkstras_algorithm_in_graph_aux(GRAPH * graph, VERTEX* source, EDGE* edge, type_graphptrf_oneitem get_edge_value){
// 	// base case:

	
	
	
// 	// other:
// 	return _dijkstras_algorithm_in_graph_aux(graph, )
	
	
// 	// quero fazer quando chego em um nó
// 	long edge_value;
// 	if(edge != NULL){
// 		edge_value = get_edge_value(edge->edge_info);
// 	}
// 	else edge_value = 0;

// 	source->temp_dijkstra_value = edge_value;
// 	// ver para quantos ele aponta
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

