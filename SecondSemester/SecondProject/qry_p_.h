// 
//  qry_p_.h
//  
//
//  Created by Denise F. de Rezende.
//

#ifndef qry_p_h
#define qry_p_h
#include "hash_table.h"
#include "rectangle.h" 
#include "block.h"
#include "_auxiliary_functions.h"
#include "SVG.h"
#include "TXT.h"
#include "graph.h"
#include "dijkstras_algorithm.h"
#include "property.h"
#include "edge.h" 
#include "vertex.h"
#include "_geometry_operations.h"

// Qual o melhor trajeto de carro entre a origem (@o?) e o destino especificado pelo endereço
// cep/face/num. O percurso na representação pictórica deve indicar o trajeto mais curto na cor
// cmc e o trajeto mais rápido com a cor cmr.
// TXT: descrição textual do percurso
// SGV : traçar (linhas) dos percursos com as cores correspondentes. Cuidado para que uma
// percurso não esconda o outro. Indicar o início e o fim do percurso. As linhas devem ser grossas,
// mas menos espessas que as arestas da AGM
void p_(type_svg SVGFILE, type_txt TXTFILE, type_mMlavltree blocks_avl, type_hashtable blocks_hashtable, type_graph via_graph, type_property property, char cep[], char cardinal_direction, int house_number, char shortest_route_color[], char fastest_route_color[]);

#endif /* qry_p_h */