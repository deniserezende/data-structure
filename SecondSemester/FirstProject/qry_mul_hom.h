// 
//  qry_mul_hom.h
//  
//
//  Created by Denise F. de Rezende.
//

#ifndef qry_mul_hom_h
#define qry_mul_hom_h

#include "hash_table.h"
#include "mM_avl_tree_wlist.h"
#include "block.h"
#include "property.h"
#include "person.h"
#include "_auxiliary_functions.h"
#include "SVG.h"
#include "TXT.h"

void mul(type_svg SVGFILE, type_txt TXTFILE, type_mMlavltree blocks_avl, type_hashtable properties_table, type_hashtable property_leases, type_hashtable people_table, double x, double y, double w, double h);

void hom(type_svg SVGFILE, type_txt TXTFILE, type_mMlavltree blocks_avl, type_hashtable properties_table, type_hashtable property_leases, type_hashtable people_table, double x, double y, double w, double h);


#endif /* qry_mul_hom_h */