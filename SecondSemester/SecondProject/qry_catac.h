// 
//  qry_catac.h
//  
//
//  Created by Denise F. de Rezende.
//

#ifndef qry_dmpt_catac_h
#define qry_dmpt_catac_h
#include "hash_table.h"
#include "rectangle.h" 
#include "block.h"
#include "_auxiliary_functions.h"
#include "SVG.h"
#include "TXT.h"
#include "graph.h"
#include "vertex.h"
#include "_geometry_operations.h"
#include "edge.h"
type_mMlavltree catac(type_svg SVGFILE, type_txt TXTFILE, type_mMlavltree blocks_avl, type_hashtable blocks_hashtable, type_graph via_graph, double x, double y, double w, double h);

#endif /* qry_dmpt_catac_h */