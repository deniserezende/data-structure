#ifndef dijkstras_algorithm_h
#define dijkstras_algorithm_h

#include "ascending_priority_queue.h"
#include "list.h"
#include "graph.h"

typedef void* type_graphptrf_twotypeinfo(type_graphinfos, type_graphinfos);

// Dijkstra's algorithm is an algorithm for finding the shortest paths between nodes in a graph, 
// This specific implementation finds the shortest path between two points only.
type_list dijkstras_algorithm_with_destination_in_graph(type_graph graph, char source_info_id[], char destination_info_id[], type_graphptrf_onetypeinfo get_edge_value);

type_list dijkstras_destroi_solution_array(type_list solution_array);

#endif