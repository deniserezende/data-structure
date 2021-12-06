#include <stdio.h>
#include <stdlib.h>
#include "qry_cx.h"



double QCX_limiar;
type_svg QCX_SVGFILE;
type_txt QCX_TXTFILE;
int *QCX_solution;
int QCX_index;


// void cx_vertex_action(type_vertex vertex){
//     _report_vertex_txt_(vertex);
//     double x = get_vertex_x(vertex);
//     double y = get_vertex_y(vertex);
//     char* colors[40] = {"Calamime", "Cardinal", "Celadon", "Cerulean", "Charcoal", "Chocolate", "Cyan", "Cornflower"};
//     int max = 7;
//     int min = 0;
//     int randNum = rand()%(max-min + 1) + min;


// // Colocar sob os vértices, elipses de cores
// // diferentes para cada região desconectada. 
//     insert_ellipse_in_svg(QCX_SVGFILE, x, y, 6, 3, colors[randNum], colors[randNum], 1);

// }

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

long cx_vertex_condition_true(type_vertex vertex){
    return 1;
}

long cx_duplicate_edge_condition(type_vertex from_vertex, type_edge edge, type_vertex to_vertex){
    double speed = get_edge_speed_limit(edge);
    if(speed < QCX_limiar) return 0;
    return 1;
}

// como para svg so existem 147 cores, se houverem mais de 147 componentes fortemente conexas em algum ponto algumas cores serao repetidas
// depois ver se isso 'e verdade ou se d'a para colocar:
// background: url("data:image/svg+xml;utf8,<svg xmlns='http://www.w3.org/2000/svg' width='20' height='10' ><path fill='%23FF0000' d='M 0,10 H 20 L 10,0 Z' /></svg>")  repeat-x;
// equivalente ao hexa
// maior numero de componentes conexas ate agr foi 350 +-
void cx_vertex_action_svg(type_vertex vertex){
    double x = get_vertex_x(vertex);
    double y = get_vertex_y(vertex);
    char* colors[145] = {"aliceblue", "antiquewhite", "aqua", "aquamarine", "azure", "beige", "bisque", "blanchedalmond", "blue", "blueviolet", "brown", "burlywood", "cadetblue", "chartreuse", "chocolate", "coral", "cornflowerblue", "cornsilk", "crimson", "cyan", "darkblue", "darkcyan", "darkgoldenrod", "darkgray", "darkgreen", "darkgrey", "darkkhaki" "darkmagenta", "darkolivegreen", "darkorange", "darkorchid", "darkred", "darksalmon", "darkseagreen", "darkslateblue", "darkslategray", "darkslategrey", "darkturquoise", "darkviolet", "deeppink", "deepskyblue", "dimgray", "dimgrey", "dodgerblue", "firebrick", "floralwhite", "forestgreen", "fuchsia", "gainsboro", "ghostwhite", "gold", "goldenrod", "gray", "green", "greenyellow",  "grey ",  "honeydew", "hotpink", "indianred", "indigo", "ivory", "khaki", "lavender", "lavenderblush", "lawngreen", "lemonchiffon", "lightblue",  "lightcoral", "lightcyan", "lightgoldenrodyellow", "lightgray", "lightgreen", "lightgrey", "lightpink", "lightsalmon", "lightseagreen", "lightskyblue", "lightslategray", "lightslategrey",   "lightsteelblue", "lightyellow", "lime", "limegreen", "linen", "magenta", "maroon", "mediumaquamarine", "mediumblue", "mediumorchid", "mediumpurple", "mediumseagreen", "mediumslateblue", "mediumspringgreen", "mediumturquoise", "mediumvioletred", "midnightblue", "mintcream", "mistyrose", "moccasin", "navajowhite", "navy", "oldlace", "olive", "olivedrab", "orange", "orangered", "orchid", "palegoldenrod", "palegreen", "paleturquoise", "palevioletred", "papayawhip", "peachpuff", "peru", "pink", "plum", "powderblue", "purple", "red", "rosybrown", "royalblue", "saddlebrown", "salmon", "sandybrown", "seagreen", "seashell", "sienna", "silver", "skyblue", "slateblue", "slategray", "slategrey", "snow", "springgreen", "steelblue", "tan", "teal", "thistle", "tomato", "turquoise", "violet", "wheat", "white",  "whitesmoke",  "yellow", "yellowgreen"};
    int max = 144;
    int min = 0;
    int randNum = rand()%(max-min + 1) + min;

    // txt
    _report_vertex_txt_(vertex);
    char* string = malloc(sizeof(char) * 60);
    
    sprintf(string, "REGIÃO %s", colors[QCX_solution[QCX_index]%145]);
    insert_string_in_txt(QCX_TXTFILE, string);
    free(string);
    // svg
    insert_ellipse_in_svg(QCX_SVGFILE, x, y, 6, 3, colors[QCX_solution[QCX_index]%145], colors[QCX_solution[QCX_index]%145], 1);
    QCX_index++;

}


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
void cx(type_svg SVGFILE, type_txt TXTFILE, type_graph via_graph, double limiar){
    QCX_limiar = limiar;
    QCX_SVGFILE = SVGFILE;

    int size = get_amount_of_vertices_in_graph(via_graph);
    int *solution = malloc(sizeof(int) * (size + 1));

    // fazer mini grafico
    type_graph subgraph = duplicate_graph_with_conditionals(via_graph, (void*)cx_vertex_condition_true, (void*)cx_duplicate_edge_condition);

    strongly_connected_components_algorithm(subgraph, solution);

    QCX_solution = solution;
    QCX_index = 0;
    //traverse_verticies_with_conditional_action_graph(subgraph, (void*)cx_vertex_action_svg, (void*)cx_vertex_condition_true);
    set_txt_file(TXTFILE);
    QCX_TXTFILE = TXTFILE;
    traverse_graph_conditional_actions(via_graph, (void*)cx_vertex_action_svg, (void*)cx_vertex_condition_true, (void*)cx_edge_action, (void*)cx_edge_condition);

    free(solution);
}