#ifndef kruskals_algorithm_h
#define kruskals_algorithm_h

#include "graph.h"
#include "disjoint_sets.h"
#include "ascending_priority_queue.h"


type_graph kruskals_algorithm_in_graph(type_graph graph, type_graphptrf_onetypeinfo get_edge_value);


type_graph kruskals_algorithm_in_graph_forest(type_graph graph, type_graphptrf_onetypeinfo get_edge_value, int *vector);
#endif