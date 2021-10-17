//
//  list.h
//   
//
//  Created by Denise F. de Rezende on 17/03/21.
//

#ifndef list_h
#define list_h

typedef void* type_list; 
typedef void* type_litems;
typedef void* type_lptrf_twoitems(type_litems, type_litems);
typedef void* type_lptrf_oneitem(type_litems);

 
/* This module provides functions for dealing with lists.
	Note that: Every function has it's pre-condition and post-condition,
	if ignored the result is unpredictable!
*/

// Pre-condition: None
// Post-condition: Max is set to the new value
// This function is optional!
void set_list_max_size(int size);

// Pre-condition: None
// Post-condition: The list exists and the current item is undefined
type_list create_list();

// Pre-condition: The list has to have been created
// Post-condition: None
// Returns a boolean: True if the list is full and false otherwise.
int full_list(type_list list);

// Pre-condition: The list has to have been created
// Post-condition: None
int list_current_size(type_list list);

// Pre-condition: The list has to have been created
// Post-condition: None
// Returns a boolean: True if the list is empty and false otherwise.
int empty_list(type_list list);

// Pre-condition: The list has to have been created
// Post-condition: The list does not exist
void destroi_list(type_list list);

// Pre-condition: The list exists and is not full
// Post-condition: The item has been inserted at the end of the list
void insert_item_at_the_end_of_list(type_list list, type_litems item);

// Pre-condition: The list exists and is not empty
// Post-condition: The item has been removed
// and if current pointed to item, now it points to the previous element
void delete_item_in_list(type_list list, type_litems item, type_lptrf_twoitems compare);

// Pre-condition: Current is set to an item in the list
// Post-condition: None
// Returns the item that current represents.
type_litems get_current_item_in_list(type_list list);

// Pre-condition: The list has to have been created
// Post-condition: None
// Returns a boolean: True if current is undefined and false otherwise.
int is_current_undefined_in_list(type_list list);

// Pre-condition: The list has to have been created
// Post-condition: None
// Returns a boolean: True if current is NULL and false otherwise.
// This function is here for debuging purpose
int is_current_equal_to_NULL(type_list list);

// Pre-condition: The list is not empty
// Post-condition: Current is the first item
void set_current_to_first_item_in_list(type_list list);

// Pre-condition: The list is not empty
// Post-condition: Current is the last item
void set_current_to_last_item_in_list(type_list list);

// Pre-condition: Current is set to an item in the list
// Post-condition: The item has been removed and current is the element that precedes the one removed if it exists otherwise it is undefined
void delete_current_item_in_list(type_list list);

// Pre-condition: Current is set to an item in the list
// Post-condition: The item has been removed and current is the element that precedes the one removed if it exists otherwise it is undefined
// Note that: This function returns the item so you can free it.
type_litems delete_allocated_current_item_in_list(type_list list);
// Pre-condition: Current can't be undefined 
// Post-condition: None
// Returns a boolean: True if current is the first item and false otherwise.
int is_current_first_item_in_list(type_list list);

// Pre-condition: Current can't be undefined 
// Post-condition: None
// Returns a boolean: True if current is the last item and false otherwise.
int is_current_last_item_in_list(type_list list);

// Pre-condition: The list exists.
// Post-condition: if item exists current is set to this item, otherwise current remains where it was.
// Returns a boolean: True if the item was found and false otherwise. 
int find_item_in_list(type_list list, type_litems item);

// Pre-condition: Current can't be undefined and current is not the last item.
// Post-condition: Current is now the next item.
void move_current_forward_in_list(type_list list);

// Pre-condition: Current can't be undefined and current is not the first item.
// Post-condition: Current is now the previous item.
void move_current_backward_in_list(type_list list);

// Pre-condition: Current can't be undefined.
// Post-condition: None
// Transverses from current comparing to all the elements in front of it and when the condition is true, a action is executed to both items.
// Note that: 'condition' receives two elements, the first is always the current element
void traverse_from_current_with_conditional_action_in_list(type_list list, type_lptrf_twoitems condition,  type_lptrf_twoitems action);

// Pre-condition: The list exists.
// Post-condition: None
// Transverses full list checking a condition, and if true taking action.
// Note that: the action function can include a deletion:
// if it does and the item was deleted: needs to return 1.
// if the action function does not include a deletion or if the item was not deleted: needs to returns 0.
void traverse_full_list_with_conditional_action(type_list list, type_lptrf_oneitem condition, type_lptrf_oneitem action);

#endif 
