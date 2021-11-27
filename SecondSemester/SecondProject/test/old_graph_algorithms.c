
#include <stdio.h>
#include "graph.c"
#include "graph_algorithms.h"

// INT LONG OU FLOAT
// ACHO MELHOR FLOAT
// AI EU LIDO COM UM APONTADOR!!!!!!

typedef struct dijkstra_node{
	VERTEX* vertex;
	int edge_path_cost;
}DNODE; 


_set_up__dijkstras_values_in_graph_action_aux(VERTEX* vertex){
    vertex->temp_dijkstra_value = INT_MAX; // INT64_MAX
    // FLOAT?
}

void _set_up_dijkstras_values_in_graph_aux(GRAPH * graph, VERTEX* source){
    _traverse_graph_verticies_with_action(graph, (void*)_set_up__dijkstras_values_in_graph_action_aux);
    source->definitive_dijkstra_value = 0;
}


void dijkstras_algorithm_in_graph(type_graph graph, type_graphinfos source_info, type_graphptrf_twoitems compare_vertices, type_graphptrf_onetypeinfo get_edge_value){
	GRAPH *graph_ = graph; 
	VERTEX* source_node = _find_vertex_in_list_aux_graph(graph_->vertices, source_info, compare_vertices);
	_set_up_dijkstras_values_in_graph_aux(graph_, source_node);
    set_list_max_size(graph_->current_size+1);
    type_apqueue priority_queue = create_ascending_priority_queue();
	_dijkstras_algorithm_in_graph_aux(graph, source_node, priority_queue, get_edge_value);
}


long _compare_two_vertex_for_galgorithms(VERTEX* vertex, VERTEX* vertex2){
    return(strcmp(vertex->id,vertex2->id));
}

long _compare_two_vertex_for_galgorithms(VERTEX* vertex){
    if(vertex->)
}

void _dijkstras_algorithm_in_graph_aux(GRAPH * graph, VERTEX* vertex, type_list priority_queue, type_graphptrf_onetypeinfo get_edge_value){
	// base case:
    // visit os vizinhos e coloco valores temporarios do custo
    // tanto no grafo quanto na fila


    // setando os valores temp! -------------------
    if(vertex->edges != NULL){
        if(!empty_list(vertex->edges)){
            
            set_current_to_first_item_in_list(vertex->edges);

            int done;
            do{
                done = is_current_last_item_in_list(vertex->edges);

                // FALTA ALGUM TIPO DE VERIFICACAO SE O ELEMENTO JA TA LA 
                // SE SIM COMPARAR VALORES E MUDAR A PRIORIDADE
                //int change_item_priority_in_ascending_priority_queue(type_apqueue queue, int new_priority, type_apqitems item, type_apqptrf_twoitems check_if_equal);
                fin
                // colocando valores temporários no gráfo
                EDGE* edge = get_current_item_in_list(vertex->edges);
                long value = get_edge_value(edge->edge_info);
                (edge->to)->temp_dijkstra_value = value;

                int changed = conditionally_change_item_priority_in_ascending_priority_queue(priority_queue, value, edge->to, (void*)_compare_two_vertex_for_galgorithms, type_dpqptrf_oneitem condition);

                // colocando valores temporários na fila
                if(changed == -1) insert_item_in_ascending_priority_queue(priority_queue, value, edge->to);

                move_current_forward_in_list(vertex->edges);
            }while(!done);

            // pego o de menor custo e seto para definitivo
        }
    }

    // para onde vou?
    // PEGANDO DO PRIORITY QUEUE O MENOR 
    VERTEX* next_vertex =  pull_item_in_ascending_priority_queue(priority_queue);

    //return _dijkstras_algorithm_in_graph_aux(graph, next_vertex, priority_queue, get_edge_value);
    _dijkstras_algorithm_in_graph_aux(graph, next_vertex, priority_queue, get_edge_value);

}

// SOS AQUIDE ver que tipo colocar a variavel do edge!!!!!!


















