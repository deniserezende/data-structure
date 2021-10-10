// 
//  qry_property_lease.h
//  
//
//  Created by Denise F. de Rezende.
//

#ifndef qry_property_lease_h
#define qry_property_lease_h

#include "hash_table.h"
#include "mM_avl_tree_wlist.h"
#include "rectangle.h"
#include "block.h"
#include "property.h"
#include "person.h"
#include "_auxiliary_functions.h"
#include "TXT.h"
#include "SVG.h"

// usa a avl oloc_

void oloc(type_hashtable property_leases, char property_lease_id[], char cep[], char cardinal_direction, int house_number, char addicional_data[], double property_area, double monthly_rent);

void oloc_(type_svg SVGFILE, type_txt TXTFILE, type_mMlavltree blocks, type_hashtable property_leases, double x, double y, double w, double h);

int loc(type_svg SVGFILE, type_txt TXTFILE, type_hashtable blocks_table, type_hashtable property_leases, type_hashtable people_table, char property_lease_id[], char person_cpf[]);

int loc_(type_svg SVGFILE, type_txt TXTFILE, type_hashtable blocks_table, type_hashtable property_leases, char property_lease_id[]);

int dloc(type_txt TXTFILE, type_hashtable blocks_table, type_hashtable property_leases, char property_lease_id[]);
#endif /* qry_property_lease_h */