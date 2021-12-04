
#ifndef depth_first_search_in_graph_h
#define depth_first_search_in_graph_h

#include "graph.h"

void DFS_traverse_graph_verticies_with_action(type_graph graph, type_graphptrf_onetypeinfo action);
void DFS_depth_first_search_with_actions_in_graph(type_graph graph, char order[][40], type_lptrf_oneitem vertex_action_one, type_lptrf_oneitem vertex_action_two);
#endif