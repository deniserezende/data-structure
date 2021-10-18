// 
//  qry_dmpt_catac.h
//  
//
//  Created by Denise F. de Rezende.
//

#ifndef qry_dmpt_catac_h
#define qry_dmpt_catac_h
#include "hash_table.h"
#include "rectangle.h" 
#include "block.h"
#include "property.h"
#include "person.h"
#include "_auxiliary_functions.h"
#include "SVG.h"
#include "TXT.h"
#include "graphviz_draw.h"

type_mMlavltree catac(type_svg SVGFILE, type_txt TXTFILE, type_mMlavltree blocks_avl, type_hashtable blocks_table, type_hashtable properties_table, type_hashtable property_leases, type_hashtable people_table, double x, double y, double w, double h);
void dmpt(type_dot DOTFILE, type_mMlavltree blocks_avl);

#endif /* qry_dmpt_catac_h */