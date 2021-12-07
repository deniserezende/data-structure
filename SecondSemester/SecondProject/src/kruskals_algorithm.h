#ifndef kruskals_algorithm_h
#define kruskals_algorithm_h

#include "graph.h"
#include "disjoint_sets.h"
#include "ascending_priority_queue.h"

// Kruskal's algorithm finds a minimum spanning forest of an undirected edge-weighted graph. 
// If the graph is connected, it finds a minimum spanning tree.
type_graph kruskals_algorithm_in_graph(type_graph graph, type_graphptrf_onetypeinfo get_edge_value);

type_graph kruskals_destroi_solution_graph(type_graph solution_graph);

#endif