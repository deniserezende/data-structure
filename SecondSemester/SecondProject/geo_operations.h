//
//  geo_operations.h -> interprets the geofile of the first project of Data Structure II
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

// Reads and interprets the geofile, adding circles and rectangles to the respective kdtree sent.
type_mMlavltree get_geo_input(char *geo_fullpath, type_mMlavltree cityblocks_tree, type_hashtable cityblocks_table, double view_box[4]);

#endif /* geo_operations_h */
 