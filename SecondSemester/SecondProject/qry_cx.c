#include <stdio.h>
#include <stdlib.h>
#include "qry_cx.h"

// Calcule as regiões isoladas. Considere
// inacessível as regiões não conectas ou se
// estiverem conectadas apenas por trechos com
// velocidades médias abaixo do limiar
// especificado.
// TXT: reportar os identificadores dos vértices de
// cada região
// SVG: pintar de vermelho e com traço grosso os
// trechos com velocidade abaixo do limiar.
// Colocar sob os vértices, elipses de cores
// diferentes para cada região desconectada. 

double QCX_limiar;
type_svg QCX_SVGFILE;

void cx_vertex_action(type_vertex vertex){
    _report_vertex_txt_(vertex);
    double x = get_vertex_x(vertex);
    double y = get_vertex_y(vertex);
    char* colors[40] = {"Calamime", "Cardinal", "Celadon", "Cerulean", "Charcoal", "Chocolate", "Cyan", "Cornflower"};
    int max = 7;
    int min = 0;
    int randNum = rand()%(max-min + 1) + min;


// Colocar sob os vértices, elipses de cores
// diferentes para cada região desconectada. 
    insert_ellipse_in_svg(QCX_SVGFILE, x, y, 6, 3, colors[randNum], colors[randNum], 1);

}

void cx_edge_action(type_vertex from_vertex, type_edge edge, type_vertex to_vertex){

// SVG: pintar de vermelho e com traço grosso os
// trechos com velocidade abaixo do limiar.
// Colocar sob os vértices, elipses de cores
// diferentes para cada região desconectada. 

    double x = get_vertex_x(from_vertex);
    double x2 = get_vertex_x(to_vertex);
    double y = get_vertex_y(from_vertex);
    double y2 = get_vertex_y(to_vertex);
    char color[5];
    sprintf(color, "red%c", '\0');
    insert_line_in_svg(QCX_SVGFILE, x, y, x2, y2, color, 3);

    //AQUI DE precisa disso??
    _report_edge_txt_(edge);

}

long cx_edge_condition(type_vertex from_vertex, type_edge edge, type_vertex to_vertex){
    double speed = get_edge_speed_limit(edge);    
    if(speed < QCX_limiar) return 1;
    return 0;
}



void cx(type_svg SVGFILE, type_txt TXTFILE, type_graph via_graph, double limiar){
    printf("limiar=%lf\n", limiar);
    QCX_limiar = limiar;
    QCX_SVGFILE = SVGFILE;

    set_txt_file(TXTFILE);

    // AQUIDE fazer algo no svg
    traverse_graph_conditional_actions_plus_vertex_condition_is_no_edges(via_graph, (void*)cx_vertex_action, (void*)cx_edge_action, (void*)cx_edge_condition);

}