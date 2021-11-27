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
#include "graph_algorithms.h"
#include "property.h"
#include "edge.h" //aquide
#include "vertex.h" //aquide
#include "_geometry_operations.h"

void p_(type_svg SVGFILE, type_txt TXTFILE, type_mMlavltree blocks_avl, type_hashtable blocks_hashtable, type_graph via_graph, type_property property, char cep[], char cardinal_direction, int house_number, char shortest_route_color[], char fastest_route_color[]);

#endif /* qry_p_h */