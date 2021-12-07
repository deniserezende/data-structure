#ifndef qry_cx_h
#define qry_cx_h
#include "SVG.h"
#include "graph.h"
#include "vertex.h"
#include "edge.h"
#include "_auxiliary_functions.h"
#include "strongly_connected_components_algorithm.h"

// Calcule as regiões isoladas. Considere inacessível as regiões não conectas ou se estiverem 
// conectadas apenas por trechos com velocidades médias abaixo do limiar especificado.
// TXT: reportar os identificadores dos vértices de cada região
// SVG: pintar de vermelho e com traço grosso os trechos com velocidade abaixo do limiar.
// Colocar sob os vértices, elipses de cores diferentes para cada região desconectada. 
void cx(type_svg SVGFILE, type_txt TXTFILE, type_graph via_graph, double limiar);

#endif