//
//  kd_tree.h
//   
//
//  Created by Denise F. de Rezende on 29/05/21.
//

#ifndef kd_tree_h
#define kd_tree_h

typedef void* type_kdtree;
typedef void* type_kdtitems;
typedef void* type_kdtptrf_twoitems_oneint(type_kdtitems, type_kdtitems, int);
typedef void* type_kdtptrf_oneitem(type_kdtitems);
typedef void* type_kdtptrf_oneitem_oneint(type_kdtitems, int);

/* This module provides functions for dealing with k-dimensional trees.
	Note that: Every function has it's pre-condition and post-condition,
	if ignored the result is unpredictable!
*/

// Pre-condition: None
// Post-condition: The kdtree exists.
type_kdtree create_kdtree(int dimension);

// Pre-condition: The kdtree has to have been created
// Post-condition: None
// Returns a boolean: True if the kdtree is empty and false otherwise.
int empty_kdtree(type_kdtree kdtree);

// Pre-condition: The kdtree has to have been created
// Post-condition: None
// Returns a boolean: True if the kdtree is full and false otherwise.
int full_kdtree(type_kdtree kdtree);

// Pre-condition: The kdtree exists and is not full.
// Post-condition: The item has been inserted. 
// If greater than or equal to the dimension, item is inserted at the right subkdtree.
// Note that: 'compare' receives two items, the first is always the item to be inserted.
// if equal, returns 0.
// if the first item is greater than the second return number > 0.
// if the first item is less than the second return number < 0.
// the function 'compare' should return a value convertable to 'long'
int insert_item_in_kdtree(type_kdtree kdtree, type_kdtitems item, int dimension, type_kdtptrf_twoitems_oneint compare);

// Pre-condition: The kdtree exists.
// Post-condition: None.
// Note that: the action function can include a deletion:
// must return fail or success if it includes a deletion (0 or 1 respectively)
// if it does not include deletion, function must contain a return fail (0).
// Note that: the traverse_side function determines which side to traverse to.
// if traverse_side should be right, returns 01
// if traverse_side should be left, returns 10
// if traverse_side should be both, returns 11
// Transverses kdtree depending on traverse side, checks a condition and if true takes action.
void traverse_kdtree_with_conditional_action(type_kdtree kdtree, int dimension, type_kdtptrf_oneitem_oneint traverse_side, type_kdtptrf_oneitem condition, type_kdtptrf_oneitem action);

// Pre-condition: The kdtree exists and the action function cannot include a deletion.
// Post-condition: None
// Transverses the full kdtree checking a condition and if true taking action.
void traverse_full_kdtree_with_conditional_action(type_kdtree kdtree, type_kdtptrf_oneitem condition, type_kdtptrf_oneitem action);

// Pre-condition: The kdtree exists.
// Post-condition: None
// Transverses kdtree checking a condition when condition is true takes action and exists traverse.
void traverse_kdtree_until_condition_is_met_then_take_action(type_kdtree kdtree, type_kdtptrf_oneitem condition, type_kdtptrf_oneitem action);

// Pre-condition: The kdtree exists.
// Post-condition: The kdtree does not exist.
void destroi_kdtree(type_kdtree kdtree, int dimension, type_kdtptrf_oneitem action);

#endif /* kd_tree_h */



