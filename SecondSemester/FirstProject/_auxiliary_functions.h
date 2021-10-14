// 
//  _auxiliary_functions.h
//  
//
//  Created by Denise F. de Rezende.
//

#ifndef _auxiliary_functions_h
#define _auxiliary_functions_h

#include "hash_table.h"
#include "mM_avl_tree_wlist.h"
#include "rectangle.h"
#include "block.h"
#include "property.h"
#include "person.h"

void set_id(char id[]);
void set_x1_x2_y1_y2(double x1, double x2, double y1, double y2);
long traverse_side_rect_in_rect_(type_mMlavlitems item, type_mMlavlitems lminimum, type_mMlavlitems lmaximum, type_mMlavlitems rminimum, type_mMlavlitems rmaximum);
long condition_rect_in_rect_(type_mMlavlitems item);
long get_key_from_block(type_rect block);
long compare_rect_blocks_cep(type_rect block1, type_rect block2);
long verify_block_found(type_rect block);
long verify_property_found(type_property property);
long verify_person_found(type_person person);
long verify_property_leases(type_property property);

#endif /* _auxiliary_functions_h */