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

// Pre-condition: None
// Post-condition: The graph exists.
type_graph create_graph();

// Pre-condition: The graph has to have been created
// Post-condition: None
// Returns a boolean: True if the graph is empty and false otherwise.
int empty_graph(type_graph graph);

// Pre-condition: The graph exists
// Post-condition: None
int get_amount_of_vertices_in_graph(type_graph graph);

// Pre-condition: The graph exists.
// Post-condition: The vertex has been inserted
// If vertex was previously in graph than function returns 0 and doesn't add the vertex
int add_vertex_to_graph(type_graph graph, char id[]);

// Pre-condition: The graph exists
// Post-condition: The vertex info has been inserted if the vertex with id was in the graph
// If vertex had already been inserted in graph
int set_vertex_info_in_graph(type_graph graph, char id[], type_graphinfos vertex_info);

// Pre-condition: The graph exists and the vertex already exists in graph
// Post-condition: None
type_graphinfos get_vertex_info_in_graph(type_graph graph, char id[]);

// Pre-condition: The graph exists
// Post-condition: If the vertex was in graph now it has been removed
type_graphinfos remove_vertex_from_graph(type_graph graph, char id[], type_graphptrf_onetypeinfo deallocate_edge);

// Pre-condition: The graph exists.
// Post-condition: The edge has been inserted
// if "from vertex" and "to vertex" had already been inserted, in which case function returns 1 
int add_edge_to_graph(type_graph graph, char from_vertex_id[], char to_vertex_id[]);

// Pre-condition: The graph exists.
// Post-condition: The edge has been inserted
// if edge had already been inserted in graph, in which case function returns 1 
int set_edge_info_in_graph(type_graph graph, char from_vertex_id[], char to_vertex_id[], type_graphinfos edge_info);

// Pre-condition: The graph exists and the both vertices already exist in graph
// Post-condition: None
type_graphinfos get_edge_info_in_graph(type_graph graph, char from_vertex_id[], char to_vertex_id[]);

// Pre-condition: The graph exists
// Post-condition: If the edge was in graph now it has been removed
type_graphinfos remove_edge_from_graph(type_graph graph, char from_vertex_id[], char to_vertex_id[]);

// Pre-condition: The graph exists
// Post-condition: prints the graph
void print_graph(type_graph graph, type_graphptrf_onetypeinfo print_vertex, type_graphptrf_onetypeinfo print_edge);

// Pre-condition: The graph exists
// Post-condition: The graph does not exist
void destroi_graph(type_graph graph, type_graphptrf_onetypeinfo deallocate_vertex, type_graphptrf_onetypeinfo deallocate_edge);

// Pre-condition: The graph exists and the both vertices already exist in graph
// Post-condition: None
// If yes, returns the edge info else returns NULL
type_graphinfos are_vertex_adjacent_in_graph_return_edge(type_graph graph, char from_vertex_id[], char to_vertex_id[]);

// Pre-condition: The graph exists and the both vertices already exist in graph
// Post-condition: None
// Returns 1 (true) or 0 (false)
int are_vertex_adjacent_in_graph(type_graph graph, char from_vertex_id[], char to_vertex_id[]);

// Pre-condition: The graph exists and the vertex is in the graph
// Post-condition: None
// Returns a list of neighbors
type_list vertex_neighbors_in_graph(type_graph graph, char id[]);

// Destrois list of neighbors
type_list destroi_list_created_with_vertex_neighbors_in_graph(type_list list);

// Pre-condition: The graph has to have been created
// Post-condition: None
// See (1), (2), (3) and (4)
void traverse_graph_conditional_actions(type_graph graph, type_lptrf_oneitem vertex_action, type_lptrf_oneitem vertex_condition, type_lptrf_threeitems edge_action, type_lptrf_threeitems edge_condition);

// Pre-condition: The graph has to have been created
// Post-condition: None
// See (1) and (2)
int traverse_verticies_until_conditional_action_graph(type_graph graph, type_lptrf_oneitem vertex_action, type_lptrf_oneitem vertex_condition);

// Pre-condition: The graph has to have been created
// Post-condition: None
// See (1) and (2)
void traverse_verticies_with_conditional_action_graph(type_graph graph, type_lptrf_oneitem vertex_action, type_lptrf_oneitem vertex_condition);

// Pre-condition: The graph has to have been created
// Post-condition: None
// See (1) and (3)
type_graph duplicate_graph_with_conditionals(type_graph graph, type_lptrf_oneitem vertex_condition, type_lptrf_threeitems edge_condition);

// Pre-condition: The graph has to have been created
// Post-condition: None
// See (1) and (3)
type_graph create_reverse_graph_with_conditionals(type_graph base_graph, type_lptrf_oneitem vertex_condition, type_lptrf_threeitems edge_condition);

// Pre-condition: The graph has to have been created
// Post-condition: None
// See (1), (2), (3) and (4)
void breadth_first_search_traversal_with_conditional_actions_in_graph(type_graph graph, char source[], type_lptrf_oneitem vertex_action, type_lptrf_oneitem vertex_condition, type_lptrf_threeitems edge_action, type_lptrf_threeitems edge_condition);


/* Functions: */

// (1) Note that: 'vertex_action' receives one item
// Function should return a long value either 1 or 0.

// (2) Note that: 'vertex_condition' receives one item
// Function cannot include a deletion.

// (3) Note that: 'edge_condition' receives three item
// Function should return a long value either 1 or 0.
// This function gives you these items in 'this exact order'.
// 1. From vertex info
// 2. Edge info
// 3. To vertex info

// (4) Note that: 'edge_action' receives three item
// Function cannot include a deletion.
// This function gives you these items in 'this exact order'.
// 1. From vertex info
// 2. Edge info
// 3. To vertex info


/*

IMPORTANT THIS IS ONLY SHARED FOR DEVELOPERS WHO NEED TO IMPLEMENT BIG ALGORITHMS 
THAT NEED DIRECT ACCESS TO THE GRAPH AND SPACE FOR THERE DATA INSIDE THE GRAPH
LIKE DIJKSTRAS, KRUSKAL...


typedef struct my data{
    // content
}MY_DATA;

typedef struct vertex{
	char id[41];
	type_graphinfos *vertex_info;
	type_list edges;
	void* other_data;
	MY_DATA* data_for_other_algorithms; // HERE YOU WILL ADD A POINTER TO A STRUCT WITH YOUR DATA
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

*/

#endif 
