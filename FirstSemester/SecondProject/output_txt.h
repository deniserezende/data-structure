// 
//  output_txt.h -> Used for the second project of Data Structure
//  
//
//  Created by Denise F. de Rezende.
//

#ifndef output_txt_h
#define output_txt_h
#include "binary_search_tree.h"
#include "rectangle.h"
#include "circle.h"
#include "TXT.h"

// These function will insert data in txtfiles in alphanumeric order.

// Insert rectangles and circles that are in the binary search tree
// This function is only used when fg function is called.
void save_rectid_circleid_for_txt(type_bstree tree, type_rect rectangle, type_circle circle);
void insert_rectid_circleid_in_txt(type_bstree tree, type_txt txtfile);

// Inserts rectangles that are in the binary search tree in the txtfile
void save_rectid_for_txt(type_bstree tree, type_rect rectangle);
void insert_rectid_in_txt(type_bstree tree, type_txt txtfile);

// Inserts circles that are in the binary search tree in the txtfile
void save_circleid_for_txt(type_bstree tree, type_circle circle);
void insert_circleid_in_txt(type_bstree tree, type_txt txtfile);


#endif /* output_txt_h */