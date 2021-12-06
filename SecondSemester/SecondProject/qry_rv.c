#include "qry_rv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

type_rect QRV_rectangle;
char* QRV_ID;
int QRV_index;
double QRV_f;
type_svg QRV_SVGFILE;

long _rv_graph_duplicate_vertex_condition(type_graphinfos vertex){
    double vertex_x = get_vertex_x(vertex);
    double vertex_y = get_vertex_y(vertex);

    return point_in_rect(QRV_rectangle, vertex_x, vertex_y);
}

long _rv_graph_duplicate_edge_condition(type_graphinfos from_vertex, type_graphinfos edge, type_graphinfos to_vertex){
    long from_vertex_in_rect = _rv_graph_duplicate_vertex_condition(from_vertex);
    long to_vertex_in_rect = _rv_graph_duplicate_vertex_condition(to_vertex);

    if(from_vertex_in_rect && to_vertex_in_rect) return 1;
    return 0;
}

long _kruskals_get_edge_length(type_edge edge){
    return (long)get_edge_length(edge);
}

long _rv_reduce_speed_condition_vertex(type_graphinfos vertex){
    return 1;
}

long _rv_reduce_speed_condition_edge(type_graphinfos from_vertex, type_graphinfos edge, type_graphinfos to_vertex){
    return 1;
}

void _rv_reduce_speed_action_vertex(type_graphinfos vertex){
    QRV_index++;
    return;
}

void _rv_reduce_speed_action_edge(type_graphinfos from_vertex, type_graphinfos edge, type_graphinfos to_vertex){
    double current_speed = get_edge_speed_limit(edge);
    double new_speed = current_speed * (QRV_f * QRV_index);
    set_edge_speed_limit(edge, new_speed); 

    // values for report
    double x1 = get_vertex_x(from_vertex);
    double y1 = get_vertex_y(from_vertex);
    double x2 = get_vertex_x(to_vertex);
    double y2 = get_vertex_y(to_vertex);

    // reporting
    _report_edge_txt_(edge);
    char color_blue[6];
    sprintf(color_blue, "Blue%c", '\0');
    char color_PeachPuff[12];
    sprintf(color_PeachPuff, "PeachPuff%c", '\0');

    insert_line_in_svg(QRV_SVGFILE, x1, y1, x2, y2, color_PeachPuff, 5);
    if(QRV_index == 1){
        insert_ellipse_in_svg(QRV_SVGFILE, x1, y1, 6, 5, color_blue, color_blue, 3); 
        insert_text_in_svg(QRV_SVGFILE, x1+5, y1-5, color_blue, "Raiz", 20); 
    }
    return;
}

long _rv_get_id_condition(type_vertex vertex){
    return 1;
}

void _rv_get_id_action(type_vertex vertex){
    char *id = get_vertex_id(vertex);
    QRV_ID = id;
}
void _rv_do_nothing_edge_destroi(type_graphinfos from_vertex, type_graphinfos edge, type_graphinfos to_vertex){
    return;
}

void _rv_do_nothing_vertex_destroi(type_graphinfos vertex){
    return;
}


// Calcule a árvore geradora mínima do subgrafo
// com os vértices que estão dentro da região
// especificada pela retângulo x,y,w,h. A velocidade
// dos trechos relativos às arestas da árvore
// geradora mínima deve ser reduzida, a cada nível
// da árvore, de acordo com o fator f (0.0 < f <
// 1.0), até, no mínimo, 0.01 (ou seja, 1%). Por
// exemplo, se f = 0.05, a velocidade deve ser
// reduzida de 5% da velocidade original nas
// arestas que ligam a raiz da árvore aos seus
// filhos; de 10% nas arestas que ligam os filhos
// aos netos; de 15%, nas que ligam os netos aos
// bisnetos e assim sucessivamente.
// TXT: reportar arestas da AGM, incluindo seus
// atributos (busca em largura)
// SVG: pintar as arestas da AGM com um traço
// bastante largo e de uma cor clara. Delimitar a
// região x,y,w,h com um retângulo de bordas
// grossas e tracejadas. ATENÇÃO: Indicar a raiz
// da AGM
void rv(type_svg SVGFILE,type_txt TXTFILE, type_graph via_graph, double x, double y, double w, double h, double f){
    QRV_SVGFILE = SVGFILE;
    set_txt_file(TXTFILE);
    type_rect rectangle = new_rectangle("", x, y, w, h, "", "");
    QRV_rectangle = rectangle;
    
    // Find the items that are in the rectangle sent
    // and create a subgraph based on the original graph
    type_graph subgraph = duplicate_graph_with_conditionals(via_graph, (void*)_rv_graph_duplicate_vertex_condition, (void*)_rv_graph_duplicate_edge_condition);

    // Kruskal in the subgraph to find the minimum generator tree
    type_graph mst = kruskals_algorithm_in_graph(subgraph, (void*)_kruskals_get_edge_length);

    // Getting an item to represent the root
    traverse_verticies_until_conditional_action_graph(mst, (void*)_rv_get_id_action, (void*)_rv_get_id_condition);

    QRV_f = f;
    QRV_index = 0;
    // Generating output
    // and reducing the speed of some edges
    breadth_first_search_traversal_with_conditional_actions_in_graph(mst, QRV_ID, (void*)_rv_reduce_speed_action_vertex, (void*)_rv_reduce_speed_condition_vertex, (void*)_rv_reduce_speed_action_edge, (void*)_rv_reduce_speed_condition_edge);
    insert_dasharray_rect_in_svg(SVGFILE, x, y, w, h, "Transparent", "Red", 4, 4);

    // Clean up
    destroi_graph(subgraph, (void*)_rv_do_nothing_vertex_destroi, (void*)_rv_do_nothing_edge_destroi);
    kruskals_destroi_solution_graph(mst);
    destroi_rectangle(rectangle);
}