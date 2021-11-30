//
//  graph.h
//   
//
//  Created by Denise F. de Rezende on 17/03/21.
//

#ifndef graph_h
#define graph_h
#include "list.h"
#include "ascending_priority_queue.h"

typedef void* type_graph; 
typedef void* type_graphinfos;
typedef void* type_graphptrf_onetypeinfo(type_graphinfos);
typedef void* type_lptrf_threeitems(type_graphinfos, type_graphinfos, type_graphinfos);


type_graph create_graph();

int empty_graph();

// returns the id of the inserted info
int add_vertex_to_graph(type_graph graph, char id[]);

void set_vertex_info_in_graph(type_graph graph, char vertex_id[], type_graphinfos vertex_info);

type_graphinfos get_vertex_info_in_graph(type_graph graph, char id[]);

int add_edge_to_graph(type_graph graph, char from_vertex_id[], char to_vertex_id[]);

int set_edge_info_in_graph(type_graph graph, char from_vertex_id[], char to_vertex_id[], type_graphinfos edge_info);

type_graphinfos get_edge_info_in_graph(type_graph graph, char from_vertex_id[], char to_vertex_id[]);

type_graphinfos remove_edge_from_graph(type_graph graph, char from_vertex_id[], char to_vertex_id[]);

type_graphinfos remove_vertex_from_graph(type_graph graph, char id[], type_graphptrf_onetypeinfo deallocate_edge);

void print_graph(type_graph graph, type_graphptrf_onetypeinfo print_vertex, type_graphptrf_onetypeinfo print_edge);

void destroi_graph(type_graph graph, type_graphptrf_onetypeinfo deallocate_vertex, type_graphptrf_onetypeinfo deallocate_edge);

type_graphinfos are_vertex_adjacent_in_graph_return_edge(type_graph graph, char from_vertex_id[], char to_vertex_id[]);

int are_vertex_adjacent_in_graph(type_graph graph, char from_vertex_id[], char to_vertex_id[]);

type_list vertex_neighbors_in_graph(type_graph graph, char id[]);

type_list destroi_list_created_with_vertex_neighbors_in_graph(type_list list);

void traverse_graph_conditional_actions(type_graph graph, type_lptrf_oneitem vertex_action, type_lptrf_oneitem vertex_condition, type_lptrf_threeitems edge_action, type_lptrf_threeitems edge_condition);

int traverse_verticies_until_conditional_action_graph(type_graph graph, type_lptrf_oneitem vertex_action, type_lptrf_oneitem vertex_condition);

void traverse_verticies_with_conditional_action_graph(type_graph graph, type_lptrf_oneitem vertex_action, type_lptrf_oneitem vertex_condition);

void traverse_graph_conditional_actions_plus_vertex_condition_is_no_edges(type_graph graph, type_lptrf_oneitem vertex_action, type_lptrf_threeitems edge_action, type_lptrf_oneitem edge_condition);

type_graph duplicate_graph_with_conditionals(type_graph graph, type_lptrf_oneitem vertex_condition, type_lptrf_threeitems edge_condition);


void breadth_first_search_traversal_with_conditional_actions_in_graph(type_graph graph, char source[], type_lptrf_oneitem vertex_action, type_lptrf_oneitem vertex_condition, type_lptrf_threeitems edge_action, type_lptrf_threeitems edge_condition);
#endif 
