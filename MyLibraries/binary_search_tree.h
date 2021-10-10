//
//  binary_search_tree.h
//  
//
//  Created by Denise F. de Rezende on 17/05/21.
//

#ifndef binary_search_tree_h
#define binary_search_tree_h

typedef void* type_bstree; 
typedef void* type_bstitems;
typedef void* type_bstptrf_twoitems(type_bstitems, type_bstitems);
typedef void* type_bstptrf_oneitem(type_bstitems);

/* This module provides functions for dealing with binary search trees.
	Note that: Every function has it's pre-condition and post-condition,
	if ignored the result is unpredictable!
*/

// Pre-condition: None
// Post-condition: The binary search tree exists.
type_bstree create_binary_search_tree();

// Pre-condition: The binary search tree has to have been created
// Post-condition: None
// Returns a boolean: True if the binary search tree is full and false otherwise.
int full_binary_search_tree(type_bstree tree);

// Pre-condition: The binary search tree has to have been created
// Post-condition: None
// Returns a boolean: True if the binary search tree is empty and false otherwise.
int empty_binary_search_tree(type_bstree tree);

// Pre-condition: The binary search tree exists and is not full
// Post-condition: The item has been inserted.
// Note that: 'compare' receives two items, the first is always the item to be inserted.
// if item to be inserted is greater than current item, compare should return number > 0
// if item to be inserted is less than current item, compare should return number < 0
// if both items are equal, compare should return 0
// the function 'compare' should return a value convertable to 'long'
int insert_item_in_binary_search_tree(type_bstree tree, type_bstitems item, type_bstptrf_twoitems compare);

// Pre-condition: The binary search tree exists.
// Post-condition: if item exists it is returned, else the function returns NULL.
type_bstitems search_in_binary_search_tree(type_bstree tree, type_bstitems item, type_bstptrf_twoitems compare);

// Pre-condition: The binary search tree exists.
// Post-condition: None.
// This function traverses the binary search tree in order performing action. 
// Note that: this action can't include deletion. 
void in_order_traversal_binary_search_tree(type_bstree tree, type_bstptrf_oneitem action);

// Pre-condition: The binary search tree exists.
// Post-condition: The item has been deleted.
// Note that: 'compare' receives two items, the first is always the item sent by the user as 'item'.
// if 'item' is greater than current item, compare should return number > 0
// if item is less than current item, compare should return number < 0
// if both items are equal, compare should return 0
// the function 'compare' should return a value convertable to 'long'
void delete_item_in_binary_search_tree(type_bstree tree, type_bstitems item, type_bstptrf_twoitems compare);

// Pre-condition: The binary search tree has to have been created
// Post-condition: The binary search tree does not exist.
// Note that: the action function is available in case the items inserted in the tree have been malloc.
// use this function to free them, to avoid memory leak.
void destroi_binary_search_tree(type_bstree tree, type_bstptrf_oneitem action);

#endif /* binary_search_tree_h */




