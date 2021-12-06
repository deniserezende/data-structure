//
//  geo_operations.h
//  
//
//  Created by Denise F. de Rezende on 12/09/21.
//

#ifndef geo_operations_h
#define geo_operations_h
#include "hash_table.h"
#include "mM_avl_tree_wlist.h"
#include "rectangle.h"
#include "block.h"
#include "_auxiliary_functions.h"

// Reads and interprets the geofile.
type_mMlavltree get_geo_input(char *geo_fullpath, type_mMlavltree cityblocks_tree, type_hashtable cityblocks_table, double view_box[4]);

#endif /* geo_operations_h */
 