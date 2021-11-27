//
//  graph.h
//   
//
//  Created by Denise F. de Rezende on 17/03/21.
//

#ifndef graph_h
#define graph_h
#include "list.h"

typedef void* type_graph; 
typedef void* type_graphitems;
typedef void* type_graphptrf_twoitems(type_graphitems, type_graphitems);
typedef void* type_graphptrf_oneitem(type_graphitems);



type_graph create_graph(int amount_of_vertices);

int insert_vertex_in_graph(type_graph graph, type_graphitems vertex_info, type_graphptrf_twoitems compare_vertices);

// já insere a aresta junto com a info dela
void insert_edge_in_graph(type_graph graph, type_graphitems from_vertex_info, type_graphitems to_vertex_info, type_graphptrf_twoitems compare_vertices,  type_graphitems edge_info);

type_graphitems get_edge_info_in_graph(type_graph graph, type_graphitems from_vertex_info, type_graphitems to_vertex_info, type_graphptrf_twoitems compare_vertices);

int change_edge_info_value_in_graph(type_graph graph, type_graphitems from_vertex_info, type_graphitems to_vertex_info, type_graphptrf_twoitems compare_vertices, type_graphitems new_edge_info);

int change_vertex_info_value_in_graph(type_graph graph, type_graphitems vertex_info, type_graphptrf_twoitems compare_vertices, type_graphitems new_vertex_info);

int remove_edge_from_graph(type_graph graph, type_graphitems from_vertex_info, type_graphitems to_vertex_info, type_graphptrf_twoitems compare_vertices, type_graphptrf_oneitem deallocate_edge);

int remove_vertex_from_graph(type_graph graph, type_graphitems vertex_info, type_graphptrf_twoitems compare_vertices, type_graphptrf_oneitem deallocate_vertex, type_graphptrf_oneitem deallocate_edge);

void print_graph(type_graph graph, type_graphptrf_oneitem print_vertex, type_graphptrf_oneitem print_edge);

void destroi_graph(type_graph graph, type_graphptrf_oneitem deallocate_vertex, type_graphptrf_oneitem deallocate_edge);


int are_vertex_adjacent_in_graph(type_graph graph, type_graphitems from_vertex_info, type_graphitems to_vertex_info, type_graphptrf_twoitems compare_vertices);

type_list vertex_neighbors_in_graph(type_graph graph, type_graphitems vertex_info, type_graphptrf_twoitems compare_vertices);

type_list destroi_list_created_with_vertex_neighbors_in_graph(type_list list);

#endif 
